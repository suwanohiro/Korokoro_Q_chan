#pragma once

#include "../GameObject/GameObject.hpp"
#include "../Audio/AudioManager.hpp"
#include "../Gravity/Gravity.hpp"
#include "../Character/Shot/Shot.hpp"

template <typename T = spShot>
using spShotArray = std::vector<T>;

class Character : public GameObject
{
private:
	spAudioManager _audioManager;

	Vector2 _moveSpd;

	int _HP;
	int _maxHP;

	int _damageWait;

	CSpriteMotionController _motion;
	CRectangle _motionRect;

	spCTexture _shotTexture;

protected:
	spAudioManager __getAudioManager() { return _audioManager; }

	void __setMaxHP(int value) { _maxHP = value; }

	void __setMoveSpd(Vector2 value) { _moveSpd = value; }
	void __setMoveSpd(float x, float y) { _moveSpd = Vector2(x, y); }

	void __setDamageWait(int value) { _damageWait = value; }
	void __updateDamageWait();

	void __setMotion(CSpriteMotionController value) { _motion = value; }
	CSpriteMotionController __getMotion() { return _motion; }
	bool __isEndMotion() { return __getMotion().IsEndMotion(); }
	void __updateMotion();

	void __setMotionRect() { _motionRect = _motion.GetSrcRect(); }
	CRectangle __getMotionRect() { return _motionRect; }
	Vector2 __getMotionRectSize() { return Vector2(__getMotionRect().GetWidth(), __getMotionRect().GetHeight()); }

	void __setHP(int value) { _HP = value; }

	spCTexture __getShotspTexture() { return _shotTexture; }
	CTexture* __getShotTexture() { return __getShotspTexture().get(); }

public:
	Character(spAudioManager audioManager);

	virtual void LateUpdate() override;

	virtual void Render() override { Render(Vector2(0, 0)); };
	virtual void Render(Vector2 correction);

	void CollisionStage(float ox, float oy) { CollisionStage(Vector2(ox, oy)); };
	virtual void CollisionStage(Vector2 value) = 0;

	void updateHP(int value) { _HP += value; }
	int getHP() { return _HP; }
	int getMaxHP() { return _maxHP; }

	Vector2 getMoveSpd() { return _moveSpd; }
	int getDamageWait() { return _damageWait; }

	void setShotTexture(spCTexture value) { _shotTexture = value; }
};

template <typename T = spShot>
using spCharacter = std::shared_ptr<Character>;
