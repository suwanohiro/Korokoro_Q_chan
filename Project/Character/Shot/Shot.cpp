#include "Shot.hpp"

Shot::Shot()
	: GameObject()
	, _speed(0)
{
}

void Shot::Initialize(Vector2 initPos)
{
	GameObject::Initialize(initPos);
	isActive(false);
}

void Shot::Fire(Vector2 playerPos)
{
	isActive(true);

	setPosition(playerPos);
}
