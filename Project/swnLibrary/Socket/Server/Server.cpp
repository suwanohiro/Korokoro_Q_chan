#include "Server.h"

void Server::__acceptThread()
{
	// サーバーソケットを作成
	if (!__makeSocket()) return;

	struct sockaddr_in tmp_addr;
	memset(&tmp_addr, 0, sizeof(struct sockaddr_in));
	tmp_addr.sin_family = AF_INET;
	tmp_addr.sin_port = htons(_port);
	tmp_addr.sin_addr.s_addr = ADDR_ANY;

	// ソケットをバインド
	if (bind(_tsock, (struct sockaddr*)&tmp_addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		// エラーメッセージを設定
		__addError("Error: Socket Bind");
		__closeSocket();
		return;
	}

	// 接続待機状態にする
	if (listen(_tsock, SOMAXCONN) == SOCKET_ERROR) {
		// エラーメッセージを設定
		__addError("Error: Socket Listen");
		__closeSocket();
		return;
	}

	__addDebug("Socket Listening...");

	while (true)
	{
		SOCKADDR_IN ta;
		int addrin_size = sizeof(SOCKADDR_IN);
		__addDebug("Wait Accept");

		SOCKET ts = accept(_tsock, (struct sockaddr*)&ta, &addrin_size);

		if (ts == INVALID_SOCKET) break;

		std::string msg = std::string("Client IP : " + std::string(inet_ntoa(ta.sin_addr)));
		//__addDebug((char*)msg.c_str());
		__addDebug("Connect Client");

		ClientData tmp;
		tmp.socket = ts;
		_clients.push_back(&tmp);

		// クライアントからの受信を処理するスレッドを起動
		std::thread recvThread(&Server::__recvThread, this, &tmp);
		recvThread.detach();
	}
	_endthreadex(NULL);
}

void Server::__recvThread(ClientData* client)
{
	client->isConnect = true;
	while (true)
	{
		char* msg;

		// クライアントからデータを受信
		int s = recv(client->socket, (char*)&msg, sizeof(msg), 0);
		if (s <= 0) {
			__addDebug("Exit Client");
			__addDebug("Connection End");
			break;
		}

		__recvFunc(msg);

		// 受信したメッセージを配列に追加
		_receivedData.push_back(msg);

		for (unsigned int cnt = 0; cnt < _clients.size(); cnt++) {
			// 接続状態でないなら送信をしない
			if (!_clients[cnt]->isConnect) continue;

			// 送信主には送信をしない
			if (_clients[cnt] == client) continue;

			// 他のクライアントにもメッセージを送信
			send(_clients[cnt]->socket, (char*)msg, sizeof(msg), 0);
		}
	}
	client->isConnect = false;
	_endthreadex(NULL);
}

void Server::__closeSocket()
{
	// サーバー処理が開始されていなければここで処理終了
	if (!_isServerStart) return;

	// ソケットのクリーンアップとスレッドの停止待機
	for (unsigned int cnt = 0; cnt < _clients.size(); cnt++) {
		if (!_clients[cnt]->isConnect) continue;
		closesocket(_clients[cnt]->socket);
	}

	_acceptThread.join();

	WSACleanup();

	_isServerStart = false;
}

Server::Server(const unsigned short port)
{
	_port = port;

	__recvFunc = [=](char*) {};
}

Server::Server(const unsigned short port, std::function<void(char*)> recvFunc)
{
	_port = port;

	__recvFunc = recvFunc;
}

Server::~Server()
{
	__closeSocket();
}

bool Server::Start()
{
	// Winsockの初期化
	if (!__initWinsock()) return false;

	// クライアント接続待機スレッドを開始
	_acceptThread = std::thread(&Server::__acceptThread, this);

	_isServerStart = true;

	return true;
}

std::vector<char*> Server::getReceivedData()
{
	return _receivedData;
}
