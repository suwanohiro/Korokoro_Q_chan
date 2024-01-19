#pragma once

#include "../../swnLibrary/swnLibrary.h"
#include "./Block_Base.h"
#include "./Block_Ground.h"

#include "../Character/CharacterManager.hpp"

class BlockManager
{
private:
	spCharacterManager _characterManager;
	spCharacterManager __getCharacterManager() { return _characterManager; };

	std::string _blockDataFileName;

	/// <summary>
	/// Blockデータ配列
	/// </summary>
	std::vector<BlockDataElem> _blockDataArray;

	// マップデータ関連
	JSON _mapData;
	void __loadMapData(std::string mapFileName);
	std::vector<spGameObject> _blockArray;

	void __loadBlockData();
	void __addBlockData(BlockDataElem data);

	/// <summary>
	/// 引数のBlockIDが既存データの何番目に存在するか
	/// </summary>
	/// <param name="blockID">既存データの添字 (存在しない場合-1)</param>
	int __searchBlockID(std::string blockID);

	void __addBlock(std::string BlockID, Vector2 position);
public:
	BlockManager(spCharacterManager characterManager, std::string blockDataFileName);

	void Load();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(std::string mapFileName);

	void FixedUpdate(Vector2 scroll);
	void Update();
	void LateUpdate();

	void Render();

	/// <summary>
	/// 開放処理
	/// </summary>
	void Release();
};

using spBlockManager = std::shared_ptr<BlockManager>;
