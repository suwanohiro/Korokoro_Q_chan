#include "Item.h"

/* �R���X�g���N�^*/
CItem::CItem() :
	m_pos(),
	m_MoveY(0.0f),
	m_bShow(false),
	m_SrcRect()
{
}

/* �f�X�g���N�^*/
CItem::~CItem()
{
}

/* ������
����
[in]		px		X���W
[in]		py		Y���W
*/
void CItem::Initialize(float px, float py, int type)
{
	m_pos.x = px;
	m_pos.y = py;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_ItemType = (ItemType)type;
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim = {
		"�A�C�e��",0,0,40,40,
		TRUE,{{5,0,0}}
	};
	m_Motion.Create(anim);	
}

/* �X�V*/
void CItem::Update(void)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}
	
	//�d�͂ɂ��^���ɏ�����������
	m_Gravity.Gravity(m_MoveY);
	if (m_MoveY >= 10.0f)
	{
		m_MoveY = 10.0f;
	}
	m_pos.y += m_MoveY;
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/* �X�e�[�W�ƏՓ˂����ۂ̕␳����
����
[in]		oy		Y���܂��
*/
void CItem::CollisionStage(float oy)
{
	m_pos.y += oy;
	//�������̉����܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
}

/* �`��
����
[in]		wx		���[���h�̕ω�
[in]		wy		���[���h�̕ω�
*/
void CItem::Render(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}

	m_itemTexture->Render(m_pos.x - wx, m_pos.y - wy,m_SrcRect);
}

void CItem::RenderDebug(float wx, float wy)
{
	//��\��
	if (!m_bShow) return;

	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}

/* ���*/
void CItem::Release(void)
{
	m_Motion.Release();
}

/* �������`*/
CRectangle CItem::GetRect()
{
	//��\��
	if (!m_bShow)
	{
		return NULL;
	}

	return CRectangle(m_pos.x,m_pos.y, m_pos.x + m_SrcRect.GetWidth(), m_pos.y + m_SrcRect.GetHeight());
}
