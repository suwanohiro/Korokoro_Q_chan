#pragma once

#include "../Socket.h"

class Server : public Socket
{
private:
	/// <summary>
	/// クライアント情報
	/// </summary>
	struct ClientData {
		// 接続中か
		bool	isConnect;

		// ソケット
		SOCKET	socket;
	};

	/// <summary>
	/// クライアント配列
	/// </summary>
	std::vector<ClientData*> _clients;

	/// <summary>
	/// ポート番号
	/// </summary>
	unsigned short _port;

	/// <summary>
	/// サーバー処理が開始されているかどうか
	/// </summary>
	bool _isServerStart;

	/// <summary>
	/// クライアント接続待機スレッド
	/// </summary>
	std::thread _acceptThread;

	/// <summary>
	/// 受信したデータ
	/// </summary>
	std::vector<char*> _receivedData;

	/// <summary>
	/// 受信時に実行する処理 (char* 受信したデータ)
	/// </summary>
	std::function<void(char*)>	__recvFunc;

	/// <summary>
	/// クライアントの接続を待機し、接続された場合にスレッドを起動する
	/// </summary>
	void __acceptThread();

	/// <summary>
	/// クライアントからのデータを処理するスレッドのメイン関数
	/// </summary>
	/// <param name="client">対象クライアント情報のポインタ</param>
	void __recvThread(ClientData* client);

	/// <summary>
	/// ソケットを閉じる
	/// </summary>
	void __closeSocket();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="port">ポート番号</param>
	Server(const unsigned short port);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="port">ポート番号</param>
	/// <param name="recvFunc">受信時の処理</param>
	Server(const unsigned short port, std::function<void(char*)> recvFunc);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Server();

	/// <summary>
	/// サーバーを初期化/開始する処理
	/// </summary>
	/// <returns>正常に開始できたかどうか</returns>
	bool Start();

	/// <summary>
	/// 受信したメッセージを取得する処理
	/// </summary>
	/// <returns>受信したメッセージ</returns>
	std::vector<char*> getReceivedData();
};
