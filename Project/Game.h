#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
//�������ύX�_
#include	"Menu.h"
#include	"EffectManager.h"
#include	"Audio.h"
#include	"Countdown.h"


class CGame {
private:
	//�X�e�[�W
	CStage		m_Stage;
	//�G�t�F�N�g
	CEffectManager m_EffectManager;
	//���j���[
	CMenu		m_Menu;
	//�T�E���h
	spCAudio		m_Audio;
	//�J�E���g�_�E��
	Countdown	m_Countdown;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(int stage);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	void SetAudio(spCAudio audio) {
		m_Audio = audio;
	}
};
