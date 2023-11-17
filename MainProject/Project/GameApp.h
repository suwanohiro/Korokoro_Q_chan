#pragma once

#include	"Mof.h"

class CGameApp : public CSingleGameApplication {
private:

public:
	CGameApp(){}

	virtual ~CGameApp(){	Release();	}

	virtual MofBool Initialize(void);

	virtual MofBool Update(void);

	virtual MofBool Render(void);

	virtual MofBool Release(void);
};
