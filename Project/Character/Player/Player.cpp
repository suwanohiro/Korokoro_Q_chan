#include "Player.hpp"

//////////////////////////////
// 
// TODO : Player::Load未実装
// TODO : PlayerUI関連の移行作業
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
		// モーション再生中ならここで処理終了
		if (!__isEndMotion()) break;

		__changeMotion(PlayerMotion::Wait);
		__isHit(false);
		isChangedMotion = true;
		break;

	case PlayerMotion::Damage:
		// モーション再生中ならここで処理終了
		if (!__isEndMotion()) break;

		__changeMotion(PlayerMotion::Wait);
		isChangedMotion = true;
		break;

	default:
		break;
	}

	return isChangedMotion;
}

// TODO : 未実装
void Player::__updateKey()
{
}

// TODO : 未実装
void Player::__updateMove()
{
}

void Player::__updateJumpEnd()
{
	const bool isTouchGround = (getPosition().y + __getMotionRectSize().y >= __getScreenSize().y);

	// 地面に触れていない状態ならここで処理終了
	if (!isTouchGround) return;

	const float y = __getScreenSize().y - __getMotionRectSize().y;
	updatePosition(0, y);

	__setMoveSpd(getMoveSpd().x, 0);

	// ジャンプ状態でないならここで処理終了
	if (!__isJump()) return;

	__isJump(false);
	__changeMotion(PlayerMotion::JumpEnd);
}

// 画面下へ落下時処理
void Player::__screenOutBottom()
{
	const bool isOutBottom = getPosition().y >= __getScreenSize().y;
	const bool isDead = (isOutBottom && isAlive());

	// 生存状態ならここで処理終了
	if (!isDead) return;

	// 死亡時処理
	__dead();
}

void Player::__dead()
{
	__setHP(0);

	// 爆発エフェクトを発生させる
	const Vector2 effectPos = getPosition() + __getMotionRectSize() * 0.5f;
	__getEffectManager()->startEffect(EffectType::DownPlayer, effectPos);

	// 死亡SE再生
	__getAudioManager()->play(AudioTrack::SE_Player_Dead);
}

void Player::__fire()
{
	//弾の発射
	const bool fireable = (__getShotWait() <= 0);

	// 発射インターバル時間中なら
	if (!fireable) {
		__updateShotWait(-1);
		__isShot(false);
		return;
	}

	// 発射できない状態ならここで処理終了
	if (!__isShot()) return;

	__setShotWait(PlayerShot_Wait);

	spPlayerShot work(new PlayerShot);
	work->Initialize(getPosition());

	Vector2 firePos = getPosition();
	if (isReverse()) firePos.x += __getMotionRectSize().x * 0.5f;

	work->Fire(firePos, isReverse());

	__getShotArray().push_back(work);

	// 最大HPを減らす
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

	// モーション変更が無ければupdateKey実行
	if (!__updateMotion()) __updateKey();

	// 移動更新
	__updateMove();

	// 座標更新
	updatePosition(getMoveSpd());

	// 移動SE再生
	if (__isPlayerMove()) __getAudioManager()->play(AudioTrack::SE_Player_Move, true);
	else if (__isPlayerStop()) __getAudioManager()->stop(AudioTrack::SE_Player_Move);

	// プレイヤー弾の更新処理
	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->Update();
	}

	// HP回復
	__heelHP();

	// 画面下へ落下時処理
	__screenOutBottom();

	// ジャンプ終了時処理
	__updateJumpEnd();
}

void Player::LateUpdate()
{
	if (!isActive()) return;

	Character::LateUpdate();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->LateUpdate();

		// エフェクト要素が無効状態ならば要素を削除する
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
