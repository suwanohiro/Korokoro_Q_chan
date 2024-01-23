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
	rectPos = Vector2(0, 15);
	rectSize = Vector2(120, 7.5);

	rectPos.x = (g_pGraphics->GetTargetWidth() / 2) - (rectSize.x / 2);

	m_MaxHPRect = CRectangle(rectPos, rectPos + rectSize);
	m_HPRect = CRectangle(rectPos, rectPos + rectSize);
	
	if(end){ m_Life = m_MaxLife; }
}

void CPlayerUI::UpdateHp(Vector2 pos, float scroll, int maxhp, int hp)
{
	//HPと最大HPの変化

	hppercent = (hp * 0.01f);

	rectPos = pos;
	rectPos.x -= scroll;
	rectPos.y -= 20;

	Vector2 hprec = rectPos + Vector2(rectSize.x * hppercent, rectSize.y);
	Vector2 maxhprec = rectPos + Vector2(rectSize.x * (maxhp * 0.01f), rectSize.y);

	m_HPRect = CRectangle(rectPos, hprec);
	m_MaxHPRect = CRectangle(rectPos, maxhprec);
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
	// m_MaxHPTexture.Render(248, 20, m_MaxHPRect);
	// m_HPTexture.Render(248, 20, m_HPRect);
	//フレームを上部に描画
	// m_FrameTexture.Render(0, 0);
	Vector2 base(0, 0);
	Vector2 size = Vector2(
		g_pGraphics->GetTargetWidth(),
		45
	);

	CRectangle recbk(base, size);

	CGraphicsUtilities::RenderFillRect(recbk, getRGB(WebColor::black));



	CRectangle rec = m_MaxHPRect;
	rec.Expansion(3, 3);

	float maxhpsize = getRecSize(m_MaxHPRect).x;
	float hpsize = getRecSize(m_HPRect).x;
	float percent = (hpsize / maxhpsize) * 100;

	unsigned long color = getRGB(WebColor::lightgreen);

	if (percent < 50) color = getRGB(WebColor::yellow);
	if (percent < 30) color = getRGB(WebColor::lightcoral);

	CGraphicsUtilities::RenderFillRect(rec, getRGB(WebColor::darkgray));
	CGraphicsUtilities::RenderFillRect(m_MaxHPRect, getRGB(WebColor::gray));
	CGraphicsUtilities::RenderFillRect(m_HPRect, color);
}

void CPlayerUI::Release(void)
{
	m_FrameTexture.Release();
	m_HPTexture.Release();
	m_MaxHPTexture.Release();
}
