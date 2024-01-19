#include "Effect.h"

/* �R���X�g���N�^*/
CEffect::CEffect():
	m_effectTexture(NULL),
	m_Motion(),
	m_pos(0.0f,0.0f),
	m_bShow(false),
	m_SrcRect()
{
}

/* �f�X�g���N�^*/
CEffect::~CEffect()
{
}

/* �J�n
�p�����[�^����W������������
����
[in]		type		�^�C�v
*/
void CEffect::Initialize(Vector2 pos,int type)
{
	m_pos = pos;
	m_bShow = false;

	switch (type)
	{
		case EFC_DAMEGE:
		{
			SpriteAnimationCreate anim[] = {
				//�_���[�W
				{
					"�G�t�F�N�g",
					0,0,128,128,
					FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0}}
				},
			};
			m_Motion.Create(anim, 1);

			break;
		}
		case EFC_OFFENEMY:
		{
			SpriteAnimationCreate anim[] = {
				//�G����_���[�W
				{
					"�G�t�F�N�g",
					0,0,120,120,
					FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},
					{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},
					{3,11,0},{3,12,0},{3,13,0},{3,14,0},{3,15,0}}
				},
			};
			m_Motion.Create(anim, 1);

			break;
		}
		case EFC_OFFPLAYER:
		{
			SpriteAnimationCreate anim[] = {
				//�v���C���[����_���[�W
				{
					"�G�t�F�N�g",
					0,0,180,180,
					FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0},
					{3,5,0},{3,6,0},{3,7,0},{3,8,0},{3,9,0},{3,10,0},
					{3,0,1},{3,1,1},{3,2,1},{3,3,1},{3,4,1},
					{3,5,1},{3,6,1},{3,7,1},{3,8,1},{3,9,1},{3,10,1}}
				},
			};
			m_Motion.Create(anim, 1);

			break;
		}
	}
}

/* �J�n
���W��ݒ肵�ă��[�V�������J�n����
����
[in]		pos			X,Y���W
*/
void CEffect::Start(Vector2 pos)
{
	m_SrcRect = m_Motion.GetSrcRect();
	m_pos.x = pos.x - m_SrcRect.GetWidth() * 0.5f;
	m_pos.y = pos.y - m_SrcRect.GetHeight() * 0.5f;
	m_bShow = true;
	m_Motion.ChangeMotion(0);
}

void CEffect::Update(void)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}

	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	//�A�j���[�V�����̏I���Ŕ�\���ɂ���
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

void CEffect::Render(float wx, float wy)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}

	m_effectTexture->Render(m_pos.x - wx, m_pos.y - wy,m_SrcRect);
}

void CEffect::Release(void)
{
	m_Motion.Release();
}
