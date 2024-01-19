#include "EnemyShot.hpp"

EnemyShot::EnemyShot()
	: Shot()
{
	__setSpeed(4.0f);
	isActive(false);
}

void EnemyShot::Initialize(Vector2 initPos)
{
	Shot::Initialize(initPos);
	__setVector(0, 0);
}

void EnemyShot::Update()
{
	const Vector2 scroll = __getScroll();
	Vector2 pos = getPosition();

	//�e�𔭎�
	const Vector2 spd = Vector2(__getSpeed(), __getSpeed());
	pos += (__getVector() * spd);

	//�X�N���[����
	Vector2 screenSize = __getScreenSize();

	//��ʊO�ŏ���
	const Vector2 work = pos + getTextureSize();
	const bool isOusScreen_x = (work.x < scroll.x || screenSize.x < pos.x);
	const bool isOutScreen_y = (work.y < scroll.y || screenSize.y < pos.y);
	const bool isOutScreen = (isOusScreen_x || isOutScreen_y);

	if (isOutScreen) isActive(false);

	// �ύX�𔽉f
	setPosition(pos);
}

void EnemyShot::Fire(Vector2 playerPos, Vector2 vector)
{
	Shot::Fire(playerPos);

	//�v���C���[���狅�ւ̃x�N�g�����v�Z
	Vector2 vec = playerPos - vector;

	//�x�N�g���̐��K��
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= length;
	vec.y /= length;

	// �ύX�𔽉f
	__setVector(vec);
}
