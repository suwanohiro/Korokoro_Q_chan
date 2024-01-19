/*************************************************************************//*!
					
					@file	GameApp.h
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

#pragma once

//INCLUDE
#include	"Mof.h"
#include	"GameDefine.h"
#include	"Title.h"
//結合時変更点
#include	"StageSelect.h"
#include	"Game.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"GameContinue.h"
#include	"Audio.h"

/*******************************//*!
@brief	基本ゲームアプリ。

@author	濱田　享
*//********************************/
class CGameApp : public CSingleGameApplication {
private:
	//現在のシーン
	int						m_Scene;
	//変更するシーン
	int						m_ChangeScene;

	//各シーンクラス
	CTitle					m_TitleScene;
	CGame					m_GameScene;
	CGameClear				m_GameClearScene;
	CGameOver				m_GameOverScene;
	//結合時変更点
	CStageSelect			m_StageSelect;
	CGameContinue			m_GameContinue;
	CAudio					m_Audio;

	//デバッグ表示フラグ
	bool					m_bDebug;

public:
	/*************************************************************************//*!
			@brief			コンストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	CGameApp() {}
	/*************************************************************************//*!
			@brief			デストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	virtual ~CGameApp(){	Release();	}
	/*************************************************************************//*!
			@brief			アプリケーションの初期化
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Initialize(void);
	/*************************************************************************//*!
			@brief			アプリケーションの更新
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Update(void);
	/*************************************************************************//*!
			@brief			アプリケーションの描画
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Render(void);
	/*************************************************************************//*!
			@brief			アプリケーションの解放
			@param			None
				
			@return			TRUE		成功<br>
							それ以外	失敗、エラーコードが戻り値となる
	*//**************************************************************************/
	virtual MofBool Release(void);
};
