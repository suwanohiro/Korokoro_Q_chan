#pragma once

#include "../Character.h"
#include "./PlayerStatus.hpp"
#include "./PlayerMotion.hpp"
#include "./PlayerShot/PlayerShot.hpp"

using spPlayerShotArray = spShotArray<spPlayerShot>;

class Player : public Character
{
private:
	bool _isJump;
	bool _isMoveX;
	bool _isMoveY;
	bool _isHit;
	bool _isWallMove;
	bool _isStageCollision;
	bool _isShot;

	spPlayerShotArray _shotArray;


	bool __updateMotion();
	void __updateKey();
	void __updateMove();
	void __updateJumpEnd();

	/// <summary>
	/// ‰æ–Ê‰º‚Ö—‰ºˆ—
	/// </summary>
	void __screenOutBottom();

	void __dead();

	void __fire();

	/// <summary>
	/// HP‰ñ•œ
	/// </summary>
	void __heelHP() { if (getHP() < getMaxHP()) updateHP(ADD_HP); }

	// ƒ‚[ƒVƒ‡ƒ“ŠÖ˜A
	PlayerMotion __getMotionNo() { return (PlayerMotion)__getMotion().GetMotionNo(); }
	void __changeMotion(PlayerMotion motion) { __getMotion().ChangeMotion((int)motion); }

	bool __isPlayerMove() { return getMoveSpd().x != 0 || (__isWallMove() && getMoveSpd().y != 0); }
	bool __isPlayerStop();

	bool __isJump() { return _isJump; }
	void __isJump(bool value) { _isJump = value; }

	bool __isHit() { return _isHit; }
	void __isHit(bool value) { _isHit = value; }

	bool __isWallMove() { return _isWallMove; }
	void __isWallMove(bool value) { _isWallMove = value; }

	bool __isStageCollision() { return _isStageCollision; }
	void __isStageCollision(bool value) { _isStageCollision = value; }

	bool __isShot() { return _isShot; }
	void __isShot(bool value) { _isShot = value; }

	spPlayerShotArray __getShotArray() { return _shotArray; }

public:
	Player(spAudioManager audioManager, spEffectManager effectManager);

	void Initialize(Vector2 initPos) override;
	void FixedUpdate(Vector2 scroll) override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
};

