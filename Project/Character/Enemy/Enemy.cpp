#include "Enemy.hpp"

void Enemy::__damage()
{
	// ダメージ中でなければここで処理終了
	if (__getMotionNo() != EnemyMotion::Damage) return;

	if (__isEndMotion()) {
		__changeMotion(EnemyMotion::Move);

		if (getHP() <= 0) {
			setActive(false);

			// 死亡時処理
			// TODO : 爆発エフェクト等未実装の為、ここも未実装
		}

		const float move_x = (isReverse()) ? -3.0f : 3.0f;
		__setMoveSpd(move_x, getMoveSpd().y);
		return;
	}

	float move_x = getMoveSpd().x;

	if (move_x > 0) {
		move_x -= 0.2f;
		if (move_x < 0) move_x = 0;
	}
	else if (move_x < 0) {
		move_x += 0.2f;
		if (move_x < 0) move_x = 0;
	}
	// 値の変更がない場合はここで処理終了
	else return;

	// 値の変更を反映
	__setMoveSpd(move_x, getMoveSpd().y);
}

Enemy::Enemy()
	: Character()
	, _isMove(false)
	, _isInScreen(false)
{
}

bool Enemy::Load()
{
	return true;
}

void Enemy::Initialize(Vector2 initPos)
{
	Character::Initialize(initPos);
	__setMoveSpd(-3.0f, 0);
	setActive(true);
	setReverse(true);
	__setIsMove(false);
	__setHP(10);
	__setDamageWait(0);

	SpriteAnimationCreate anim[] = {
		{
			"移動",
			0,0,60,64,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"ダメージ",0,210,60,64,
			FALSE,{{20,0,0}}
		},
	};
	__getMotion().Create(anim, (int)EnemyMotion::Length);
}

void Enemy::Update()
{
	if (!isActive()) return;

	// ダメージ時の処理
	__damage();

	// SE関連処理
	// TODO : 未実装

	// 重力処理
	// TODO : 未実装
}

void Enemy::CollisionStage(Vector2 value)
{
	const Vector2 pos = getPosition();
	Vector2 move = getMoveSpd();

	setPosition(pos + value);

	const bool puddleTop = (value.y > 0 && move.y < 0);
	const bool puddleBottom = (value.y < 0 && move.y > 0);
	const bool puddleLeft = (value.x < 0 && move.x > 0);
	const bool puddleRight = (value.x > 0 && move.x < 0);

	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if (puddleTop || puddleBottom) move.y = 0;

	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if (puddleLeft || puddleRight) move.x *= -1;

	if (puddleLeft) setReverse(true);
	else if (puddleRight) setReverse(false);

	// 変更を反映
	__setMoveSpd(move);
}

void Enemy::Damage(int value, bool isReverse)
{
	Vector2 move = getMoveSpd();

	__setIsMove(false);
	updateHP(-value);
	__setDamageWait(60);
	move.x = (isReverse) ? -5.0f : 5.0f;
	setReverse(!isReverse);

	__changeMotion(EnemyMotion::Damage);

	// ダメージエフェクトを発生させる
	// ダメージSEを再生する

	// TODO : 未実装

	// 変更を反映
	__setMoveSpd(move);
}
