#include "Audio.h"


bool CAudio::Load()
{
	//âπÇÃì«Ç›çûÇ›
	char* name[]{
		"TitleBGM.mp3",
		"GameOverBGM.mp3",
		"GameClearBGM.mp3",
		"GameContinueBGM.mp3",
		"StageBGM.mp3",
		"Button.mp3",
		"Select.mp3",
		"PlayerMove.mp3",
		"PlayerJump.mp3",
		"PlayerAttack01.mp3",
		"PlayerAttack02.mp3",
		"PlayerDamege.mp3",
		"PlayerDead.mp3",
		"EnemyMove.mp3",
		"EnemyAttack.mp3",
		"EnemyDamege.mp3",
		"EnemyDead.mp3",
		"Heel.mp3",
		"BGM_Stage.mp3",
		"BGM_StageSelect.mp3",
	};
	
	for (int i = 0; i < Audio_Count; i++) {
		m_Audio.push_back(new CAudioCtrl());
		if (!m_Audio[i]->Load(name[i])) {
			return false;
		}
	}
	return true;
}

void CAudio::SetVolume(int volume)
{
	m_Volume = volume;
}

void CAudio::Initialize()
{
	for (int i = 0; i < Audio_Count; i++) {
		m_Audio[i]->Stop();
	}
	m_Volume = 50;
}

void CAudio::Play(tag_Audio tAudio, bool flg)
{
	m_Audio[tAudio]->Play(flg,m_Volume);
}

bool CAudio::IsPlay(tag_Audio tAudio)
{
	return m_Audio[tAudio]->IsPlay();
}

void CAudio::Stop(tag_Audio tAudio)
{
	m_Audio[tAudio]->Stop();
}

float CAudio::GetVolume()
{
	return m_Volume;
}

void CAudio::Release()
{
	for (int i = 0; i < m_Audio.size(); i++) {
		m_Audio[i]->Release();
	}
}

