#include "Player.hpp"

//////////////////////////////
// 
// TODO : Player::Load–¢À‘•
// TODO : PlayerUIŠÖ˜A‚ÌˆÚsì‹Æ
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
