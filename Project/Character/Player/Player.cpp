#include "Player.hpp"

//////////////////////////////
// 
// TODO : Player::Load未実装
// TODO : PlayerUI関連の移行作業
// 
//////////////////////////////

Player::Player(spAudioManager audioManager, spEffectManager effectManager)
	: Character(audioManager, effectManager)
{
}

void Player::Initialize(Vector2 initPos)
{
	Character::Initialize(initPos);

	__setMaxHP(Player_MaxHP);
	__setHP(getMaxHP());
	__setMoveSpd(0, 0);
	setReverse(false);

	__changeMotion(PlayerMotion::Wait);
}
