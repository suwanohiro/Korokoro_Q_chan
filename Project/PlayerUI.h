#pragma once
#include "Mof.h"


class CPlayerUI
{
private:
	CTexture				m_FrameTexture;
	CTexture				m_HPTexture;
	CTexture				m_MaxHPTexture;

	CRectangle				m_MaxHPRect;
	CRectangle				m_HPRect;
	CRectangle				m_LifeRect;

	const int				m_MaxLife;
	int						m_Life;

public:
	CPlayerUI();
	~CPlayerUI();
	bool Load(void);
	void Initializ(bool end);
	void UpdateHp(int maxhp, int hp);
	void UpdateLife(bool& end);
	void Render(CTexture texture);
	void Release(void);
};
