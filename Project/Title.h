#pragma once
#include "Mof.h"
#include "Audio.h"


class CTitle
{
private:	
	CTexture	m_Texture;		//�^�C�g���̉摜
	int         m_Alpha;		//�t�F�[�h�p
	bool        m_Cange;		//��ʑJ�ڃt���O
	CTexture    m_TextTexure;	//�����摜
	int         m_TextAlpha;	//�����摜�̃A���t�@�l
	float		m_Tw;			//�摜�̉��̒���
	float       m_Th;			//�摜�̏c�̒���
	int         m_PlusRGB;		//�����摜�̐F�̕ϓ��l
	int			m_RGB;			//�����摜�̐F��RGB�l
	CTexture    m_BackTexture;  //�o�b�N�̉摜
	spCAudio		m_Audio;
	int			m_Volume;
public:
	CTitle();
	~CTitle();
	void Load(void);
	void Initialize(void);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	void SetAudio(spCAudio audio) {m_Audio = audio; }
};

