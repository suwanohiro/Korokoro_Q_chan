#pragma once

#include "../Character.h"
#include "./EnemyShot/EnemyShot.hpp"
#include "./EnemyMotion.hpp"

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

	spEnemyShotArray __getShotArray() { return _shotArray; };

public:
	Enemy(spAudioManager audioManager, spEffectManager effectManager);

	virtual void Initialize(Vector2 initPos) override;
	virtual void FixedUpdate(Vector2 scroll) override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

	void CollisionStage(Vector2 value) override;

	void Damage(int value, bool isReverse);

	virtual void Attack() = 0;
};

