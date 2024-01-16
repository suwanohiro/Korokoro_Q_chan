#include "BlockManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// 
// private
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// ブロックデータ読み込み処理
void BlockManager::__loadBlockData(std::string blockDataFileName)
{
	// ブロックデータを読み込む
	const std::string filePath = "Resource/MapData/" + blockDataFileName + ".swnjsn";
	JSON blockDatas = FileAction::ReadJSON(filePath);

	const int length = blockDatas["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = blockDatas["BlockDatas"][cnt];
		const std::string BlockID = blockData["BlockID"];

		if (BlockID == "blank") continue;

		// テクスチャ関連
		const std::string ImageFileName = blockData["ImageFileName"];
		const std::string ImageFilePath = "Image/Blocks/" + ImageFileName;
		const spCTexture texture(new CTexture);
		const bool flg = texture->Load(ImageFilePath.c_str());

		const BlockData work = { BlockID, texture };
		__addBlockData(work);
	}
}

// ブロックデータ追加処理
void BlockManager::__addBlockData(BlockData data)
{
	// BlockIDが既に存在するかどうか
	const bool isFoundID = __searchBlockID(data.BlockID) != -1;

	// 既に存在するならここで処理終了
	if (isFoundID) return;

	// データを追加
	_blockDataArray.push_back(data);
}

// ブロックID検索処理
int BlockManager::__searchBlockID(std::string blockID)
{
	int index = -1;
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		const BlockData work = _blockDataArray[cnt];
		if (work.BlockID != blockID) continue;

		index = cnt;
		break;
	}
	return index;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// 
// public
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// 初期化処理
void BlockManager::Initialize(std::string blockDataFileName)
{
	__loadBlockData(blockDataFileName);
}

// 開放処理
void BlockManager::Release()
{
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		CTexture* texture = _blockDataArray[cnt].Texture.get();
		texture->Release();
	}
}

// ブロック追加処理
addBlockResult BlockManager::addBlock(std::string ID, Vector2 position)
{
	const int blockIndex = __searchBlockID(ID);
	const bool isFound = blockIndex != -1;

	// 存在しないIDならここで処理終了
	if (!isFound) return NULL;

	// blankならここで処理終了
	if (ID == "blank") return NULL;

	const BlockData blockData = _blockDataArray[blockIndex];

	if (ID == "Player") {
		// プレイヤー
	}
	else {
		// その他地形
		return spBlock_Ground(new Block_Ground(blockData, position));
	}

	return NULL;
}
