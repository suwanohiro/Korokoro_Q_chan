#pragma once

#include "../swnLibrary/swnLibrary.h"

enum class AudioTrack {
	BGM_Title,
	BGM_GameOver,
	BGM_GameClear,
	BGM_GameContinue,
	BGM_Stage,

	SE_Button,
	SE_Select,

	SE_Player_Move,
	SE_Player_Jump,
	SE_Player_Attack1,
	SE_Player_Attack2,
	SE_Player_Damage,
	SE_Player_Dead,

	SE_Enemy_Move,
	SE_Enemy_Attack,
	SE_Enemy_Damage,
	SE_EnemyDead,

	Length
};

class AudioManager
{
private:
	std::vector<spAudioCtrl> _audioArray;

	spAudioCtrl __getTrack(AudioTrack target) { return _audioArray[(int)target]; }

public:
	AudioManager();
	~AudioManager() { Release(); };

	bool Load();

	void play(AudioTrack target);
	bool isPlay(AudioTrack target) { return __getTrack(target)->isPlay(); }
	void stop(AudioTrack target) { __getTrack(target)->stop(); }

	void setVolume(int vol);
	void setVolume(AudioTrack target, int vol);

	void Release();
};

using spAudioManager = std::shared_ptr<AudioManager>;
