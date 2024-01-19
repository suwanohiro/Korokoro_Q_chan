#pragma once

#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
//結合時変更点
#include	"Menu.h"
#include	"EffectManager.h"
#include	"Audio.h"
#include	"Countdown.h"


class CGame {
private:
	//プレイヤー
	CPlayer		m_Player;
	//ステージ
	CStage		m_Stage;
	//敵
	CEnemy*		m_EnemyArray;
	//エフェクト
	CEffectManager m_EffectManager;
	//アイテム
	CItem*		m_ItemArray;
	//メニュー
	CMenu		m_Menu;
	//サウンド
	CAudio*		m_Audio;
	//カウントダウン
	Countdown	m_Countdown;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	void SetAudio(CAudio* audio) {
		m_Audio = audio;
	}
};