#include "EnemyShot.hpp"

EnemyShot::EnemyShot()
	: Shot()
{
	__setSpeed(4.0f);
	setActive(false);
}

void EnemyShot::Initialize(Vector2 initPos)
{
	Shot::Initialize(initPos);
	__setVector(0, 0);
}

void EnemyShot::Update(Vector2 w)
{
	Vector2 pos = getPosition();

	//弾を発射
	const Vector2 spd = Vector2(__getSpeed(), __getSpeed());
	pos += (__getVector() * spd);

	//スクリーン幅
	Vector2 screenSize = getScreenSize();

	//画面外で消去
	const Vector2 work = pos + getTextureSize();
	const bool isOusScreen_x = (work.x < w.x || screenSize.x < pos.x);
	const bool isOutScreen_y = (work.y < w.y || screenSize.y < pos.y);
	const bool isOutScreen = (isOusScreen_x || isOutScreen_y);

	if (isOutScreen) setActive(false);

	// 変更を反映
	setPosition(pos);
}

void EnemyShot::Fire(Vector2 playerPos, Vector2 vector)
{
	Shot::Fire(playerPos);

	//プレイヤーから球へのベクトルを計算
	Vector2 vec = playerPos - vector;

	//ベクトルの正規化
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= length;
	vec.y /= length;

	// 変更を反映
	__setVector(vec);
}
