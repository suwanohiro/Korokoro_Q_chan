#include "AudioManager.hpp"

AudioManager::AudioManager()
	: _audioArray()
{
}

bool AudioManager::Load()
{
	CSVData audioList = FileAction::ReadCSV("Resource/Audio/AudioList.swn");

	for (int cnt = 0; cnt < (int)AudioTrack::Length; cnt++) {
		const std::string filePath = audioList[cnt][0];

		spAudioCtrl work(new AudioCtrl());

		if (!work->Load(filePath)) return false;

		_audioArray.push_back(work);
	}

	return true;
}

void AudioManager::play(AudioTrack target)
{
	// Ä¶’†‚È‚ç‚±‚±‚Åˆ—I—¹
	if (isPlay(target)) return;

	__getTrack(target)->play();
}

void AudioManager::setVolume(int vol)
{
	for (int cnt = 0; cnt < (int)AudioTrack::Length; cnt++) {
		const AudioTrack target = (AudioTrack)cnt;
		setVolume(target, vol);
	}
}

void AudioManager::setVolume(AudioTrack target, int vol)
{
	__getTrack(target)->setVolume(vol);
}

void AudioManager::Release()
{
	for (int cnt = 0; cnt < (int)AudioTrack::Length; cnt++) {
		const AudioTrack target = (AudioTrack)cnt;
		__getTrack(target)->Release();
	}
}
