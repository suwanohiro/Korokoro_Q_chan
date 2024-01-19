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
	case PlayerMotion::Attack1:
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

void Player::__updateKey()
{
	// �ړ�����
	__inputMove();

	// �W�����v����
	__inputJump();

	// �U�� (1)
	__inputAttack1();

	// �U�� (2)
	__inputAttack2();

	// �ǈړ�
	__inputWallMove();
}

// �ړ�����
void Player::__inputMove()
{
	//�L�[�{�[�h�ړ�
	const bool leftMove = g_pInput->IsKeyHold((int)KeyContents::LEFTMOVE) && !_isWallMove;
	const bool rightMove = g_pInput->IsKeyHold((int)KeyContents::RIGHTMOVE) && !_isWallMove;

	// �ǂ�������͂���Ă��Ȃ���΂����ŏ����I��
	if (!leftMove && !rightMove) return;

	// �ǂ��炩�����͂���Ă����

	const float playerSpd = (leftMove) ? -PLAYER_SPEED : PLAYER_SPEED;

	__updateMoveSpd(playerSpd, 0);

	// �����͂̎��͔��]������
	isReverse(leftMove);

	__isMove(true, __isMove().y);

	const bool updateFlg = (leftMove) ? (getMoveSpd().x < -PLAYER_MAXSPEED) : (getMoveSpd().x > PLAYER_MAXSPEED);

	if (updateFlg) __updateMoveSpd(playerSpd, 0);
	
	const bool isMotionWait = __getMotionNo() == PlayerMotion::Wait;
	const bool isMotionWallMove = __getMotionNo() == PlayerMotion::WallMove;
	if (isMotionWait || isMotionWallMove) __changeMotion(PlayerMotion::Move);
}

// �W�����v����
void Player::__inputJump()
{
	//A�L�[�ŃV�����v
	//���ӓ_�F�󒆂ł��W�����v�ł��Ă��܂�

	const bool isKeyHold = g_pInput->IsKeyHold((int)KeyContents::JUMP);
	const bool isJump = isKeyHold && __isJump() && __isWallMove() && __isStageCollision();

	// �W�����v�\��ԂłȂ��Ȃ炱���ŏ����I��
	if (!isJump) return;

	__isJump(true);
	__isStageCollision(false);
	__updateMoveSpd(0, PLAYER_JUMP);

	__changeMotion(PlayerMotion::JumpStart);

	// �W�����vSE�Đ�
	__getAudioManager()->play(AudioTrack::SE_Player_Jump);
}

// �U�� (1)
void Player::__inputAttack1()
{
	const bool isKeyPush = g_pInput->IsKeyPush((int)KeyContents::ATTACK);
	const bool isAttack = isKeyPush && !__isWallMove() && __getShotWait() <= 0;

	if (!isAttack) return;

	__changeMotion(PlayerMotion::Attack1);
	__isShot(true);

	// �U��SE�Đ�
	__getAudioManager()->play(AudioTrack::SE_Player_Attack1);
}

// �U�� (2)
void Player::__inputAttack2()
{
	const bool isKeyPush = g_pInput->IsKeyPush((int)KeyContents::ATTACK2);
	const bool isAttack = isKeyPush && !__isWallMove();

	if (!isAttack) return;

	__changeMotion(PlayerMotion::Attack2);
	__getAudioManager()->play(AudioTrack::SE_Player_Attack2);
}

// �ǈړ�
void Player::__inputWallMove()
{
	//�ǂɍU�����������ď㉺�ɓ���
	const bool upMove = g_pInput->IsKeyHold((int)KeyContents::WALLUPMOVE);
	const bool downMove = g_pInput->IsKeyHold((int)KeyContents::WALLDOWNMOVE);
	const bool isWallMove = (upMove || downMove) && __isWallMove();

	if (!isWallMove) return;

	const float playerMove = (upMove) ? -Player_WallMove : Player_WallMove;
	__isMove(__isMove().x, true);
	__updateMoveSpd(0, playerMove);

	if (getMoveSpd().y < -1.0f) __setMoveSpd(getMoveSpd().x, -1.0f);
	if (getMoveSpd().y > 1.0f) __setMoveSpd(getMoveSpd().x, 1.0f);

	//TODO:�l�͕ς���@��ʏ�O�ɂ����Ɩ߂�
	if (getPosition().y < 0) setPosition(getPosition().x, 0);
}

bool Player::__collisionShot(spEnemy enemy, bool isDamagedEnemy)
{
	if (isDamagedEnemy) return false;

	struct {
		CRectangle Player;
		CRectangle PlayerShot;
		CRectangle PlayerAttack;
		CRectangle Enemy;
	} rect;

	rect.Enemy = enemy->getRect();

	rect.Player = getHitBox();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		spPlayerShot shot = __getShotArray()[cnt];
		rect.PlayerShot = shot->getRect();

		if (rect.PlayerShot.CollisionRect(rect.Enemy)) {
			enemy->Damage(PlayerShot_Power, isReverse());
			shot->isActive(false);
			break;
		}

		if (__getMotionNo() != PlayerMotion::Attack2) continue;

		//�G�̋�`�Ǝ����̍U����`�œG���_���[�W
		rect.PlayerAttack = getRect();

		// ������Ȃ���΂����ŏ����I��
		if (!rect.PlayerAttack.CollisionRect(rect.Enemy)) continue;

		enemy->Damage(PlayerShot_Power, isReverse());

		return true;
	}

	return false;
}

// Player::__collisionEnemyShot�͓G (Enemy) �Ɉړ�������
bool Player::__collisionEnemyShot(spEnemy enemy, bool isDamagedPlayer)
{
	// �_���[�W���Ȃ珈���I��
	if (isDamagedPlayer) return false;

	struct {
		CRectangle Player;
		CRectangle EnemyShot;
	} rect;

	rect.Player = getHitBox();

	for (int cnt = 0; cnt < enemy->getShotArray().size(); cnt++) {
		const spEnemyShot shot = enemy->getShotArray()[cnt];
		rect.EnemyShot = shot->getRect();

		// �������Ă��Ȃ���΃��[�v�����I��
		if (!rect.Player.CollisionRect(rect.EnemyShot)) continue;

		const bool isLeftHit = (rect.Player.Left < rect.EnemyShot.Left);

		Damage(Enemy_Power, isLeftHit);

		shot->isActive(false);

		return true;
	}

	return false;
}

bool Player::__collisionEnemy(spEnemy enemy)
{
	// �G���L����ԏo�Ȃ��Ȃ炱���ŏ����I��
	if (enemy->isActive()) return false;

	struct {
		CRectangle Player;
		CRectangle Enemy;
	} rect;

	rect.Player = getHitBox();
	rect.Enemy = enemy->getRect();

	// �������Ă��Ȃ���΂����ŏ����I��
	if (!rect.Player.CollisionRect(rect.Enemy)) return false;

	const bool isLeftHit = (rect.Player.Left < rect.Enemy.Left);
	
	Damage(Enemy_Power, isLeftHit);

	return true;
}

bool Player::__collisionAttack(spEnemy enemy)
{
	const bool isAttackAction = (__isAttack1() || __isAttack2());

	// �U�����łȂ��Ȃ炱���ŏ����I��
	if (!isAttackAction) return false;

	struct {
		CRectangle Player;
		CRectangle Enemy;
	} rect;

	rect.Player = getAttack2Box();

	rect.Enemy = enemy->getRect();

	// �������Ă��Ȃ���΂����ŏ����I��
	if (!rect.Player.CollisionRect(rect.Enemy)) return false;

	enemy->Damage(PlayerShot_Power, isReverse());
	return true;
}

// ��������
void Player::__deceleration()
{
	// �ړ����͂�����΂����ŏ����I��
	if (__isMove().x) return;

	const bool left = (getMoveSpd().x < 0);
	const bool right = (getMoveSpd().x > 0);

	// ���E�ǂ�����ړ����x���Ȃ����
	if (!left && !right) {
		if (__getMotionNo() == PlayerMotion::Move) __changeMotion(PlayerMotion::Wait);
		return;
	}

	const float playerSpd = (left) ? PLAYER_SPEED : -PLAYER_SPEED;
	__updateMoveSpd(playerSpd, 0);

	const bool isOutvalue = (left) ? (getMoveSpd().x > 0) : (getMoveSpd().x < 0);
	if (isOutvalue) __setMoveSpd(0, getMoveSpd().y);
}

void Player::__decelerationWall()
{
	const bool flg = !__isMove().y && __isWallMove();

	if (!flg) return;

	const float y = getMoveSpd().y;

	const bool moveUp = y > 0;
	const bool moveDown = y < 0;

	const float wallMove = (moveUp) ? -Player_WallMove : Player_WallMove;
	__updateMoveSpd(0, wallMove);

	const bool isOutValue = (moveUp) ? (y > 0) : (y < 0);
	if (isOutValue) __setMoveSpd(getMoveSpd().x, 0);
}

void Player::__gravity()
{
	// �ʏ�ړ��̎�
	if (!__isWallMove()) {
		// �d�͏���
		Vector2 moveSpd = getMoveSpd();
		Gravity::addGravity(moveSpd);
		__setMoveSpd(moveSpd);
		return;
	}

	// �ǈړ��̎�
	const float x = (isReverse()) ? -5.0f : 5.0f;
	__updateMoveSpd(x, 0);
}

void Player::__updateMove()
{
	// ��������
	__deceleration();

	// �������� (��)
	__decelerationWall();

	// __gravity();

	//�ǂɒ���t���Ă���Ƃ��ɓG�Ɠ��������Ƃ�
	if (__getMotionNo() == PlayerMotion::Damage && __isWallMove()) __isWallMove(false);
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
	, _isMove()
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
	isReverse(false);
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

	__gravity();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->LateUpdate();

		// �v�f��������ԂȂ�Ηv�f���폜����
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

void Player::CollisionStage(Vector2 value)
{
	updatePosition(value);

	const bool isPuddleTop = (value.y > 0 && getMoveSpd().y < 0);
	const bool isPuddleBottom = (value.y < 0 && getMoveSpd().y > 0);

	if (isPuddleTop || isPuddleBottom) __setMoveSpd(getMoveSpd().x, 0);

	if (isPuddleBottom && __isJump()) {
		__isJump(false);
		__isStageCollision(true);
		__changeMotion(PlayerMotion::JumpEnd);
	}

	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	const bool isPuddleLeft = (value.x < 0 && getMoveSpd().x > 0);
	const bool isPuddleRight = (value.x > 0 && getMoveSpd().x < 0);
	if (isPuddleLeft || isPuddleRight) __setMoveSpd(0, getMoveSpd().y);


	//�ǂɒ���t���Ă���Ƃ��ɍU���{�^���������ƕǂ��甍�����
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK2) && __isWallMove()) {
		__isWallMove(false);
		__changeMotion(PlayerMotion::JumpEnd);
	}

	//�U��2�̏ꍇ�U�����[�V�������I����Ă��璣��t��
	if (__isEndMotion() && __isAttack2() && __isWallMove()) {
		__changeMotion(PlayerMotion::WallMove);
	}
}

void Player::Damage(int value, bool IsReverse)
{
	if (!isAlive()) return;

	updateHP(-value);
	__setDamageWait(60);

	const float x = (IsReverse) ? -5.0f : 5.0f;
	__setMoveSpd(x, getMoveSpd().y);

	isReverse(!IsReverse);

	__changeMotion(PlayerMotion::Damage);

	// �G�t�F�N�g�֘A����
	const Vector2 effectPos = getPosition() + __getMotionRectSize() * 0.5f; 
	const EffectType effectType = (isAlive()) ? EffectType::DownPlayer : EffectType::Damage;
	__getEffectManager()->startEffect(effectType, effectPos);

	// SE�֘A����
	const AudioTrack audio = (isAlive()) ? AudioTrack::SE_Player_Dead : AudioTrack::SE_Player_Damage;
	__getAudioManager()->play(audio);
}

void Player::ChangeWallMove(AttackDirections direction)
{
	// �Y���̃��[�V�����łȂ��Ȃ炱���ŏ����I��
	if (!__isAttack2()) return;

	__isWallMove(true);

	const float x = (direction == AttackDirections::Left) ? -5.0f : 5.0f;
	__setMoveSpd(x, 0);
}

bool Player::CollisionEnemy(spEnemy enemy)
{
	//HP���Ȃ��Ȃ�Ɠ����蔻�肵�Ȃ�
	if (getHP() <= 0) {
		return false;
	}

	// �_���[�W�����ǂ��� (�G)
	bool isDamagedEnemy = (enemy->isActive() && enemy->getDamageWait() > 0);

	// �_���[�W�����ǂ��� (�v���C���[)
	bool isDamagedPlayer = (getDamageWait() > 0 || !enemy->isActive());

	// �v���C���[�e�ƓG�̔���
	if(__collisionShot(enemy, isDamagedEnemy)) return true;

	// TODO : �G���̏����Ƃ��Ĉړ�������ׂ�
	// �G�̒e�Ƃ̓����蔻��
	if(__collisionEnemyShot(enemy, isDamagedPlayer)) return true;

	// �G (�{��) �Ƃ̔���
	if(__collisionEnemy(enemy)) return true;

	// �U�����̃v���C���[ (�{��) �Ƃ̔���
	if (__collisionAttack(enemy)) return true;

	return false;
}

CRectangle Player::getHitBox()
{
	Vector2 base = getPosition() + Vector2(PLAYER_RECTDECREASE, PLAYER_RECTDECREASE);

	Vector2 after = getPosition() + __getMotionRectSize();
	after.x -= PLAYER_RECTDECREASE;
	if (__isAttack1() || __isAttack2()) after.x -= PLAYER_ATTACKWIDTH;

	return CRectangle(base, after);
}

CRectangle Player::getAttack2Box()
{
	CRectangle rec(0, 0, 0, 0);

	if (__isAttack2()) return CRectangle(0, 0, 0, 0);

	Vector2 base = getPosition();
	base.x += (isReverse()) ? -PLAYER_ATTACKWIDTH : __getMotionRectSize().x;
	base.y += PLAYER_RECTDECREASE;

	Vector2 after = getPosition();
	if (isReverse()) {
		after += __getMotionRectSize();
		after.x += PLAYER_ATTACKWIDTH;
	}

	return CRectangle(base, after);
}
