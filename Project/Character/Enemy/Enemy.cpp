#include "Enemy.hpp"

void Enemy::__damage()
{
	// �_���[�W���łȂ���΂����ŏ����I��
	if (__getMotionNo() != EnemyMotion::Damage) return;

	if (__isEndMotion()) {
		__changeMotion(EnemyMotion::Move);

		if (getHP() <= 0) {
			setActive(false);

			// ���S������
			// TODO : �����G�t�F�N�g���������ׁ̈A������������
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
	// �l�̕ύX���Ȃ��ꍇ�͂����ŏ����I��
	else return;

	// �l�̕ύX�𔽉f
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
			"�ړ�",
			0,0,60,64,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"�_���[�W",0,210,60,64,
			FALSE,{{20,0,0}}
		},
	};
	__getMotion().Create(anim, (int)EnemyMotion::Length);
}

void Enemy::Update()
{
	if (!isActive()) return;

	// �_���[�W���̏���
	__damage();

	// SE�֘A����
	// TODO : ������

	// �d�͏���
	// TODO : ������
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

	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (puddleTop || puddleBottom) move.y = 0;

	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (puddleLeft || puddleRight) move.x *= -1;

	if (puddleLeft) setReverse(true);
	else if (puddleRight) setReverse(false);

	// �ύX�𔽉f
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

	// �_���[�W�G�t�F�N�g�𔭐�������
	// �_���[�WSE���Đ�����

	// TODO : ������

	// �ύX�𔽉f
	__setMoveSpd(move);
}
