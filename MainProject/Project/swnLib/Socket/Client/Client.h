#pragma once

#include "../Socket.h"

class Client : public Socket
{
private:
	/// <summary>
	/// IPアドレス
	/// </summary>
	const char*			_ipAddress;

	/// <summary>
	/// ポート番号
	/// </summary>
	unsigned short		_port;

	/// <summary>
	/// 接続しているかどうか
	/// </summary>
	bool				_isConnect;

	/// <summary>
	/// 接続試行をしたかどうか
	/// </summary>
	bool				_isTryConnect;

	/// <summary>
	/// 接続試行スレッド
	/// </summary>
	std::thread			_tryConnect;

	/// <summary>
	/// 受信用スレッド
	/// </summary>
	std::thread			_receiveThread;

	/// <summary>
	/// 受信時に実行する処理 (char* 受信したデータ)
	/// </summary>
	std::function<void(char*)>	__recvFunc;

	/// <summary>
	/// 接続試行する処理 (スレッド動作用)
	/// </summary>
	void __tryConnectThread();

	/// <summary>
	/// 受信スレッドの処理
	/// </summary>
	void __recvThread();

	/// <summary>
	/// ソケットを閉じる
	/// </summary>
	void __closeSocket();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="ip">サーバーのIPアドレス</param>
	/// <param name="port">ポート番号</param>
	/// <param name="recvFunc">受信時の処理</param>
	Client(
		const char* ip, 
		const unsigned short port,
		std::function<void(char*)> recvFunc
	);
	~Client();

	/// <summary>
	/// サーバーに接続
	/// </summary>
	/// <returns>接続が成功したかどうか</returns>
	bool connectServer();

	/// <summary>
	/// 接続しているかどうかを取得する
	/// </summary>
	/// <returns>接続しているかどうか</returns>
	bool isConnect();

	/// <summary>
	/// データを送信
	/// </summary>
	/// <param name="data">送信するデータ</param>
	void sendData(char* data);
};

