#pragma once
#include "Mof.h"

enum BGM
{
	BGM_Title,
	BGM_Select,
	BGM_Game,
	BGM_GameOver,
	BGM_GameClear,
	BGM_GameContinue,
	SE_Select,

	BGM_Count
};

enum SE
{
	Player_Damege,
	Player_Dead,
	Player_Attack1,
	Player_Attack2,
	Enemy_Damege,
	Enemy_Dead,
	Enemy_Attack,

	SE_Count
};

class CAudioCtrl
{
private:
	CSoundBuffer	m_Source;											//�����v�f
	std::string		m_AudioFolder;									//�ǂݍ��݃t�H���_
	float			m_Volume;											//�~���[�g���ۑ��p�{�����[�� (0.0f�`1.0f)
	bool			m_bMute;											//�~���[�g��Ԃ��ǂ���

	void			SetMute();										//�~���[�g�ݒ�

public:
	CAudioCtrl() :
		m_Source(),
		m_AudioFolder("Audio/"),
		m_bMute(false),
		m_Volume(1.0f)
	{
	}

	void			ChangeMute();									//�~���[�g�ύX�i���]�j
	void			ChangeMute(bool flg);							//�~���[�g�ύX�i���ڎw��j

	bool			Load(std::string Path);							//�ǂݍ���

	bool			IsMute();										//�~���[�g��Ԃ�

	bool			IsPlay();										//�Đ�����

	bool			IsLoop();										//���[�vON��OFF��

	void			Play();											//�Đ�
	void			Play(bool IsLoop);								//�Đ��i���[�v�j
	void			Play(bool IsLoop, float volume);				//�Đ��i���[�v�A���ʁj
	void			Play(bool IsLoop, float volume, float pitch);	//�Đ� (���[�v�A���ʁA�s�b�`)

	void			Stop();											//��~

	void			SetCurrentDirectory(std::string dir);			//�ǂݍ��݃t�H���_��ύX

	void			Release();										//�J��

	void			SetVolume(int vol);								//���ʐݒ�(0�`100)
	float			GetVolume();									//���� (0.0f�`1.0f)
};

