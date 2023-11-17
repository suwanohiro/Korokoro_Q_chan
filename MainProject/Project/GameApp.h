#pragma once

#include	"Mof.h"
#include	"swnLib/swnLib.h"
#include "RenderMap/RenderMap.h"

class CGameApp : public CSingleGameApplication {
private:
	std::unique_ptr<RenderMap> _renderMap;

public:
	CGameApp(){}

	virtual ~CGameApp(){	Release();	}

	virtual MofBool Initialize(void);

	virtual MofBool Update(void);

	virtual MofBool Render(void);

	virtual MofBool Release(void);
};
