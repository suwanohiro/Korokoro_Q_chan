#pragma once

#include "../swnLibrary/swnLibrary.h"

class Gravity
{
private:
	static inline const float _gravityValue = 0.3f;

public:
	static void addGravity(float& value);
	static void addGravity(Vector2& value);
};

