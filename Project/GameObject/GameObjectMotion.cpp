#include "./GameObjectMotion.hpp"

void GameObjectMotion::__setMotion(spCSpriteMotionController value)
{
	_motion = value;
	__setMotionRect();
}

bool GameObjectMotion::__isEndMotion()
{
	try {
		return _motion->IsEndMotion();
	}
	catch (...) {
		return false;
	}
}

void GameObjectMotion::Update()
{
	__getMotion()->AddTimer(CUtilities::GetFrameSecond());
	__setMotionRect();
}

GameObjectMotion::GameObjectMotion()
	: _motion(new CSpriteMotionController)
	, _motionRect()
{
}
