#include "AudioManager.hpp"

spAudioCtrl AudioManager::__getTrack(AudioTrack target)
{
	int target_int = (int)target;

	if (_audioArray.size() <= target_int) return spAudioCtrl(new AudioCtrl);

	return _audioArray[target_int];
}

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
	play(target, false);
}

void AudioManager::play(AudioTrack target, bool isLoop)
{
	// Ä¶’†‚È‚ç‚±‚±‚Åˆ—I—¹
	if (isPlay(target)) return;

	__getTrack(target)->play(isLoop);
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
