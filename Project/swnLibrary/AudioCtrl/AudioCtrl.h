#pragma once
#include "Mof.h"

class AudioCtrl
{
private:
	CSoundBuffer	_audioElem;											//�����v�f
	std::string		_audioFolder;									//�ǂݍ��݃t�H���_
	float			_volume;											//�~���[�g���ۑ��p�{�����[�� (0.0f�`1.0f)
	bool			_isMute;											//�~���[�g��Ԃ��ǂ���

	void			__setMute();										//�~���[�g�ݒ�

public:
	AudioCtrl() :
		_audioElem(),
		_audioFolder("Audio/"),
		_isMute(false),
		_volume(1.0f)
	{
	}

	~AudioCtrl() { Release(); }

	void			changeMute();									//�~���[�g�ύX�i���]�j
	void			changeMute(bool flg);							//�~���[�g�ύX�i���ڎw��j

	bool			Load(std::string Path);							//�ǂݍ���

	bool			isMute();										//�~���[�g��Ԃ�

	bool			isPlay();										//�Đ�����

	bool			isLoop();										//���[�vON��OFF��

	void			play();											//�Đ�
	void			play(bool IsLoop);								//�Đ��i���[�v�j
	void			play(bool IsLoop, float volume);				//�Đ��i���[�v�A���ʁj
	void			play(bool IsLoop, float volume, float pitch);	//�Đ� (���[�v�A���ʁA�s�b�`)

	void			stop();											//��~

	void			setCurrentDirectory(std::string dir);			//�ǂݍ��݃t�H���_��ύX

	void			Release();										//�J��

	void			setVolume(int vol);								//���ʐݒ�(0�`100)
	float			getVolume();									//���� (0.0f�`1.0f)
};

using spAudioCtrl = std::shared_ptr<AudioCtrl>;
