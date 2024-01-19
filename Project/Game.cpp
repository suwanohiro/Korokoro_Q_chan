#include	"GameDefine.h"
#include	"Game.h"


/**
 * コンストラクタ
 *
 */
CGame::CGame():
m_EnemyArray(),
m_ItemArray()
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
	m_Stage.Load("Stage1.txt");
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	
	//変更部分
	//敵の素材読み込み
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].Load();
	}

	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
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
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//結合時変更点
	//メニューの状態初期化
	m_Menu.Initialize();
	//オーディオの状態初期化
	m_Audio->Initialize();
	//カウントダウンの初期化
	m_Countdown.Initialize();

	//プレイヤーと敵にエフェクトクラスの設定
	//プレイヤーと敵にオーディオクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	m_Player.SetAudio(&*m_Audio);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
		m_EnemyArray[i].SetAudio(&*m_Audio);
	}
	
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

	//プレイヤーの更新
	m_Player.Update();
	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.getHitBox(), ox, oy)) {
		m_Player.CollisionStage(ox, oy);
		m_Player.SetStCollision(m_Stage.GetStageCollision());
	}
	else {
		//変更点＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
		m_Player.NotCollisionStage();
	}
	//変更点＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊
	if (m_Stage.CollisionAttack(m_Player.getAttackBox(), ox, 1)) {
		m_Player.CollisionStageAttackLeft();
	}
	else if (m_Stage.CollisionAttack(m_Player.getAttackBox(), ox, 0)) {
		m_Player.CollisionStageAttackRight();
	}
	//敵の更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].TypeCheck(m_Player.getPosition(), m_Stage.GetScrollX(), m_Stage.GetScrollY());
		if (!m_EnemyArray[i].GetShow()) {
			continue;
		}

		//変更部分
		m_EnemyArray[i].Update();
		
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy)) {
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
		
	}
	//アイテムの更新
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		if (!m_ItemArray[i].GetShow()) {
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy)) {
			m_ItemArray[i].CollisionStage(oy);
		}
	}
	//当たり判定の実行
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		//結合時変更点
		
		//敵と当たればサウンドを鳴らす
		(m_Player.CollisionEnemy(m_EnemyArray[i]));

	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		m_Player.CollisionItem(m_ItemArray[i]);
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
	//プレイヤーの描画
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	m_Player.RenderShot(m_Stage.GetScrollX());
	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//エフェクトの描画
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//UIの描画
	m_Player.RenderUI();
	//カウントダウンの描画
	m_Countdown.Render();
	//結合時変更点
	//メニューの描画
	m_Menu.Render();

	//CGraphicsUtilities::RenderString(10,10,"ゲーム画面");
	//CGraphicsUtilities::RenderString(10,40,"F2キーでゲームクリア、F3キーでゲームオーバー");
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
	//敵のデバック描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムのデバック描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
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
	//敵の解放
	if (m_EnemyArray) {
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if (m_ItemArray) {
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//エフェクトの解放
	m_EffectManager.Release();

	//結合時変更点
	//メニューの描画
	m_Menu.Release();
}