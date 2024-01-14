#include "Shot.hpp"

Shot::Shot()
	: GameObject()
	, _speed(0)
{
}

void Shot::Initialize(Vector2 initPos)
{
	GameObject::Initialize(initPos);
	setActive(false);
}

void Shot::Render(Vector2 w)
{
	if (!isActive()) return;

	const Vector2 pos = getPosition();
	const Vector2 drowPos = pos - w;
	getTexture()->Render(drowPos.x, drowPos.y);
}

void Shot::Fire(Vector2 playerPos)
{
	setActive(true);

	setPosition(playerPos);
}
