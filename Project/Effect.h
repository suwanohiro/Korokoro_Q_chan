#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

enum tag_EFFECT {
	EFC_DAMEGE,			//ダメージ
	EFC_OFFENEMY,		//やられエネミー
	EFC_OFFPLAYER,		//やられプレイヤー

	EFC_COUNT,
};

class CEffect {
private:
	CTexture* m_effectTexture;
	CSpriteMotionController	m_Motion;
	Vector2					m_pos;
	bool					m_bShow;
	CRectangle				m_SrcRect;
public:
	CEffect();
	~CEffect();
	void Initialize(Vector2 pos, int type);
	void Start(Vector2 pos);
	void Update(void);
	void Render(float wx, float wy);
	void Release(void);

	void SetTexture(CTexture* et) { m_effectTexture = et; }
	bool GetShow(void) { return m_bShow; }
};

