#include "Countdown.h"

/*
コンストラクタ
*/
Countdown::Countdown()
	: progressTime(0)
	, timeLimit(0)
	, remaining(0)
	, isProcess(false)
	, isRemaining(true)
{
}
/*
デストラクタ
*/
Countdown::~Countdown()
{
}

void Countdown::Initialize()
{
	progressTime = 0;
	timeLimit = 0;
	remaining = 0;
	isProcess = false;
	isRemaining = true;
}

/*
カウントダウン処理
*/
void Countdown::Update()
{
	// 実行中でなければ処理しない
	if (!isProcess) return;

	progressTime += CUtilities::GetFrameSecond();

	// 残り時間を計算する
	remaining = timeLimit - progressTime;

	if (remaining < 0) {
		remaining = 0;
		isRemaining = false;
	}
}

void Countdown::Render()
{
	CGraphicsUtilities::RenderString(850, 40, "残り%2.2f秒", remaining);
}
