#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string>
#include <thread>
#include <vector>
#include <functional>
#include <winsock2.h>

class Socket
{
protected:
	/// <summary>
	/// エラー内容
	/// </summary>
	std::vector<char*>	_error;

	/// <summary>
	/// デバッグ情報
	/// </summary>
	std::vector<char*>	_debug;

	/// <summary>
	/// ソケット
	/// </summary>
	SOCKET				_tsock;

	/// <summary>
	/// エラー情報を追加
	/// </summary>
	/// <param name="msg">エラー文字列</param>
	void __addError(char* msg);

	/// <summary>
	/// デバッグ情報を追加
	/// </summary>
	/// <param name="msg">デバッグ文字列</param>
	void __addDebug(char* msg);

	/// <summary>
	/// Winsockを初期化する処理
	/// </summary>
	/// <returns>正常に初期化が完了したかどうか</returns>
	bool __initWinsock();

	/// <summary>
	/// ソケットを作成する
	/// </summary>
	/// <returns>ソケットの作成に成功したかどうか</returns>
	bool __makeSocket();

	/// <summary>
	/// ソケットを閉じる
	/// </summary>
	virtual void __closeSocket() = 0;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Socket();

	/// <summary>
	/// エラー情報を取得する
	/// </summary>
	/// <returns>エラー情報</returns>
	std::vector<char*> getErrors();

	/// <summary>
	/// デバッグ情報を取得する
	/// </summary>
	/// <returns>デバッグ情報</returns>
	std::vector<char*> getDebugs();
};

