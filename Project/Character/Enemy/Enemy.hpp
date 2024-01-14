#pragma once

#include "../Character.h"
#include "./EnemyShot/EnemyShot.hpp"

enum class EnemyMotion {
	Move,
	Damage,
	Length
};

using spEnemyShotArray = spShotArray<spEnemyShot>;

class Enemy : public Character
{
private:
	bool _isMove;
	bool _isInScreen;

	spEnemyShotArray _shotArray;

protected:
	// ÉÇÅ[ÉVÉáÉìä÷òA
	EnemyMotion __getMotionNo() { return EnemyMotion::Length; }
	void __changeMotion(EnemyMotion motion) { __getMotion().ChangeMotion((int)motion); }

	void __damage();

	void __setIsMove(bool value) { _isMove = value; }
	bool __isMove() { return _isMove; }

	void __setIsInScreen(bool value) { _isInScreen = value; }
	bool __isInScreen() { return _isInScreen; }

	spEnemyShotArray __getShotArray() { return _shotArray; };

public:
	Enemy();

	bool Load() override;
	virtual void Initialize(Vector2 initPos) override;
	virtual void Update() override;

	void CollisionStage(Vector2 value) override;

	void Damage(int value, bool isReverse);

	virtual void Attack() = 0;
};

