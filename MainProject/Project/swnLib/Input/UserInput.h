#pragma once

#include "Mof.h"
#include "KeyInput.h"
#include "MouseInput.h"

class UserInput
	: public KeyInput
	, public MouseInput
{
private:

public:
	static bool isHold() = delete;
	static bool isPull() = delete;
	static bool isPush() = delete;
	static bool isWheelMove() = delete;
};
