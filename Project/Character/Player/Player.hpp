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

// �U������
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
	/// �v���C���[�e�Ƃ̓����蔻�菈��
	/// </summary>
	/// <param name="enemy">�ΏۂƂȂ�G�v�f</param>
	/// <param name="isDamagedEnemy">�_���[�W�����ǂ��� (�G)</param>
	/// <returns>�����������ǂ���</returns>
	bool __collisionShot(spEnemy enemy, bool isDamagedEnemy);

	/// <summary>
	/// �G�̒e�Ƃ̓����蔻�菈��
	/// </summary>
	/// <param name="enemy">�ΏۂƂȂ�G�v�f</param>
	/// <param name="isDamagedEnemy">�_���[�W�����ǂ��� (�v���C���[)</param>
	/// <returns>�����������ǂ���</returns>
	bool __collisionEnemyShot(spEnemy enemy, bool isDamagedPlayer);

	/// <summary>
	/// �G�Ƃ̓����蔻�菈��
	/// </summary>
	/// <param name="enemy">�ΏۂƂȂ�G�v�f</param>
	/// <returns>�����������ǂ���</returns>
	bool __collisionEnemy(spEnemy enemy);

	/// <summary>
	/// �G�̋�`�Ǝ����̍U����`�œG���_���[�W
	/// </summary>
	/// <param name="enemy">�ΏۂƂȂ�G�v�f</param>
	/// <returns>�����������ǂ���</returns>
	bool __collisionAttack(spEnemy enemy);

	/// <summary>
	/// ��������
	/// </summary>
	void __deceleration();
	void __decelerationWall();

	void __gravity();

	/// <summary>
	/// ��ʉ��֗���������
	/// </summary>
	void __screenOutBottom();

	void __dead();

	void __fire();

	/// <summary>
	/// HP��
	/// </summary>
	void __heelHP() { if (getHP() < getMaxHP()) updateHP(ADD_HP); }

	// ���[�V�����֘A
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
	/// �ǈړ��ɕύX������
	/// </summary>
	/// <param name="direction">�U������</param>
	void ChangeWallMove(AttackDirections direction);

	bool CollisionEnemy(spEnemy enemy);

	CRectangle getHitBox();
	CRectangle getAttack2Box();
};

using spPlayer = std::shared_ptr<Player>;
