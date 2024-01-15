#pragma once

#include "../Character.h"
#include "./PlayerStatus.hpp"

enum class PlayerMotion {
	Wait,
	Move,
	JumpStart,
	JumpEnd,
	Attack,
	Attack2,
	Damage,
	WallMove,
	Length
};

class Player : public Character
{
private:
	float _wallMove;

	void __changeMotion(PlayerMotion target) { __getMotion().ChangeMotion((int)target); }

public:
	Player(spAudioManager audioManager, spEffectManager effectManager);

	void Initialize(Vector2 initPos);
};

