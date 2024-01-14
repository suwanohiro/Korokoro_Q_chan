#pragma once
#include "Mof.h"

class AudioCtrl
{
private:
	CSoundBuffer	_audioElem;											//音声要素
	std::string		_audioFolder;									//読み込みフォルダ
	float			_volume;											//ミュート時保存用ボリューム (0.0f～1.0f)
	bool			_isMute;											//ミュート状態かどうか

	void			__setMute();										//ミュート設定

public:
	AudioCtrl() :
		_audioElem(),
		_audioFolder("Audio/"),
		_isMute(false),
		_volume(1.0f)
	{
	}

	~AudioCtrl() { Release(); }

	void			changeMute();									//ミュート変更（反転）
	void			changeMute(bool flg);							//ミュート変更（直接指定）

	bool			Load(std::string Path);							//読み込み

	bool			isMute();										//ミュート状態か

	bool			isPlay();										//再生中か

	bool			isLoop();										//ループONかOFFか

	void			play();											//再生
	void			play(bool IsLoop);								//再生（ループ）
	void			play(bool IsLoop, float volume);				//再生（ループ、音量）
	void			play(bool IsLoop, float volume, float pitch);	//再生 (ループ、音量、ピッチ)

	void			stop();											//停止

	void			setCurrentDirectory(std::string dir);			//読み込みフォルダを変更

	void			Release();										//開放

	void			setVolume(int vol);								//音量設定(0～100)
	float			getVolume();									//音量 (0.0f～1.0f)
};

using spAudioCtrl = std::shared_ptr<AudioCtrl>;
