#pragma once

#include	"Effect.h"

//�Ǘ��G�t�F�N�g�̐�
#define		EFFECTCOUNT		5

class CEffectManager
{
private:
	//�G�t�F�N�g
	CEffect		m_Effect[EFFECTCOUNT][EFC_COUNT];
	//�G�t�F�N�g�摜
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

