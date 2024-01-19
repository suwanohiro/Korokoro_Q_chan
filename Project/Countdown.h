#pragma once

#include	"Mof.h"


class Countdown
{
private:
	int timeLimit;//制限時間
	float remaining;//残り時間
	float progressTime;//経過時間
	bool isProcess;//実行中かどうか
	bool isRemaining;//残り時間があるかどうか

public:
	Countdown();
	~Countdown();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// カウントダウンスタート
	/// </summary>
	void Start() { if (!isProcess) isProcess = true; }

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();

	/// <summary>
	/// カウントダウン時間を設定する
	/// </summary>
	/// <param name="cnt"></param>
	void SetCountdown(int cnt) { 
		// 実行中なら変更させない
		if (isProcess) return;

		timeLimit = cnt;
	}

	/// <summary>
	/// カウントダウン時間を取得する
	/// </summary>
	/// <returns></returns>
	float GetLimit() const { return timeLimit; }

	/// <summary>
	/// 残り時間があるかを取得する
	/// </summary>
	/// <returns>残り時間フラグ true:残り時間がある false:残り時間がない</returns>
	float GetRemaining() {
		return isRemaining;
	}
};