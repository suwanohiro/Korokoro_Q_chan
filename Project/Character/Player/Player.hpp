#pragma once

#include "../Character.h"
#include "./PlayerStatus.hpp"
#include "./PlayerMotion.hpp"
#include "./PlayerShot/PlayerShot.hpp"

#include "../Enemy/Enemy.hpp"

using spPlayerShotArray = spShotArray<spPlayerShot>;

enum class KeyContents {
	LEFTMOVE = MOFKEY_LEFT,
	RIGHTMOVE = MOFKEY_RIGHT,
	ATTACK = MOFKEY_S,
	ATTACK2 = MOFKEY_D,
	JUMP = MOFKEY_A,
	WALLUPMOVE = MOFKEY_UP,
	WALLDOWNMOVE = MOFKEY_DOWN
};

struct MoveFlg {
	bool x = false;
	bool y = false;

	MoveFlg(bool _x = false, bool _y = false) {
		x = _x;
		y = _y;
	}
};

// 攻撃方向
enum class AttackDirections {
	Left,
	Right
};

class Player : public Character
{
private:
	bool _isJump;
	MoveFlg _isMove;
	bool _isHit;
	bool _isWallMove;
	bool _isStageCollision;
	bool _isShot;

	spPlayerShotArray _shotArray;


	bool __updateMotion();
	void __updateMove();
	void __updateJumpEnd();

	void __updateKey();
	void __inputMove();
	void __inputJump();
	void __inputAttack1();
	void __inputAttack2();
	void __inputWallMove();

	/// <summary>
	/// プレイヤー弾との当たり判定処理
	/// </summary>
	/// <param name="enemy">対象となる敵要素</param>
	/// <param name="isDamagedEnemy">ダメージ中かどうか (敵)</param>
	/// <returns>当たったかどうか</returns>
	bool __collisionShot(spEnemy enemy, bool isDamagedEnemy);

	/// <summary>
	/// 敵の弾との当たり判定処理
	/// </summary>
	/// <param name="enemy">対象となる敵要素</param>
	/// <param name="isDamagedEnemy">ダメージ中かどうか (プレイヤー)</param>
	/// <returns>当たったかどうか</returns>
	bool __collisionEnemyShot(spEnemy enemy, bool isDamagedPlayer);

	/// <summary>
	/// 敵との当たり判定処理
	/// </summary>
	/// <param name="enemy">対象となる敵要素</param>
	/// <returns>当たったかどうか</returns>
	bool __collisionEnemy(spEnemy enemy);

	/// <summary>
	/// 敵の矩形と自分の攻撃矩形で敵がダメージ
	/// </summary>
	/// <param name="enemy">対象となる敵要素</param>
	/// <returns>当たったかどうか</returns>
	bool __collisionAttack(spEnemy enemy);

	/// <summary>
	/// 減速処理
	/// </summary>
	void __deceleration();
	void __decelerationWall();

	void __gravity();

	/// <summary>
	/// 画面下へ落下時処理
	/// </summary>
	void __screenOutBottom();

	void __dead();

	void __fire();

	/// <summary>
	/// HP回復
	/// </summary>
	void __heelHP() { if (getHP() < getMaxHP()) updateHP(ADD_HP); }

	// モーション関連
	PlayerMotion __getMotionNo() { return (PlayerMotion)__getMotion().GetMotionNo(); }
	void __changeMotion(PlayerMotion motion) { __getMotion().ChangeMotion((int)motion); }

	bool __isPlayerMove() { return getMoveSpd().x != 0 || (__isWallMove() && getMoveSpd().y != 0); }
	bool __isPlayerStop();

	bool __isJump() const { return _isJump; }
	void __isJump(bool value) { _isJump = value; }

	bool __isHit() const { return _isHit; }
	void __isHit(bool value) { _isHit = value; }

	bool __isWallMove() const { return _isWallMove; }
	void __isWallMove(bool value) { _isWallMove = value; }

	bool __isStageCollision() const { return _isStageCollision; }
	void __isStageCollision(bool value) { _isStageCollision = value; }

	bool __isShot() const { return _isShot; }
	void __isShot(bool value) { _isShot = value; }

	MoveFlg __isMove() const { return _isMove; }
	void __isMove(MoveFlg value) { _isMove = value; }
	void __isMove(bool x, bool y) { _isMove = MoveFlg(x, y); }

	spPlayerShotArray __getShotArray() const { return _shotArray; }

	bool __isAttack1() { return (__getMotionNo() == PlayerMotion::Attack1); }
	bool __isAttack2() { return (__getMotionNo() == PlayerMotion::Attack2); }


public:
	Player(spAudioManager audioManager, spEffectManager effectManager);

	void Initialize(Vector2 initPos) override;
	void FixedUpdate(Vector2 scroll) override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;

	void CollisionStage(Vector2 value) override;

	void Damage(int value, bool IsReverse) override;

	/// <summary>
	/// 壁移動に変更させる
	/// </summary>
	/// <param name="direction">攻撃方向</param>
	void ChangeWallMove(AttackDirections direction);

	bool CollisionEnemy(spEnemy enemy);

	CRectangle getHitBox();
	CRectangle getAttack2Box();
};

using spPlayer = std::shared_ptr<Player>;
