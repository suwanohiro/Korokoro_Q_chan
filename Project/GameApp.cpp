/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"





void CGameApp::__renderLoading()
{
	Vector2 screenSize = {
			(float)g_pGraphics->GetTargetWidth(),
			(float)g_pGraphics->GetTargetHeight()
	};

	CRectangle bk(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	CGraphicsUtilities::RenderFillRect(bk, getRGB(WebColor::white));

	std::string nowloading = "Now Loading";
	Vector2 size = StringAction::GetStringSize(nowloading.c_str());
	Vector2 padding(30, 30);
	size += padding;

	Vector2 pos = screenSize * 0.5 - size * 0.5;

	CGraphicsUtilities::RenderString(pos.x, pos.y, getRGB(WebColor::black), "Now Loading");
}

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	m_Audio = spCAudio(new CAudio);

	_isLoaded = false;

	_loadThread = std::thread([=]() {
		//シーンの必要リソースを全て読み込む
		m_TitleScene.Load();
		//結合時変更点
		m_StageSelect.Load();
		m_GameScene.Load();
		m_GameClearScene.Load();
		m_GameOverScene.Load();
		m_GameContinue.Load();
		m_Audio->Load();

		m_Scene = SCENENO_TITLE;
		m_ChangeScene = SCENENO_TITLE;
		m_bDebug = false;

		m_TitleScene.SetAudio(m_Audio);
		m_StageSelect.SetAudio(m_Audio);
		m_GameScene.SetAudio(m_Audio);
		m_GameClearScene.SetAudio(m_Audio);
		m_GameOverScene.SetAudio(m_Audio);
		m_GameContinue.SetAudio(m_Audio);

		//最初に実行されるシーンの初期化
		m_TitleScene.Initialize();

		_isLoaded = true;
	});
	_loadThread.detach();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	if (!_isLoaded) return TRUE;
	
	//シーン番号によって更新
	switch(m_Scene)
	{
		case SCENENO_TITLE:
			m_TitleScene.Update(m_ChangeScene);
			break;
		//結合時変更点
		case SCENENO_SELECT:
			m_StageSelect.Update(m_ChangeScene);
			break;
		case SCENENO_GAME:
			m_GameScene.Update(m_ChangeScene);
			break;
		case SCENENO_GAMECLEAR:
			m_GameClearScene.Update(m_ChangeScene);
			break;
		case SCENENO_GAMEOVER:
			m_GameOverScene.Update(m_ChangeScene);
			break;
		case SCENENO_CONTINUE:
			m_GameContinue.Update(m_ChangeScene);
			break;
	}
	
	//シーン変更があった場合変更先シーンの初期化
	if(m_ChangeScene != m_Scene)
	{
		switch(m_ChangeScene)
		{
			case SCENENO_TITLE:
				m_TitleScene.Initialize();
				break;
			//結合時変更点
			case SCENENO_SELECT:
				m_StageSelect.Initialize();
				break;
			case SCENENO_GAME:
				m_GameScene.Initialize(m_StageSelect.getStageNumber());
				break;
			case SCENENO_GAMECLEAR:
				m_GameClearScene.Initialize();
				break;
			case SCENENO_GAMEOVER:
				m_GameOverScene.Initialize();
				break;
			case SCENENO_CONTINUE:
				m_GameContinue.Initialize();
				break;
		}
		m_Scene = m_ChangeScene;
	}

	//デバッグ表示の切り替え
	if(g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_bDebug = ((m_bDebug) ? false : true);
	}
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	if (!_isLoaded) {
		__renderLoading();

		//描画の終了
		g_pGraphics->RenderEnd();
		return TRUE;
	}

	
	//シーン番号によって描画
	switch(m_Scene)
	{
		case SCENENO_TITLE:
			m_TitleScene.Render();
			break;
		//結合時変更点
		case SCENENO_SELECT:
			m_StageSelect.Render();
			break;
		case SCENENO_GAME:
			m_GameScene.Render();
			break;
		case SCENENO_GAMECLEAR:
			m_GameClearScene.Render();
			break;
		case SCENENO_GAMEOVER:
			m_GameOverScene.Render();
			break;
		case SCENENO_CONTINUE:
			m_GameContinue.Render();
			break;
	}
	
	//デバッグ表示をする場合
	if(m_bDebug)
	{
		//シーン番号によって描画
		switch(m_Scene)
		{
			case SCENENO_TITLE:
				m_TitleScene.RenderDebug();
				break;
			//結合時変更点
			case SCENENO_SELECT:
				m_StageSelect.RenderDebug();
				break;
			case SCENENO_GAME:
				m_GameScene.RenderDebug();
				break;
			case SCENENO_GAMECLEAR:
				m_GameClearScene.RenderDebug();
				break;
			case SCENENO_GAMEOVER:
				m_GameOverScene.RenderDebug();
				break;
			case SCENENO_CONTINUE:
				m_GameContinue.RenderDebug();
				break;
		}
	}

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	if (!_isLoaded) _loadThread.join();

	m_TitleScene.Release();
	//結合時変更点
	m_StageSelect.Release();
	m_GameScene.Release();
	m_GameClearScene.Release();
	m_GameOverScene.Release();
	m_GameContinue.Release();
	m_Audio->Release();

	return TRUE;
}