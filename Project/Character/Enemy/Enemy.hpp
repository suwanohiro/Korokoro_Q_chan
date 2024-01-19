#pragma once

#include "../Character.h"
#include "./EnemyShot/EnemyShot.hpp"
#include "./EnemyMotion.hpp"
#include "./EnemyStatus.hpp"

using spEnemyShotArray = spShotArray<spEnemyShot>;

class Enemy : public Character
{
private:
	bool _isMove;
	bool _isInScreen;

	spEnemyShotArray _shotArray;

protected:
	// ÉÇÅ[ÉVÉáÉìä÷òA
	EnemyMotion __getMotionNo() { return (EnemyMotion)__getMotion().GetMotionNo(); }
	void __changeMotion(EnemyMotion motion) { __getMotion().ChangeMotion((int)motion); }

	void __damage();

	bool __isMove() { return _isMove; }
	void __isMove(bool value) { _isMove = value; }

	bool __isInScreen() { return _isInScreen; }
	void __isInScreen(bool value) { _isInScreen = value; }


public:
	Enemy(spAudioManager audioManager, spEffectManager effectManager);

	virtual void Initialize(Vector2 initPos) override;
	virtual void FixedUpdate(Vector2 scroll) override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	void CollisionStage(Vector2 value) override;

	virtual void Damage(int value, bool IsReverse) override;

	// TODO : Enemy_getshotArray()ÇprotectedÇ…ñﬂÇ∑
	spEnemyShotArray getShotArray() { return _shotArray; };

	virtual void Attack() {};
};

using spEnemy = std::shared_ptr <Enemy>;
