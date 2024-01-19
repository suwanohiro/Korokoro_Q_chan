#pragma once
#include "Mof.h"
#include "GameDefine.h"
#include "Audio.h"

class CMenu
{
private:
	
	bool         m_Menu;			//���j���[��ʂ��J����Ă��邩�̔���

	//�����̈ʒu�����̂��߂Ɏg�p����
	CRectangle  MenuStringRect;

	CTexture m_SelectTexture[3];

	int m_Select;					//���̃V�[����I��ł��邩

	CAudio* m_Audio;

public:
	CMenu();
	~CMenu();
	void Load();
	void Initialize();
	void Update(int& ChangeScene);
	void Render();
	void Release();

	void SetAudio(CAudio* audio) { m_Audio = audio; }

	//���j���[��ʂ��J����Ă��邩
	bool GetMenu() { return m_Menu; }
};

