#pragma once

#include "../../../swnLibrary/swnLibrary.h"
#include "./Block_Base.h"
#include "./Block_Ground.h"

#include "../../../Character/Player/Player.hpp"

using addBlockResult = std::variant<
	int,
	spBlock_Base,
	spBlock_Ground
>;

class BlockManager
{
private:
	/// <summary>
	/// Blockデータ配列
	/// </summary>
	std::vector<BlockDataElem> _blockDataArray;

	// マップデータ関連
	JSON _mapData;
	void __loadMapData();
	std::vector<spGameObject> _blockArray;

	void __loadBlockData(std::string blockDataFileName);
	void __addBlockData(BlockDataElem data);

	/// <summary>
	/// 引数のBlockIDが既存データの何番目に存在するか
	/// </summary>
	/// <param name="blockID">既存データの添字 (存在しない場合-1)</param>
	int __searchBlockID(std::string blockID);

	void __addBlock(std::string BlockID, Vector2 position);
public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="blockDataFileName">ブロックデータファイル名</param>
	void Initialize(Vector2 initPos, std::string blockDataFileName);

	void FixedUpdate(Vector2 scroll);
	void Update();
	void LateUpdate();

	/// <summary>
	/// 開放処理
	/// </summary>
	void Release();
};

