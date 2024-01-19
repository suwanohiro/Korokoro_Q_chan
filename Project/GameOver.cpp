#include	"GameDefine.h"
#include	"GameOver.h"



/**
 * コンストラクタ
 *
 */
CGameOver::CGameOver() :
m_BackImage(),
m_Alpha(0),
m_Change(false) {
}

/**
 * デストラクタ
 *
 */
CGameOver::~CGameOver(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameOver::Load(void){
	if (!m_BackImage.Load("GameOver.png")) {
		return false;
	}
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGameOver::Initialize(void){
	m_Audio->Initialize();
	m_Alpha = 0;
	m_Change = false;
	m_Volume = 50;
	m_Audio->SetVolume(m_Volume);
	m_Audio->Play(Audio_GameOverBGM, false);
}

/**
 * 更新
 *
 */
void CGameOver::Update(int& ChangeScene){
	if (m_Change)
	{
		if (m_Alpha <= 0) {
			ChangeScene = SCENENO_SELECT;
		}
		else {
			m_Alpha -= 5;
		}
	}
	else
	{
		if (m_Alpha < 255)
		{
			m_Alpha += 5;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		//ボタンSEを流す
		m_Audio->Play(Audio_Button, false);
		m_Change = true;
	}
}

/**
 * 描画
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Pree Enter Key");
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(255 - m_Alpha, 0, 0, 0));
}

/**
 * デバッグ描画
 *
 */
void CGameOver::RenderDebug(void){
}

/**
 * 解放
 *
 */
void CGameOver::Release(void){
	m_BackImage.Release();
}