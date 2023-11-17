#include	"GameApp.h"

MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	_renderMap = std::unique_ptr<RenderMap>(new RenderMap("test.csv"));

	_renderMap->Load();
	_renderMap->Initialize();

	return TRUE;
}

MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();
	
	_renderMap->Update();
	
	return TRUE;
}

MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	_renderMap->Render();

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}

MofBool CGameApp::Release(void){
	_renderMap->Release();
	return TRUE;
}