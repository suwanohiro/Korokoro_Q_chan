#pragma once
#include	"AudioCtrl.h"

enum tag_Audio
{
	Audio_TitleBGM,				//�^�C�g��BGM
	Audio_GameOverBGM,			//�Q�[���I�[�o�[BGM
	Audio_GameClearBGM,			//�Q�[���N���ABGM
	Audio_GameContinueBGM,		//�Q�[���R���e�j���[BGM
	Audio_StageBGM,				//�X�e�[�WBGM

	Audio_Button,				//�{�^���N���b�NSE
	Audio_Select,				//�I��SE

	Audio_PlayerMove,			//�v���C���[�ړ�SE
	Audio_PlayerJump,			//�v���C���[�W�����vSE
	Audio_PlayerAttack_1,		//�v���C���[�U��1SE
	Audio_PlayerAttack_2,		//�v���C���[�U��2SE
	Audio_PlayerDamege,			//�v���C���[�_���[�WSE
	Audio_PlayerDead,			//�v���C���[���SSE

	Audio_EnemyMove,			//�G�ړ�SE
	Audio_EnemyAttack,			//�G�U��SE
	Audio_EnemyDamege,			//�G�_���[�WSE
	Audio_EnemyDead,			//�G���SSE

	Audio_Heel,					//��SE

	Audio_Count,
};

class CAudio
{
private:
	std::vector<CAudioCtrl*> m_Audio;
	int m_Volume;

public:
	bool Load();
	void SetVolume(int volume);
	void Initialize();
	void Play(tag_Audio tAudio, bool flg = false);
	bool IsPlay(tag_Audio tAudio);
	void Stop(tag_Audio tAudio);
	float GetVolume();
	void Release();
};

