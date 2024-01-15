#pragma once

#include "../swnLibrary/swnLibrary.h"

class GameObjectMotion
{
private:
	CSpriteMotionController _motion;
	CRectangle _motionRect;

protected:
	void __setMotion(CSpriteMotionController value) { _motion = value; }
	CSpriteMotionController __getMotion() { return _motion; }
	bool __isEndMotion() { return __getMotion().IsEndMotion(); }

	void __setMotionRect() { _motionRect = _motion.GetSrcRect(); }
	CRectangle __getMotionRect() { return _motionRect; }
	Vector2 __getMotionRectSize() { return Vector2(__getMotionRect().GetWidth(), __getMotionRect().GetHeight()); }

	void Update();
};

