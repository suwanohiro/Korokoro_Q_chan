#pragma once

#include "../../../swnLibrary/swnLibrary.h"
#include "./Block_Base.h"
#include "./Block_Ground.h"

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
	std::vector<BlockData> _blockDataArray;

	void __loadBlockData(std::string blockDataFileName);
	void __addBlockData(BlockData data);

	/// <summary>
	/// 引数のBlockIDが既存データの何番目に存在するか
	/// </summary>
	/// <param name="blockID">既存データの添字 (存在しない場合-1)</param>
	int __searchBlockID(std::string blockID);

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="blockDataFileName">ブロックデータファイル名</param>
	void Initialize(std::string blockDataFileName);

	/// <summary>
	/// 開放処理
	/// </summary>
	void Release();

	addBlockResult addBlock(std::string BlockID, Vector2 position);
};

