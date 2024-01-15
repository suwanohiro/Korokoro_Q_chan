#include "./GameObjectMotion.hpp"

void GameObjectMotion::Update()
{
	__getMotion().AddTimer(CUtilities::GetFrameSecond());
	__setMotionRect();
}

GameObjectMotion::GameObjectMotion()
	: _motion()
	, _motionRect()
{
}
