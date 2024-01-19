#include "AudioCtrl.h"

//------------------------------------------------------------------------------------------
//
// private
// 
//------------------------------------------------------------------------------------------

//ミュート設定
void AudioCtrl::__setMute()
{
	if (_isMute) {
		//ミュートONの場合
		//現在のボリュームを保存
		_volume = _audioElem.GetVolume();

		//音量を0にする
		_audioElem.SetVolume(0.0f);

		return;
	}

	//ミュートOFFの場合
	//保存していた音量に変更
	_audioElem.SetVolume(_volume);
}



//------------------------------------------------------------------------------------------
// 
// public
// 
//------------------------------------------------------------------------------------------


void AudioCtrl::changeMute()
{
	//ミュートフラグを反転する
	_isMute = !_isMute;

	__setMute();
}

void AudioCtrl::changeMute(bool flg)
{
	//ミュートフラグを設定する
	_isMute = flg;

	__setMute();
}

bool AudioCtrl::Load(std::string Path) {
	std::string TargetPath = _audioFolder + Path;

	OutputDebugString(TargetPath.c_str());

	bool result = _audioElem.Load(TargetPath.c_str());

	return result;
}

bool AudioCtrl::isMute()
{
	return (_audioElem.GetVolume() == 0.0f);
}

bool AudioCtrl::isPlay()
{
	return _audioElem.IsPlay();
}

bool AudioCtrl::isLoop()
{
	return _audioElem.IsLoop();
}

void AudioCtrl::play() {
	_audioElem.Play();
}

void AudioCtrl::play(bool IsLoop) {
	_audioElem.SetLoop(IsLoop);
	play();
}

void AudioCtrl::play(bool IsLoop, float volume)
{
	_audioElem.SetVolume(volume / 100);
	play(IsLoop);
}

void AudioCtrl::play(bool IsLoop, float volume, float pitch)
{
	_audioElem.SetPitch(pitch);
	play(IsLoop, volume);
}

void AudioCtrl::stop() {
	_audioElem.Stop();
}

void AudioCtrl::Release() {
	_audioElem.Release();
}

void AudioCtrl::setVolume(int vol)
{
	float target = ((float)vol / 100);
	_audioElem.SetVolume(target);
}

float AudioCtrl::getVolume()
{
	return _audioElem.GetVolume();
}

void AudioCtrl::setCurrentDirectory(std::string dir)
{
	_audioFolder = dir;

	if (dir.rfind("/") != dir.length() - 1) {
		_audioFolder += "/";
	}
}
