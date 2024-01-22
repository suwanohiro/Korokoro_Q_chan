#include "Item.h"

/* コンストラクタ*/
CItem::CItem() :
	m_pos(),
	m_MoveY(0.0f),
	m_bShow(false),
	m_SrcRect()
{
}

/* デストラクタ*/
CItem::~CItem()
{
}

/* 初期化
引数
[in]		px		X座標
[in]		py		Y座標
*/
void CItem::Initialize(float px, float py, int type)
{
	m_pos.x = px;
	m_pos.y = py;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_ItemType = (ItemType)type;
	//アニメーションを作成
	SpriteAnimationCreate anim = {
		"アイテム",0,0,40,40,
		TRUE,{{5,0,0}}
	};
	m_Motion.Create(anim);	
}

/* 更新*/
void CItem::Update(void)
{
	//非表示
	if (!m_bShow)
	{
		return;
	}
	
	//重力により真下に少しずつ下がる
	m_Gravity.Gravity(m_MoveY);
	if (m_MoveY >= 10.0f)
	{
		m_MoveY = 10.0f;
	}
	m_pos.y += m_MoveY;
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/* ステージと衝突した際の補正処理
引数
[in]		oy		Y埋まり量
*/
void CItem::CollisionStage(float oy)
{
	m_pos.y += oy;
	//落下中の下埋まりの場合は移動を初期化する。
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
}

/* 描画
引数
[in]		wx		ワールドの変化
[in]		wy		ワールドの変化
*/
void CItem::Render(float wx, float wy)
{
	//非表示
	if (!m_bShow)
	{
		return;
	}

	m_itemTexture->Render(m_pos.x - wx, m_pos.y - wy,m_SrcRect);
}

void CItem::RenderDebug(float wx, float wy)
{
	//非表示
	if (!m_bShow) return;

	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
}

/* 解放*/
void CItem::Release(void)
{
	m_Motion.Release();
}

/* 当たり矩形*/
CRectangle CItem::GetRect()
{
	//非表示
	if (!m_bShow)
	{
		return NULL;
	}

	return CRectangle(m_pos.x,m_pos.y, m_pos.x + m_SrcRect.GetWidth(), m_pos.y + m_SrcRect.GetHeight());
}
