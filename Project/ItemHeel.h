#pragma once

#include "Item.h"

class ItemHeel : public CItem
{
private:

public:
	void Initialize(Vector2 pos, CTexture* texture);					//初期化
	void Update(void);								//更新
	void CollisionStage(float oy);					//ステージと衝突した際の補正処理
	void Render(void);								//描画
	void Release(void);								//解放

	bool GetShow(void) { return m_bShow; }			//アイテムの表示有無
	void SetShow(bool flg) { m_bShow = flg; }		// 表示状態を設定する
	CRectangle GetRect();							//当たり矩形
};
