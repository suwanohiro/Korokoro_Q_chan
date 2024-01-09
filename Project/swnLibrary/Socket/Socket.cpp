#include "Socket.h"

// エラー情報を追加
void Socket::__addError(char* msg)
{
	_error.push_back(msg);
}

// デバッグ情報を追加
void Socket::__addDebug(char* msg)
{
	_debug.push_back(msg);
}

// Winsockの初期化
bool Socket::__initWinsock()
{
    WSAData wsaData;

    // Winsockの初期化を試みる
    bool result = (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0);

    if (result) __addDebug("WinSockの初期化に成功しました");
    else __addError("WinSockの初期化に失敗しました");

    return result;
}

bool Socket::__makeSocket()
{
    // ソケットを作成
    _tsock = socket(AF_INET, SOCK_STREAM, 0);
    
    // ソケットの作成に成功したかどうか
    bool result = (_tsock != INVALID_SOCKET);
    
    // ソケットの作成試行結果をそれぞれのログに追加する
    if (result) __addDebug("ソケットの作成に成功しました");
    else __addError("ソケットの作成に失敗しました");
    
    return result;
}

// コンストラクタ
Socket::Socket()
    : _tsock(INVALID_SOCKET)
{
}

// エラー情報を取得する
std::vector<char*> Socket::getErrors()
{
    return _error;
}

// デバッグ情報を取得する
std::vector<char*> Socket::getDebugs()
{
    return _debug;
}
