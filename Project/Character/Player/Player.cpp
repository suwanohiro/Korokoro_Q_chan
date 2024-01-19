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
	case PlayerMotion::Attack1:
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

void Player::__updateKey()
{
	// 移動処理
	__inputMove();

	// ジャンプ処理
	__inputJump();

	// 攻撃 (1)
	__inputAttack1();

	// 攻撃 (2)
	__inputAttack2();

	// 壁移動
	__inputWallMove();
}

// 移動処理
void Player::__inputMove()
{
	//キーボード移動
	const bool leftMove = g_pInput->IsKeyHold((int)KeyContents::LEFTMOVE) && !_isWallMove;
	const bool rightMove = g_pInput->IsKeyHold((int)KeyContents::RIGHTMOVE) && !_isWallMove;

	// どちらも入力されていなければここで処理終了
	if (!leftMove && !rightMove) return;

	// どちらかが入力されていれば

	const float playerSpd = (leftMove) ? -PLAYER_SPEED : PLAYER_SPEED;

	__updateMoveSpd(playerSpd, 0);

	// 左入力の時は反転させる
	isReverse(leftMove);

	__isMove(true, __isMove().y);

	const bool updateFlg = (leftMove) ? (getMoveSpd().x < -PLAYER_MAXSPEED) : (getMoveSpd().x > PLAYER_MAXSPEED);

	if (updateFlg) __updateMoveSpd(playerSpd, 0);
	
	const bool isMotionWait = __getMotionNo() == PlayerMotion::Wait;
	const bool isMotionWallMove = __getMotionNo() == PlayerMotion::WallMove;
	if (isMotionWait || isMotionWallMove) __changeMotion(PlayerMotion::Move);
}

// ジャンプ処理
void Player::__inputJump()
{
	//Aキーでシャンプ
	//注意点：空中でもジャンプできてしまう

	const bool isKeyHold = g_pInput->IsKeyHold((int)KeyContents::JUMP);
	const bool isJump = isKeyHold && __isJump() && __isWallMove() && __isStageCollision();

	// ジャンプ可能状態でないならここで処理終了
	if (!isJump) return;

	__isJump(true);
	__isStageCollision(false);
	__updateMoveSpd(0, PLAYER_JUMP);

	__changeMotion(PlayerMotion::JumpStart);

	// ジャンプSE再生
	__getAudioManager()->play(AudioTrack::SE_Player_Jump);
}

// 攻撃 (1)
void Player::__inputAttack1()
{
	const bool isKeyPush = g_pInput->IsKeyPush((int)KeyContents::ATTACK);
	const bool isAttack = isKeyPush && !__isWallMove() && __getShotWait() <= 0;

	if (!isAttack) return;

	__changeMotion(PlayerMotion::Attack1);
	__isShot(true);

	// 攻撃SE再生
	__getAudioManager()->play(AudioTrack::SE_Player_Attack1);
}

// 攻撃 (2)
void Player::__inputAttack2()
{
	const bool isKeyPush = g_pInput->IsKeyPush((int)KeyContents::ATTACK2);
	const bool isAttack = isKeyPush && !__isWallMove();

	if (!isAttack) return;

	__changeMotion(PlayerMotion::Attack2);
	__getAudioManager()->play(AudioTrack::SE_Player_Attack2);
}

// 壁移動
void Player::__inputWallMove()
{
	//壁に攻撃が当たって上下に動く
	const bool upMove = g_pInput->IsKeyHold((int)KeyContents::WALLUPMOVE);
	const bool downMove = g_pInput->IsKeyHold((int)KeyContents::WALLDOWNMOVE);
	const bool isWallMove = (upMove || downMove) && __isWallMove();

	if (!isWallMove) return;

	const float playerMove = (upMove) ? -Player_WallMove : Player_WallMove;
	__isMove(__isMove().x, true);
	__updateMoveSpd(0, playerMove);

	if (getMoveSpd().y < -1.0f) __setMoveSpd(getMoveSpd().x, -1.0f);
	if (getMoveSpd().y > 1.0f) __setMoveSpd(getMoveSpd().x, 1.0f);

	//TODO:値は変える　画面上外にいくと戻す
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

		//敵の矩形と自分の攻撃矩形で敵がダメージ
		rect.PlayerAttack = getRect();

		// 当たらなければここで処理終了
		if (!rect.PlayerAttack.CollisionRect(rect.Enemy)) continue;

		enemy->Damage(PlayerShot_Power, isReverse());

		return true;
	}

	return false;
}

// Player::__collisionEnemyShotは敵 (Enemy) に移動させる
bool Player::__collisionEnemyShot(spEnemy enemy, bool isDamagedPlayer)
{
	// ダメージ中なら処理終了
	if (isDamagedPlayer) return false;

	struct {
		CRectangle Player;
		CRectangle EnemyShot;
	} rect;

	rect.Player = getHitBox();

	for (int cnt = 0; cnt < enemy->getShotArray().size(); cnt++) {
		const spEnemyShot shot = enemy->getShotArray()[cnt];
		rect.EnemyShot = shot->getRect();

		// 当たっていなければループ処理終了
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
	// 敵が有効状態出ないならここで処理終了
	if (enemy->isActive()) return false;

	struct {
		CRectangle Player;
		CRectangle Enemy;
	} rect;

	rect.Player = getHitBox();
	rect.Enemy = enemy->getRect();

	// 当たっていなければここで処理終了
	if (!rect.Player.CollisionRect(rect.Enemy)) return false;

	const bool isLeftHit = (rect.Player.Left < rect.Enemy.Left);
	
	Damage(Enemy_Power, isLeftHit);

	return true;
}

bool Player::__collisionAttack(spEnemy enemy)
{
	const bool isAttackAction = (__isAttack1() || __isAttack2());

	// 攻撃中でないならここで処理終了
	if (!isAttackAction) return false;

	struct {
		CRectangle Player;
		CRectangle Enemy;
	} rect;

	rect.Player = getAttack2Box();

	rect.Enemy = enemy->getRect();

	// 当たっていなければここで処理終了
	if (!rect.Player.CollisionRect(rect.Enemy)) return false;

	enemy->Damage(PlayerShot_Power, isReverse());
	return true;
}

// 減速処理
void Player::__deceleration()
{
	// 移動入力があればここで処理終了
	if (__isMove().x) return;

	const bool left = (getMoveSpd().x < 0);
	const bool right = (getMoveSpd().x > 0);

	// 左右どちらも移動速度がなければ
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
	// 通常移動の時
	if (!__isWallMove()) {
		// 重力処理
		Vector2 moveSpd = getMoveSpd();
		Gravity::addGravity(moveSpd);
		__setMoveSpd(moveSpd);
		return;
	}

	// 壁移動の時
	const float x = (isReverse()) ? -5.0f : 5.0f;
	__updateMoveSpd(x, 0);
}

void Player::__updateMove()
{
	// 減速処理
	__deceleration();

	// 減速処理 (壁)
	__decelerationWall();

	// __gravity();

	//壁に張り付いているときに敵と当たったとき
	if (__getMotionNo() == PlayerMotion::Damage && __isWallMove()) __isWallMove(false);
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

	__gravity();

	for (int cnt = 0; cnt < __getShotArray().size(); cnt++) {
		const spPlayerShot work = __getShotArray()[cnt];
		work->LateUpdate();

		// 要素が無効状態ならば要素を削除する
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

	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	const bool isPuddleLeft = (value.x < 0 && getMoveSpd().x > 0);
	const bool isPuddleRight = (value.x > 0 && getMoveSpd().x < 0);
	if (isPuddleLeft || isPuddleRight) __setMoveSpd(0, getMoveSpd().y);


	//壁に張り付いているときに攻撃ボタンを押すと壁から剥がれる
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK2) && __isWallMove()) {
		__isWallMove(false);
		__changeMotion(PlayerMotion::JumpEnd);
	}

	//攻撃2の場合攻撃モーションが終わってから張り付く
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

	// エフェクト関連処理
	const Vector2 effectPos = getPosition() + __getMotionRectSize() * 0.5f; 
	const EffectType effectType = (isAlive()) ? EffectType::DownPlayer : EffectType::Damage;
	__getEffectManager()->startEffect(effectType, effectPos);

	// SE関連処理
	const AudioTrack audio = (isAlive()) ? AudioTrack::SE_Player_Dead : AudioTrack::SE_Player_Damage;
	__getAudioManager()->play(audio);
}

void Player::ChangeWallMove(AttackDirections direction)
{
	// 該当のモーションでないならここで処理終了
	if (!__isAttack2()) return;

	__isWallMove(true);

	const float x = (direction == AttackDirections::Left) ? -5.0f : 5.0f;
	__setMoveSpd(x, 0);
}

bool Player::CollisionEnemy(spEnemy enemy)
{
	//HPがなくなると当たり判定しない
	if (getHP() <= 0) {
		return false;
	}

	// ダメージ中かどうか (敵)
	bool isDamagedEnemy = (enemy->isActive() && enemy->getDamageWait() > 0);

	// ダメージ中かどうか (プレイヤー)
	bool isDamagedPlayer = (getDamageWait() > 0 || !enemy->isActive());

	// プレイヤー弾と敵の判定
	if(__collisionShot(enemy, isDamagedEnemy)) return true;

	// TODO : 敵側の処理として移動させるべき
	// 敵の弾との当たり判定
	if(__collisionEnemyShot(enemy, isDamagedPlayer)) return true;

	// 敵 (本体) との判定
	if(__collisionEnemy(enemy)) return true;

	// 攻撃中のプレイヤー (本体) との判定
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
