#pragma once

#include "../MapTile.h"
#include "./Tile_GroundType.h"

class Tile_Ground : public MapTile
{
private:
	/// <summary>
	/// マップ1タイルあたりのサイズ
	/// </summary>
	const Vector2 oneTileSize = { 30, 30 };

	/// <summary>
	/// 地面タイプ
	/// </summary>
	GroundTypes _type;

public:
	Tile_Ground(Vector2 position, CTexture* mapTexture, GroundTypes type)
		: MapTile(position, mapTexture)
	{
		// 描画矩形を設定
		__setRenderRec(CRectangle(
			(float)type.horizontal * oneTileSize.x,
			(float)type.vertical * oneTileSize.y,
			(float)type.horizontal * oneTileSize.x + oneTileSize.x,
			(float)type.vertical * oneTileSize.y + oneTileSize.y
		));
	}
};