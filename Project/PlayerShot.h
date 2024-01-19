#pragma once

#include	"Mof.h"
//ˆÚ“®‘¬“x
#define		PLAYERSHOT_SPEED		6
class CPlayerShot {
private:
	CTexture*				m_pTexture;
	Vector2					m_Position;
	bool					m_bShow;
	bool					m_Reverse;
public:
	CPlayerShot();
	~CPlayerShot();
	void Initialize(void);
	void Fire(float px,float py, bool r);
	void Update(void);
	void Render(float wx);
	void RenderDebug(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	void SetShow(bool bs){ m_bShow = bs; }
	CRectangle GetRect(){ return CRectangle(m_Position.x,m_Position.y,m_Position.x + m_pTexture->GetWidth(),m_Position.y + m_pTexture->GetHeight()); }
};