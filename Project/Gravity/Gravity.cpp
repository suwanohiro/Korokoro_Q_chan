#include "Gravity.hpp"

void Gravity::addGravity(float& value)
{
	value += _gravityValue;
	if (value >= 20.0f) { value = 20.0f; }
}

void Gravity::addGravity(Vector2& value)
{
	value.y += _gravityValue;
	if (value.y >= 20.0f) { value.y = 20.0f; }
}
