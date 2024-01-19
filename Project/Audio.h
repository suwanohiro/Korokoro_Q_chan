#pragma once
#include	"AudioCtrl.h"

enum tag_Audio
{
	Audio_TitleBGM,				//タイトルBGM
	Audio_GameOverBGM,			//ゲームオーバーBGM
	Audio_GameClearBGM,			//ゲームクリアBGM
	Audio_GameContinueBGM,		//ゲームコンテニューBGM
	Audio_StageBGM,				//ステージBGM

	Audio_Button,				//ボタンクリックSE
	Audio_Select,				//選択SE

	Audio_PlayerMove,			//プレイヤー移動SE
	Audio_PlayerJump,			//プレイヤージャンプSE
	Audio_PlayerAttack_1,		//プレイヤー攻撃1SE
	Audio_PlayerAttack_2,		//プレイヤー攻撃2SE
	Audio_PlayerDamege,			//プレイヤーダメージSE
	Audio_PlayerDead,			//プレイヤー死亡SE

	Audio_EnemyMove,			//敵移動SE
	Audio_EnemyAttack,			//敵攻撃SE
	Audio_EnemyDamege,			//敵ダメージSE
	Audio_EnemyDead,			//敵死亡SE

	Audio_Heel,					//回復SE

	Audio_Count,
};

class CAudio
{
private:
	std::vector<CAudioCtrl*> m_Audio;
	int m_Volume;

public:
	bool Load();
	void SetVolume(int volume);
	void Initialize();
	void Play(tag_Audio tAudio, bool flg = false);
	bool IsPlay(tag_Audio tAudio);
	void Stop(tag_Audio tAudio);
	float GetVolume();
	void Release();
};

