#pragma once

#include "../../../swnLibrary/swnLibrary.h"

struct BlockData {
	std::string BlockID;
	spCTexture Texture;
};

class Block_Base
{
protected:
	BlockData _blockData;

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 _position;

	/// <summary>
	/// 当たり判定
	/// </summary>
	CRectangle _rect;

public:
	Block_Base(BlockData blockData, Vector2 position);
	~Block_Base();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();

	/// <summary>
	/// 当たり判定描画
	/// </summary>
	void RenderRect();

	/// <summary>
	/// 開放処理
	/// </summary>
	void Release();

	/// <summary>
	/// BlockID取得
	/// </summary>
	/// <returns>BlockID</returns>
	std::string getBlockID() { return _blockData.BlockID; }

	/// <summary>
	/// テクスチャ取得 (share ptr)
	/// </summary>
	spCTexture getspTexture() { return _blockData.Texture; }

	/// <summary>
	/// テクスチャ取得
	/// </summary>
	CTexture* getTexture() { return getspTexture().get(); }

	/// <summary>
	/// 当たり判定用矩形取得
	/// </summary>
	/// <returns>当たり判定用矩形</returns>
	CRectangle getRect() { return _rect; }
};

using spBlock_Base = std::shared_ptr<Block_Base>;
