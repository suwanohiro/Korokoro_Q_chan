#include	"GameDefine.h"
#include	"Game.h"


/**
 * コンストラクタ
 *
 */
CGame::CGame()
{
}

/**
 * デストラクタ
 *
 */
CGame::~CGame(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGame::Load(void){
	//プレイヤーの素材読み込み
	m_Player.Load();
	//ステージの素材読み込み
	// TODO : ステージの読み込みが1ステージ分しかできていない問題
	m_Stage.LoadMapData("test_stage_2024-01-12_1");

	// TODO : アイテムの配列をStageに追加

	//エフェクトの素材読み込み
	m_EffectManager.Load();
	//メニューの素材読み込み
	m_Menu.Load();
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGame::Initialize(){

	//プレイヤーの状態初期化
	m_Player.Initialize();
	//ステージの状態初期化
	m_Stage.Initialize(&m_EffectManager, &*m_Audio);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//結合時変更点
	//メニューの状態初期化
	m_Menu.Initialize();
	//オーディオの状態初期化
	m_Audio->Initialize();
	//カウントダウンの初期化
	m_Countdown.Initialize();
	
	m_Menu.SetAudio(&*m_Audio);

	//カウントダウン時間の設定
	m_Countdown.SetCountdown(20);
	m_Countdown.Start();
}

/**
 * 更新
 *
 */
void CGame::Update(int& ChangeScene){
	//結合時変更点
	//メニュー
	m_Menu.Update(ChangeScene);
	if (m_Menu.GetMenu())
	{
		return;
	}

	//カウントダウンの更新
	m_Countdown.Update();
	if (!m_Countdown.GetRemaining()) {
		ChangeScene = SCENENO_GAMEOVER;
		return;
	}
	
	//ステージの更新
	m_Stage.Update(m_Player);
	//エフェクトの更新
	m_EffectManager.Update();

	m_Player.UpdateUI();

	if (m_Player.IsGoal()) {
		ChangeScene = SCENENO_GAMECLEAR;
	}
	//F2キーでゲームクリア画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F2)) {
		ChangeScene = SCENENO_GAMECLEAR;
	}

	if (m_Player.IsDead()) {
		ChangeScene = SCENENO_CONTINUE;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F4)) {
		ChangeScene = SCENENO_CONTINUE;
	}
	//プレイヤーの終了フラグでゲームオーバー画面へ
	if (m_Player.IsEnd()) {
		ChangeScene = SCENENO_GAMEOVER;
	}
	//F3キーでゲームクリア画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F3)) {
		ChangeScene = SCENENO_GAMEOVER;
	}
	//デバッグ用

}

/**
 * 描画
 *
 */
void CGame::Render(void){
	//ステージの描画
	m_Stage.Render();

	//エフェクトの描画
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//UIの描画
	m_Player.RenderUI();
	//カウントダウンの描画
	m_Countdown.Render();
	//結合時変更点
	//メニューの描画
	m_Menu.Render();
}

/**
 * デバッグ描画
 *
 */
void CGame::RenderDebug(void){
	//ステージのデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーのデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//エフェクトのデバック描画
	//m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * 解放
 *
 */
void CGame::Release(void){
	//ステージの解放
	m_Stage.Release();
	//プレイヤーの解放
	m_Player.Release();

	//エフェクトの解放
	m_EffectManager.Release();

	//結合時変更点
	//メニューの描画
	m_Menu.Release();
}