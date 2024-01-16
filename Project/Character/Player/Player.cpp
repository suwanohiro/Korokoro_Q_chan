#include "Player.hpp"

//////////////////////////////
// 
// TODO : Player::Load������
// TODO : PlayerUI�֘A�̈ڍs���
// 
//////////////////////////////

bool Player::__updateMotion()
{
	bool isChangedMotion = false;

	PlayerMotion motion = __getMotionNo();

	switch (motion)
	{
	case PlayerMotion::Attack:
	case PlayerMotion::Attack2:
	case PlayerMotion::JumpEnd:
		// ���[�V�����Đ����Ȃ炱���ŏ����I��
		if (!__isEndMotion()) break;

		__changeMotion(PlayerMotion::Wait);
		__isHit(false);
		isChangedMotion = true;
		break;

	case PlayerMotion::Damage:
		// ���[�V�����Đ����Ȃ炱���ŏ����I��
		if (!__isEndMotion()) break;

		__changeMotion(PlayerMotion::Wait);
		isChangedMotion = true;
		break;

	default:
		break;
	}

	return isChangedMotion;
}

// TODO : ������
void Player::__updateKey()
{
}

// TODO : ������
void Player::__updateMove()
{
}

void Player::__updateJumpEnd()
{
	const bool isTouchGround = (getPosition().y + __getMotionRectSize().y >= __getScreenSize().y);

	// �n�ʂɐG��Ă��Ȃ���ԂȂ炱���ŏ����I��
	if (!isTouchGround) return;

	const float y = __getScreenSize().y - __getMotionRectSize().y;
	updatePosition(0, y);

	__setMoveSpd(getMoveSpd().x, 0);

	// �W�����v��ԂłȂ��Ȃ炱���ŏ����I��
	if (!__isJump()) return;

	__isJump(false);
	__changeMotion(PlayerMotion::JumpEnd);
}

// ��ʉ��֗���������
void Player::__screenOutBottom()
{
	const bool isOutBottom = getPosition().y >= __getScreenSize().y;
	const bool isDead = (isOutBottom && isAlive());

	// ������ԂȂ炱���ŏ����I��
	if (!isDead) return;

	// ���S������
	__dead();
}

void Player::__dead()
{
	__setHP(0);

	// �����G�t�F�N�g�𔭐�������
	const Vector2 effectPos = getPosition() + __getMotionRectSize() * 0.5f;
	__getEffectManager()->startEffect(EffectType::DownPlayer, effectPos);

	// ���SSE�Đ�
	__getAudioManager()->play(AudioTrack::SE_Player_Dead);
}

void Player::__fire()
{
	//�e�̔���
	const bool fireable = (__getShotWait() <= 0);

	// ���˃C���^�[�o�����Ԓ��Ȃ�
	if (!fireable) {
		__updateShotWait(-1);
		__isShot(false);
		return;
	}

	// ���˂ł��Ȃ���ԂȂ炱���ŏ����I��
	if (!__isShot()) return;

	__setShotWait(PlayerShot_Wait);

	spPlayerShot work(new PlayerShot);
	work->Initialize(getPosition());

	Vector2 firePos = getPosition();
	if (isReverse()) firePos.x += __getMotionRectSize().x * 0.5f;

	work->Fire(firePos, isReverse());

	__getShotArray().push_back(work);

	// �ő�HP�����炷
	if (__getShotArray().size() >= PLAYERSHOT_COUNT) __setMaxHP(getHP());
	updateHP(-10);
}

bool Player::__isPlayerStop()
{
	const bool isStopX = (!__isWallMove() && getMoveSpd().x == 0);
	const bool isStopY = (getMoveSpd().y == 0);
	return (!__isStageCollision() || isStopX || isStopY || (!__isWallMove() && __isJump()));
}

Player::Player(spAudioManager audioManager, spEffectManager effectManager)
	: Character(audioManager, effectManager)
	, _isJump(false)
	, _isMoveX(false)
	, _isMoveY(false)
	, _isHit(false)
	, _isWallMove(false)
	, _isStageCollision(false)
	, _isShot(false)
{
}

void Player::Initialize(Vector2 initPos)
{
	Character::Initialize(initPos);

	__setMaxHP(Player_initMaxHP);
	__setHP(getMaxHP());
	__setMoveSpd(0, 0);
	setReverse(false);
	__isJump(false);

	__changeMotion(PlayerMotion::Wait);
}

void Player::FixedUpdate(Vector2 scroll)
{
	if (!isActive()) return;

	Character::FixedUpdate(scroll);

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->FixedUpdate(scroll);
	}
}

void Player::Update()
{
	if (!isActive()) return;

	// ���[�V�����ύX���������updateKey���s
	if (!__updateMotion()) __updateKey();

	// �ړ��X�V
	__updateMove();

	// ���W�X�V
	updatePosition(getMoveSpd());

	// �ړ�SE�Đ�
	if (__isPlayerMove()) __getAudioManager()->play(AudioTrack::SE_Player_Move, true);
	else if (__isPlayerStop()) __getAudioManager()->stop(AudioTrack::SE_Player_Move);

	// �v���C���[�e�̍X�V����
	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->Update();
	}

	// HP��
	__heelHP();

	// ��ʉ��֗���������
	__screenOutBottom();

	// �W�����v�I��������
	__updateJumpEnd();
}

void Player::LateUpdate()
{
	if (!isActive()) return;

	Character::LateUpdate();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->LateUpdate();

		// �G�t�F�N�g�v�f��������ԂȂ�Ηv�f���폜����
		if (!work->isActive()) __getShotArray().erase(__getShotArray().begin() + cnt);
	}
}

void Player::Render()
{
	if (!isActive()) return;

	Character::Render();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->Render();
	}
}

void Player::Release()
{
	Character::Release();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->Release();
	}
}
