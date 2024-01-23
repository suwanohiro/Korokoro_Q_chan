#pragma once
#include "Mof.h"
#include "./swnLibrary/swnLibrary.h"

class CPlayerUI
{
private:
	CTexture				m_FrameTexture;
	CTexture				m_HPTexture;
	CTexture				m_MaxHPTexture;

	Vector2					rectPos;
	Vector2					rectSize;
	float					hppercent;

	CRectangle				m_MaxHPRect;
	CRectangle				m_HPRect;
	CRectangle				m_LifeRect;

	const int				m_MaxLife;
	int						m_Life;


	Vector2 getRecSize(const CRectangle& rec) {
		return Vector2(
			rec.Right - rec.Left,
			rec.Bottom - rec.Top
		);
	}

public:
	CPlayerUI();
	~CPlayerUI();
	bool Load(void);
	void Initializ(bool end);
	void UpdateHp(Vector2 pos, float scroll, int maxhp, int hp);
	void UpdateLife(bool& end);
	void Render(CTexture texture);
	void Release(void);
};
