#include "Enemy.hpp"

void Enemy::__damage()
{
	// �_���[�W���łȂ���΂����ŏ����I��
	if (__getMotionNo() != EnemyMotion::Damage) return;

	// �I���őҋ@�ɖ߂�
	if (__isEndMotion()) {
		// TODO : �ύX�悪Move�ƂȂ��Ă��邪�ҋ@����Ȃ����m�F
		// TODO : -> Move�ȊO�̃��[�V�������������߈ꎞ�I�[�u�Ƃ���Move����
		__changeMotion(EnemyMotion::Move);

		if (getHP() <= 0) {
			isActive(false);

			// ���S������
			const Vector2 effectPos = getPosition() + __getMotionRectSize() * 0.5f;
			__getEffectManager()->startEffect(EffectType::DownEnemy, effectPos);

			// TODO : ������return���K�v���m�F
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

Enemy::Enemy(spAudioManager audioManager, spEffectManager effectManager)
	: Character(audioManager, effectManager)
	, _isMove(false)
	, _isInScreen(false)
{
}

void Enemy::Initialize(Vector2 initPos)
{
	Character::Initialize(initPos);
	__setMoveSpd(-3.0f, 0);
	isActive(true);
	setReverse(true);
	__isMove(false);
	__setHP(10);
	__setDamageWait(0);

	// TODO : �G�̃A�j���[�V�����𐳎��Ȃ��̂֕ύX������
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

void Enemy::FixedUpdate(Vector2 scroll)
{
	if (!isActive()) return;

	Character::FixedUpdate(scroll);

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spEnemyShot work = __getShotArray()[cnt];
		work->FixedUpdate(scroll);
	}
}

void Enemy::Update()
{
	if (!isActive()) return;

	// �_���[�W���̏���
	__damage();

	//�ړ�SE�𗬂�
	const bool isPlay = __getAudioManager()->isPlay(AudioTrack::SE_Enemy_Move);
	if (__isMove() && !isPlay) __getAudioManager()->play(AudioTrack::SE_Enemy_Move);
	else if (!__isMove()) __getAudioManager()->stop(AudioTrack::SE_Enemy_Dead);

	// �d�͏���
	Gravity::addGravity(getMoveSpd());
}

void Enemy::LateUpdate()
{
	if (!isActive()) return;

	Character::LateUpdate();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spEnemyShot work = __getShotArray()[cnt];
		work->LateUpdate();

		// �G�t�F�N�g�v�f��������ԂȂ�Ηv�f���폜����
		if (!work->isActive()) __getShotArray().erase(__getShotArray().begin() + cnt);
	}
}

void Enemy::Render()
{
	if (!isActive()) return;

	Character::Render();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spEnemyShot work = __getShotArray()[cnt];
		work->Render();
	}
}

void Enemy::Release()
{
	Character::Release();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spEnemyShot work = __getShotArray()[cnt];
		work->Release();
	}
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

	__isMove(false);
	updateHP(-value);
	__setDamageWait(60);
	move.x = (isReverse) ? -5.0f : 5.0f;
	setReverse(!isReverse);

	__changeMotion(EnemyMotion::Damage);

	// �_���[�W�G�t�F�N�g�𔭐�������
	const Vector2 effectPos = getPosition() + __getMotionRectSize() * 0.5f;
	__getEffectManager()->startEffect(EffectType::Damage, effectPos);

	// �_���[�WSE���Đ�����
	__getAudioManager()->play(AudioTrack::SE_Enemy_Damage);


	// �ύX�𔽉f
	__setMoveSpd(move);
}
