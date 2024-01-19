#pragma once

#include "Mof.h"

class CEnemyShot {
private:
	//�G�̒e�摜�ւ̃|�C���^
	CTexture* m_Texture;

	//���W
	Vector2 m_Pos;
	//���x
	const float m_Spd;
	//�i�ޕ���
	Vector2 m_Advance;
	//�\���t���O
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

	//�e�̃e�N�X�`����ݒ�
	void SetTexture(CTexture* pt) { m_Texture = pt; }
	void SetShow(bool* bs) { m_bShow = bs; }

	CRectangle GetRect() 
	{
		return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Texture->GetWidth(), m_Pos.y + m_Texture->GetHeight());
	}
	bool GetShow(void) { return m_bShow; }
};
