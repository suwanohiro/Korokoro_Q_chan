#pragma once

#include "Mof.h"

class CEnemyShot {
private:
	//敵の弾画像へのポインタ
	CTexture* m_Texture;

	//座標
	Vector2 m_Pos;
	//速度
	const float m_Spd;
	//進む方向
	Vector2 m_Advance;
	//表示フラグ
	bool m_bShow;


public:
	CEnemyShot();
	~CEnemyShot();
	void Initialize();
	void AdvSet(Vector2 pPos, float Ex, float Ey);
	void Update(float wx, float wy);
	void Render(float wx,float wy);
	void RenderDebug(float wx, float wy);
	void Release();

	//弾のテクスチャを設定
	void SetTexture(CTexture* pt) { m_Texture = pt; }
	void SetShow(bool* bs) { m_bShow = bs; }

	CRectangle GetRect() 
	{
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Texture->GetWidth(), m_Pos.y + m_Texture->GetHeight());
	}
	bool GetShow(void) { return m_bShow; }
};
