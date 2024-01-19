#pragma once

#include	"Effect.h"

//管理エフェクトの数
#define		EFFECTCOUNT		5

class CEffectManager
{
private:
	//エフェクト
	CEffect		m_Effect[EFFECTCOUNT][EFC_COUNT];
	//エフェクト画像
	CTexture	m_Texture[EFC_COUNT];
public:
	CEffectManager();
	~CEffectManager();
	bool Load(void);
	void Initialize(void);
	CEffect* Start(Vector2 pos, int type);
	void Update(void);
	void Render(float wx, float wy);
	void Release(void);
};

