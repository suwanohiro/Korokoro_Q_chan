#pragma once

#include	"Mof.h"
//ˆÚ“®‘¬“x
#define		PLAYERSHOT_SPEED		6
class CPlayerShot {
private:
	CTexture* m_pTexture;
	Vector2					m_Position;
	CSpriteMotionController m_ShotMotion;
	bool					m_bShow;
	bool					m_Reverse;
	CRectangle				m_SrcShotRect;
public:
	CPlayerShot();
	~CPlayerShot();
	void Initialize(void);
	void Fire(float px, float py, bool r);
	void Update(void);
	void Render(float wx);
	void RenderDebug(float wx);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow(void) { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }
	CRectangle GetRect() {
		if (m_Reverse) {
			return CRectangle(m_Position.x + m_SrcShotRect.GetWidth(), m_Position.y - (m_pTexture->GetHeight() * 0.5f),
				m_Position.x + (m_SrcShotRect.GetWidth() * 2), m_Position.y + (m_pTexture->GetHeight() * 0.5f));
		}
		else {
			return CRectangle(m_Position.x + m_SrcShotRect.GetWidth() + 150, m_Position.y - (m_pTexture->GetHeight() * 0.5f),
				m_Position.x + 360, m_Position.y + (m_pTexture->GetHeight() * 0.5f));
		}
	}
};