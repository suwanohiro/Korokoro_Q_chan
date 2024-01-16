#include "Character.h"

void Character::__updateDamageWait()
{
	if (getDamageWait() > 0) _damageWait--;
}

Character::Character(spAudioManager audioManager, spEffectManager effectManager)
	: GameObject()
	, GameObjectMotion()
	, _audioManager(audioManager)
	, _effectManager(effectManager)
	, _moveSpd(0, 0)
	, _HP(0)
	, _maxHP(0)
	, _damageWait(0)
	, _shotWait(0)
{
}

void Character::LateUpdate()
{
	if (!isActive()) return;

	GameObjectMotion::Update();
	__updateDamageWait();
}

void Character::Render()
{
	if (!isActive()) return;

	if (getDamageWait() % 4 >= 2) return;

	CRectangle rec = __getMotionRect();
	if (isReverse()) {
		const float work = rec.Right;
		rec.Right = rec.Left;
		rec.Left = work;
	}

	const Vector2 pos = getPosition() - __getScroll();
	getTexture()->Render(pos.x, pos.y, rec);
}
