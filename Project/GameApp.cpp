#include	"GameApp.h"

CGameApp::CGameApp()
	: _audioManager()
	, _effectManager()
{
	_scene = spScene_Base(new Scene_Game("mario"));
}

MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	_audioManager->Load();
	_effectManager->Load();

	_scene->Initialize();

	return TRUE;
}

MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	/////////////////////////////////////////////////////
	// 
	// FixedUpdate
	// 
	/////////////////////////////////////////////////////
	_effectManager->FixedUpdate();


	/////////////////////////////////////////////////////
	// 
	// Update
	// 
	/////////////////////////////////////////////////////
	_effectManager->Update();
	_scene->Update();


	/////////////////////////////////////////////////////
	// 
	// LateUpdate
	// 
	/////////////////////////////////////////////////////
	_effectManager->LateUpdate();
	
	return TRUE;
}

MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	_scene->Render();

	// TODO : _effectManager->Render(Vector2())の引数をどうにかする
	_effectManager->Render(Vector2());

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}

MofBool CGameApp::Release(void){
	_audioManager->Release();
	_effectManager->Release();
	_scene->Release();

	return TRUE;
}