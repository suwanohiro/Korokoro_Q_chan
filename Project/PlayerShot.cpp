#include	"PlayerShot.h"

/**
 * コンストラクタ
 *
 */
CPlayerShot::CPlayerShot() :
	m_pTexture(NULL),
	m_Position(0, 0),
	m_bShow(false),
	m_Reverse(false) {
}

/**
 * デストラクタ
 *
 */
CPlayerShot::~CPlayerShot() {
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 */
void CPlayerShot::Initialize(void) {
	m_Position = Vector2(0, 0);
	m_bShow = false;
	SpriteAnimationCreate shotanim = {
	"撃つ",
	0,0,
	120,96,
	TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
	};

	m_ShotMotion.Create(shotanim);
}
/**
 * 発射
 * 引数の座標に位置を設定して、表示フラグをtrueに変更する。
 *
 * 引数
 * [in]			px				発射Ｘ座標
 * [in]			py				発射Ｙ座標
 */
void CPlayerShot::Fire(float px, float py, bool r) {
	m_Position.x = px - m_pTexture->GetWidth() * 0.5f;
	m_Position.y = py + m_pTexture->GetHeight() * 0.5f;
	m_bShow = true;
	m_Reverse = r;
}

/**
 * 更新
 *
 */
void CPlayerShot::Update(void) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//右の時に右に発射、左の時に左に発射に変える*******************************************************************

	if (m_Reverse) {
		m_Position.x -= PLAYERSHOT_SPEED;
	}
	else {
		m_Position.x += PLAYERSHOT_SPEED;
	}

	m_ShotMotion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcShotRect = m_ShotMotion.GetSrcRect();
	//画面上より左で消去
	//+ m_pTexture->GetWidth()
	/*if (m_Position.x  < 0)
	{
		m_bShow = false;
	}*/
	//画面上より右で消去
	//if (m_Position.x  > g_pGraphics->GetTargetWidth())
	//{
		//m_bShow = false;
	//}
}

/**
 * 描画
 *
 */
void CPlayerShot::Render(float wx) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//画面上より左で消去
	if (m_Position.x < wx - m_pTexture->GetWidth() + 200)
	{
		m_bShow = false;
	}
	//画面上より右で消去
	if (m_Position.x > g_pGraphics->GetTargetWidth() + wx + m_pTexture->GetWidth() - 790)
	{
		m_bShow = false;
	}

	CRectangle dr = m_SrcShotRect;
	//テクスチャの描画
	//スクロール値が考慮されていないplayerクラスのrender参照
	if (m_Reverse) {
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		m_pTexture->Render(m_Position.x + m_SrcShotRect.GetWidth() - wx, m_Position.y - (m_SrcShotRect.GetHeight() * 0.5f), dr);
	}
	else {
		m_pTexture->Render(m_Position.x + m_SrcShotRect.GetWidth() + 150 - wx, m_Position.y - (m_SrcShotRect.GetHeight() * 0.5f), dr);
	}
}

/**
 * デバッグ描画
 *
 */
void CPlayerShot::RenderDebug(float wx) {
	//非表示
	if (!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	if (m_Reverse) {
		CGraphicsUtilities::RenderRect(m_Position.x + m_SrcShotRect.GetWidth() + 30 - wx, m_Position.y - (m_pTexture->GetHeight() * 0.5f),
			m_Position.x + (m_SrcShotRect.GetWidth() * 2) - wx, m_Position.y + (m_pTexture->GetHeight() * 0.5f), MOF_XRGB(0, 255, 0));
	}
	else {
		CGraphicsUtilities::RenderRect(m_Position.x + m_SrcShotRect.GetWidth() + 150 - wx, m_Position.y - (m_pTexture->GetHeight() * 0.5f),
			m_Position.x + 360 - wx, m_Position.y + (m_pTexture->GetHeight() * 0.5f), MOF_XRGB(0, 255, 0));
	}
}
