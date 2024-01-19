#include "Gravity.h"

CGravity::CGravity():
m_Gravity(0.3f)
{
}

CGravity::~CGravity()
{
}

void CGravity::Gravity(float& sy)
{
	sy += m_Gravity;
	if (sy >= 20.0f) { sy = 20.0f; }
}
