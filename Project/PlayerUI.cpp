#include "PlayerUI.h"


CPlayerUI::CPlayerUI():
m_MaxLife(3),
m_Life(m_MaxLife){}

CPlayerUI::~CPlayerUI()
{
}

bool CPlayerUI::Load(void)
{
	//テクスチャ読み込み
	if (!m_FrameTexture.Load("Frame.png")) {
		return false;
	}
	if (!m_HPTexture.Load("HP.png")) {
		return false;
	}
	if (!m_MaxHPTexture.Load("HP02.png")) {
		return false;
	}
	return true;
}

void CPlayerUI::Initializ(bool end)
{
	m_MaxHPRect = CRectangle(0, 0, 532, 64);
	m_HPRect = CRectangle(0, 0, 532, 64);
	m_LifeRect = CRectangle(0, 0, 60, 64);
	
	if(end){ m_Life = m_MaxLife; }
}

void CPlayerUI::UpdateHp(int maxhp, int hp)
{
	//HPと最大HPの変化
	m_HPRect = CRectangle(0, 0, 532 * (hp * 0.01f), 64);
	m_MaxHPRect = CRectangle(0, 0, 532 * (maxhp * 0.01f), 64);
}

void CPlayerUI::UpdateLife(bool& end)
{
	//残機がなくなると終了
	if (m_Life <= 0) {
		end = true;
		return;
	}

	else{ m_Life--; }
	
}

void CPlayerUI::Render(CTexture texture)
{
	m_MaxHPTexture.Render(248, 20, m_MaxHPRect);
	m_HPTexture.Render(248, 20, m_HPRect);
	//フレームを上部に描画
	m_FrameTexture.Render(0, 0);
}

void CPlayerUI::Release(void)
{
	m_FrameTexture.Release();
	m_HPTexture.Release();
	m_MaxHPTexture.Release();
}
