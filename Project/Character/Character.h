#pragma once

#include "../GameObject/GameObject.hpp"
#include "../GameObject/GameObjectMotion.hpp"
#include "../Audio/AudioManager.hpp"
#include "../Effect/EffectManager.hpp"
#include "../Gravity/Gravity.hpp"
#include "../Character/Shot/Shot.hpp"

template <typename T = spShot>
using spShotArray = std::vector<T>;

class Character : public GameObject, public GameObjectMotion
{
private:
	spAudioManager _audioManager;
	spEffectManager _effectManager;

	Vector2 _moveSpd;

	int _HP;
	int _maxHP;

	int _damageWait;

	int _shotWait;

	spCTexture _shotTexture;

protected:
	spAudioManager __getAudioManager() { return _audioManager; }
	spEffectManager __getEffectManager() { return _effectManager; }

	void __setMaxHP(int value) { _maxHP = value; }

	void __setMoveSpd(Vector2 value) { _moveSpd = value; }
	void __setMoveSpd(float x, float y) { _moveSpd = Vector2(x, y); }
	void __updateMoveSpd(Vector2 value) { _moveSpd += value; }
	void __updateMoveSpd(float x, float y) { __updateMoveSpd(Vector2(x, y)); }

	void __setDamageWait(int value) { _damageWait = value; }
	void __updateDamageWait();

	void __setHP(int value) { _HP = value; }

	int __getShotWait() { return _shotWait; }
	void __setShotWait(int value) { _shotWait = value; }
	void __updateShotWait(int value) { _shotWait += value; }

	spCTexture __getShotspTexture() { return _shotTexture; }
	CTexture* __getShotTexture() { return __getShotspTexture().get(); }

public:
	Character(spAudioManager audioManager, spEffectManager effectManager);

	virtual void LateUpdate() override;

	virtual void Render() override;

	void CollisionStage(float ox, float oy) { CollisionStage(Vector2(ox, oy)); };
	virtual void CollisionStage(Vector2 value) = 0;

	virtual void Damage(int value, bool IsReverse) = 0;

	/// <summary>
	/// 生存しているかどうか
	/// </summary>
	bool isAlive() { return getHP() > 0; }

	void updateHP(int value) { _HP += value; }
	int getHP() { return _HP; }
	int getMaxHP() { return _maxHP; }

	Vector2 getMoveSpd() { return _moveSpd; }
	int getDamageWait() { return _damageWait; }

	void setShotTexture(spCTexture value) { _shotTexture = value; }
};

using spCharacter = std::shared_ptr<Character>;
