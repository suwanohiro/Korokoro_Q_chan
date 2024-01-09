#include "Client.h"

// 接続試行する処理 (スレッド動作用)
void Client::__tryConnectThread()
{
    // ソケットの作成に失敗したら処理終了
    if (!__makeSocket()) return;

    struct sockaddr_in tmp_addr;
    memset(&tmp_addr, 0, sizeof(struct sockaddr_in));
    tmp_addr.sin_family = AF_INET;
    tmp_addr.sin_port = htons(_port);
    tmp_addr.sin_addr.s_addr = inet_addr(_ipAddress);

    // サーバーに接続
    __addDebug("接続試行を開始しました");
    if (connect(_tsock, (struct sockaddr*)&tmp_addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        __addError("接続に失敗しました");
        __closeSocket();
        return;
    }

    __addDebug("接続に成功しました");
    sendData("test");

    // 受信用スレッドを開始してバックグラウンドで実行
    _receiveThread = std::thread(&Client::__recvThread, this);
    _receiveThread.detach();

    // 接続状態を更新
    _isConnect = true;
}

// 受信スレッドの処理
void Client::__recvThread()
{
    while (true)
    {
        char* msg;

        // データを受信
        int s = recv(_tsock, (char*)&msg, sizeof(msg), 0);
        if (s <= 0) {
            // 接続終了時の処理
            break;
        }

        // 受信時の処理を実行
        __recvFunc(msg);
    }

    /// スレッド終了後、ソケットを閉じてWinsockをクリーンアップ
    __closeSocket();
}

// ソケットを閉じる
void Client::__closeSocket()
{
    // 未接続状態ならばここで処理終了
    if (!_isConnect) return;

    // ソケットを閉じる
    closesocket(_tsock);
    __addDebug("ソケットを閉じました");

    // WinSockのクリーンアップ
    WSACleanup();
    __addDebug("WinSockをクリーンアップしました");

    // 接続状態を更新
    _isConnect = false;

}

// コンストラクタ
Client::Client(
        const char* ip,
        unsigned short port,
        std::function<void(char*)> recvFunc
    )
    : _isConnect(false)
{
    // IPアドレス・ポート番号を設定する
    _ipAddress = ip;
    _port = port;

    // 受信時の処理を設定する
    __recvFunc = recvFunc;
}

// デストラクタ
Client::~Client() {
    // ソケットを閉じる
    __closeSocket();

    if (!_isTryConnect) return;

    _tryConnect.join();
}

// サーバーに接続
bool Client::connectServer()
{
    // 接続中なら処理終了
    if (isConnect()) {
        __addError("接続中のため接続処理を中断しました");
        return false;
    }

    __addDebug("接続処理を開始しました");

    _isTryConnect = true;

    // WinSockの初期化
    if (!__initWinsock()) return false;

    _tryConnect = std::thread(&Client::__tryConnectThread, this);
    // _tryConnect.detach();

    return true;
}

// 接続しているかどうかを取得する
bool Client::isConnect()
{
    return _isConnect;
}


// データを送信
void Client::sendData(char* data) {
    // 接続中でなければここで処理終了
    if (!_isConnect) return;

    // サーバーにデータを送信
    send(_tsock, (char*)&data, sizeof(data), 0);
}
