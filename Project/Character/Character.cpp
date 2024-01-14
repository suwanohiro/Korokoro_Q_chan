#include "Character.h"

void Character::__updateDamageWait()
{
	if (getDamageWait() > 0) _damageWait--;
}

void Character::__updateMotion()
{
	__getMotion().AddTimer(CUtilities::GetFrameSecond());
	__setMotionRect();
}

Character::Character()
	: GameObject()
	, _moveSpd(0, 0)
	, _HP(0)
	, _maxHP(0)
	, _damageWait(0)
	, _motion()
{
}

void Character::LateUpdate()
{
	if (!isActive()) return;

	__updateMotion();
	__updateDamageWait();
}

void Character::Render(Vector2 correction)
{
	if (!isActive()) return;

	if (getDamageWait() % 4 >= 2) return;

	CRectangle rec = __getMotionRect();
	if (isReverse()) {
		const float work = rec.Right;
		rec.Right = rec.Left;
		rec.Left = work;
	}

	const Vector2 pos = getPosition() - correction;
	getTexture()->Render(pos.x, pos.y, rec);
}
