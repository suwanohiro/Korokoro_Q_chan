#pragma once

#include "../../swnLibrary/swnLibrary.h"

using spCSpriteMotionController = std::shared_ptr<CSpriteMotionController>;

class GameObjectMotion
{
private:
	spCSpriteMotionController _motion;
	CRectangle _motionRect;

protected:
	void __createMotion(SpriteAnimationCreate anim) { _motion->Create(anim); };
	void __createMotion(LPSpriteAnimationCreate anim, int length) { _motion->Create(anim, length); }
	void __setMotion(spCSpriteMotionController value);
	spCSpriteMotionController __getMotion() { return _motion; }
	bool __isEndMotion();

	void __setMotionRect() { _motionRect = _motion->GetSrcRect(); }
	CRectangle __getMotionRect() { return _motionRect; }
	Vector2 __getMotionRectSize() { return Vector2(__getMotionRect().GetWidth(), __getMotionRect().GetHeight()); }

	void Update();

public:
	GameObjectMotion();
};

