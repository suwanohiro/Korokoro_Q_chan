#pragma once

#include	"./swnLibrary/swnLibrary.h"


#include "./Audio/AudioManager.hpp"
#include "./Effect/EffectManager.hpp"

#include "./Scene/Scene_Base.hpp"
#include "./Scene/Scene_Game/Scene_Game.hpp"

class CGameApp : public CSingleGameApplication {
private:
	spAudioManager _audioManager;
	spEffectManager _effectManager;

	spScene_Base _scene;

public:
	CGameApp();
	virtual ~CGameApp(){	Release();	}
	virtual MofBool Initialize(void);
	virtual MofBool Update(void);
	virtual MofBool Render(void);
	virtual MofBool Release(void);
};
