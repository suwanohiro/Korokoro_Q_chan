#include "BlockManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// 
// private
// 
/////////////////////////////////////////////////////////////////////////////////////////////

void BlockManager::__loadMapData()
{
	//const auto mainLayer = _mapData["MapData"]["Main"];
	//const auto mapData = mainLayer["MapData"];
	//const int length = mainLayer["Length"];

	//for (int cnt = 0; cnt < length; cnt++) {
	//	const auto blockData = mapData[cnt];
	//	const std::string BlockID = blockData["BlockID"];
	//	const auto Pos = blockData["Position"];
	//	const Vector2 Position = Vector2(Pos["x"], Pos["y"]);
	//	
	//	__addBlock(BlockID, Position);

	//	if (std::holds_alternative<int>(work)) {
	//		if (std::get<int>(work) == NULL) continue;
	//	}

	//	// ブロックデータは全て_blockDatasに格納
	//	if (std::holds_alternative<spBlock_Ground>(work)) {
	//		_blockDatas.push_back(std::get<spBlock_Ground>(work));
	//	}

	//	// 別途格納すべきデータはこの下に記述
	//}
}

// ブロックデータ読み込み処理
void BlockManager::__loadBlockData(std::string blockDataFileName)
{
	// ブロックデータを読み込む
	const std::string filePath = "Resource/MapData/" + blockDataFileName + ".swnjsn";
	const JSON blockDatas = FileAction::ReadJSON(filePath);

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

		const BlockDataElem work = { BlockID, texture };
		__addBlockData(work);
	}
}

// ブロックデータ追加処理
void BlockManager::__addBlockData(BlockDataElem data)
{
	// BlockIDが既に存在するかどうか
	const bool isFoundID = __searchBlockID(data.ID) != -1;

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
		const BlockDataElem work = _blockDataArray[cnt];
		if (work.ID != blockID) continue;

		index = cnt;
		break;
	}
	return index;
}

void BlockManager::__addBlock(std::string BlockID, Vector2 position)
{
	const int blockIndex = __searchBlockID(BlockID);
	const bool isFound = blockIndex != -1;

	// 存在しないIDならここで処理終了
	if (!isFound) return;

	// blankならここで処理終了
	if (BlockID == "blank") return;

	const BlockDataElem blockData = _blockDataArray[blockIndex];

	if (BlockID == "Player") {
		// プレイヤー
		// TODO : Playerだった場合の処理を追加
	}
	else {
		// その他地形
		spBlock_Ground work(new Block_Ground(blockData, position));
		_blockArray.push_back(work);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////
// 
// public
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// 初期化処理
void BlockManager::Initialize(Vector2 initPos, std::string blockDataFileName)
{
	__loadBlockData(blockDataFileName);

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Initialize(initPos);
	}
;}

void BlockManager::FixedUpdate(Vector2 scroll)
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->FixedUpdate(scroll);
	}
}

void BlockManager::Update()
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Update();
	}
}

void BlockManager::LateUpdate()
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->LateUpdate();
	}
}

// 開放処理
void BlockManager::Release()
{
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		spCTexture texture = _blockDataArray[cnt].Texture;
		texture->Release();
	}

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Release();
	}
}
