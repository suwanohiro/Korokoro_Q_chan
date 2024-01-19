#pragma once
#include "Mof.h"
#include "Audio.h"

//�I�ׂ�V�[����
#define SceneCount 4
class CStageSelect
{
private:
	CAudio*	m_Audio;
	int		m_Volume;

	CTexture m_Texture[SceneCount];				//�X�e�[�W�I�����摜
	CTexture m_NoSelectTexture;					//�I������Ă��Ȃ��Ƃ��̉摜
	int m_Select;								//�V�[����
	bool m_Change;								//�V�[�����ς�邩
	int m_Alpha;								//�N���[�Y�A�b�v�p

	CTexture   m_StageSelectText;				//StageSelect�����̉摜
	CTexture   m_BackTexture;

public:
	CStageSelect();
	~CStageSelect();
	void Load();
	void Initialize();
	void Update(int& ChangeScene);
	void Render();
	void RenderDebug();
	void Release();
	void SetAudio(CAudio* audio) { m_Audio = audio; }
};

