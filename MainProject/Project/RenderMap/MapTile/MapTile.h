#pragma once
#include "../../swnLib/swnLib.h"

class MapTile
{
protected:
	/// <summary>
	/// 座標
	/// </summary>
	Vector2 _position;

	/// <summary>
	/// マップテクスチャ
	/// </summary>
	CTexture* _mapTexture = NULL;

	/// <summary>
	/// 描画矩形
	/// </summary>
	CRectangle _renderRec;

	/// <summary>
	/// 描画矩形を設定する
	/// </summary>
	/// <param name="rec">描画矩形</param>
	void __setRenderRec(CRectangle rec) { _renderRec = rec; }

public:
	MapTile(Vector2 position, CTexture* mapTexture);
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Render();
};

