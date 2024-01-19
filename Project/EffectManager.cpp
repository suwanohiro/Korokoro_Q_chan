#include "EffectManager.h"

/* �R���X�g���N�^*/
CEffectManager::CEffectManager()
{
}

/* �f�X�g���N�^*/
CEffectManager::~CEffectManager()
{
}

/* �e�N�X�`���̓ǂݍ���*/
bool CEffectManager::Load(void)
{
	//�e�N�X�`���̓ǂݍ���
	char* name[] = {
		"effect01.png",
		"effect02.png",
		"effect03.png",
	};
	for (int i = 0; i < EFC_COUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}

    return false;
}

/* ������*/
void CEffectManager::Initialize(void)
{
	//�G�t�F�N�g�̊�b�ݒ�
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize({0, 0},j);
		}
	}

}

/* �J�n
���W���w�肵�ă��[�V�������J�n����
����
[in]        pos         x,y���W
[in]        type        �G�t�F�N�g�^�C�v
*/
CEffect* CEffectManager::Start(Vector2 pos, int type)
{
	for (int i = 0; i < EFFECTCOUNT; i++)
	{
		if (m_Effect[i][type].GetShow())
		{
			continue;
		}
		m_Effect[i][type].Start(pos);
		return &m_Effect[i][type];
	}

    return nullptr;
}

/* �X�V*/
void CEffectManager::Update(void)
{
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}

}

/* �`��*/
void CEffectManager::Render(float wx, float wy)
{
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(wx,wy);
		}
	}

}

/* ���*/
void CEffectManager::Release(void)
{
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}

}
