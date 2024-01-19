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
	CSoundBuffer	m_Source;											//音声要素
	std::string		m_AudioFolder;									//読み込みフォルダ
	float			m_Volume;											//ミュート時保存用ボリューム (0.0f～1.0f)
	bool			m_bMute;											//ミュート状態かどうか

	void			SetMute();										//ミュート設定

public:
	CAudioCtrl() :
		m_Source(),
		m_AudioFolder("Audio/"),
		m_bMute(false),
		m_Volume(1.0f)
	{
	}

	void			ChangeMute();									//ミュート変更（反転）
	void			ChangeMute(bool flg);							//ミュート変更（直接指定）

	bool			Load(std::string Path);							//読み込み

	bool			IsMute();										//ミュート状態か

	bool			IsPlay();										//再生中か

	bool			IsLoop();										//ループONかOFFか

	void			Play();											//再生
	void			Play(bool IsLoop);								//再生（ループ）
	void			Play(bool IsLoop, float volume);				//再生（ループ、音量）
	void			Play(bool IsLoop, float volume, float pitch);	//再生 (ループ、音量、ピッチ)

	void			Stop();											//停止

	void			SetCurrentDirectory(std::string dir);			//読み込みフォルダを変更

	void			Release();										//開放

	void			SetVolume(int vol);								//音量設定(0～100)
	float			GetVolume();									//音量 (0.0f～1.0f)
};

