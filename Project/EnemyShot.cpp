#include "EnemyShot.h"

CEnemyShot::CEnemyShot() :
m_Texture(NULL),
m_Pos(Vector2(0,0)),
m_Spd(4.0f),
m_Advance(Vector2(0,0)),
m_bShow(false){
}

CEnemyShot::~CEnemyShot()
{
}

void CEnemyShot::Initialize()
{
	//������
	m_Pos = Vector2(0.0f, 0.0f);
	m_Advance = Vector2(0.0f, 0.0f);
	m_bShow = false;

}

void CEnemyShot::AdvSet(Vector2 pPos, float Ex, float Ey)
{
	m_bShow = true;
	
	//�e�̏����ʒu
	m_Pos.x = Ex;
	m_Pos.y = Ey;

	//�v���C���[���狅�ւ̃x�N�g�����v�Z
	m_Advance.x = pPos.x - Ex;
	m_Advance.y = pPos.y - Ey;

	//�x�N�g���̐��K��
	float length = sqrt(m_Advance.x * m_Advance.x + m_Advance.y * m_Advance.y);
	m_Advance.x /= length;
	m_Advance.y /= length;
}

void CEnemyShot::Update(float wx, float wy)
{
	//�e�𔭎�
	m_Pos.x += m_Advance.x * m_Spd;
	m_Pos.y += m_Advance.y * m_Spd;

	//�X�N���[����
	float sw = wx + CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	float sh = wy + CGraphicsUtilities::GetGraphics()->GetTargetHeight();
	
	//��ʊO�ŏ���
	if (m_Pos.x + m_Texture->GetWidth() < wx || sw < m_Pos.x ||
			m_Pos.y + m_Texture->GetHeight() < wy || sh < m_Pos.y)
	{
		m_bShow = false;
	}

}

void CEnemyShot::Render(float wx, float wy)
{
	if (!m_bShow) {
		return;
	}
	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy);
}

void CEnemyShot::RenderDebug(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
}

void CEnemyShot::Release()
{
	m_Texture->Release();
}
