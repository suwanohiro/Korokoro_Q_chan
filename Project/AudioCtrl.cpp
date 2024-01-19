#include "AudioCtrl.h"

//------------------------------------------------------------------------------------------
//
// private
// 
//------------------------------------------------------------------------------------------

//ミュート設定
void CAudioCtrl::SetMute()
{
	if (m_bMute) {
		//ミュートONの場合
		//現在のボリュームを保存
		m_Volume = m_Source.GetVolume();

		//音量を0にする
		m_Source.SetVolume(0.0f);

		return;
	}

	//ミュートOFFの場合
	//保存していた音量に変更
	m_Source.SetVolume(m_Volume);
}



//------------------------------------------------------------------------------------------
// 
// public
// 
//------------------------------------------------------------------------------------------


void CAudioCtrl::ChangeMute()
{
	//ミュートフラグを反転する
	m_bMute = !m_bMute;

	SetMute();
}

void CAudioCtrl::ChangeMute(bool flg)
{
	//ミュートフラグを設定する
	m_bMute = flg;

	SetMute();
}

bool CAudioCtrl::Load(std::string Path) {
	std::string TargetPath = m_AudioFolder + Path;

	OutputDebugString(TargetPath.c_str());

	bool result = m_Source.Load(TargetPath.c_str());

	return result;
}

bool CAudioCtrl::IsMute()
{
	return (m_Source.GetVolume() == 0.0f);
}

bool CAudioCtrl::IsPlay()
{
	return m_Source.IsPlay();
}

bool CAudioCtrl::IsLoop()
{
	return m_Source.IsLoop();
}

void CAudioCtrl::Play() {
	m_Source.Play();
}

void CAudioCtrl::Play(bool IsLoop) {
	m_Source.SetLoop(IsLoop);
	Play();
}

void CAudioCtrl::Play(bool IsLoop, float volume)
{
	m_Source.SetVolume(volume / 100);
	Play(IsLoop);
}

void CAudioCtrl::Play(bool IsLoop, float volume, float pitch)
{
	m_Source.SetPitch(pitch);
	Play(IsLoop, volume);
}

void CAudioCtrl::Stop() {
	m_Source.Stop();
}

void CAudioCtrl::Release() {
	m_Source.Release();
}

void CAudioCtrl::SetVolume(int vol)
{
	float target = ((float)vol / 100);
	m_Source.SetVolume(target);
}

float CAudioCtrl::GetVolume()
{
	return m_Source.GetVolume();
}

void CAudioCtrl::SetCurrentDirectory(std::string dir)
{
	m_AudioFolder = dir;

	if (dir.rfind("/") != dir.length() - 1) {
		m_AudioFolder += "/";
	}
}
