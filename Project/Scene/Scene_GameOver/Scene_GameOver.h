#pragma once

#include "../../swnLibrary/swnLibrary.h"
#include "../Scene_Base.hpp"

class Scene_GameOver : public Scene_Base
{
private:
	CTexture m_BackImage;

public:
	void Initialize();
	void Update();
	void Render();
	void Release();
};

