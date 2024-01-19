#pragma once

#include	"Mof.h"
#include	"Gravity.h"

//アイテムの種類
enum tag_ITEMTYPE {
	ITEM_RECOVER,		//回復
	ITEM_WAYPOINT,		//中間地点
	ITEM_GOAL,			//ゴール	

	ITEM_COUNT,
};

enum class ItemType {
	Recover,
	WayPoint,
	Goal
};

class CItem {
protected:
	ItemType				m_ItemType;
	CTexture*				m_itemTexture;
	CSpriteMotionController	m_Motion;
	Vector2					m_pos = {0,0};
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	CGravity				m_Gravity;

public:
	CItem();
	~CItem();
	void Initialize(float px, float py, int typee);						//初期化
	void Update(void);													//更新
	void CollisionStage(float oy);										//ステージと衝突した際の補正処理
	void Render(float wx, float wy);									//描画
	void RenderDebug(float wx, float wy);
	void Release(void);													//解放

	void SetTexture(CTexture* pt) { m_itemTexture = pt; }				//テクスチャの設定
	void SetShow(bool flg) { m_bShow = flg; }							// 表示状態を設定する
	bool GetShow(void) { return m_bShow; }								//アイテムの表示有無
	CRectangle GetRect();												//当たり矩形
	ItemType GetType() { return m_ItemType; }							//アイテムの種類
};

using spCItem = std::shared_ptr<CItem>;