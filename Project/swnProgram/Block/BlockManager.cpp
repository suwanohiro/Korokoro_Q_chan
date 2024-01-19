#include "BlockManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// 
// private
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// マップデータ読み込み
void BlockManager::__loadMapData(std::string mapFileName)
{
	// 既存のデータを一度削除する
	_blockArray.clear();

	// マップファイルを読み込む
	const std::string mapPath = "Resource/MapData/" + mapFileName + ".swnstg";
	_mapData = FileAction::ReadJSON(mapPath);

	const auto mainLayer = _mapData["MapData"]["Main"];
	const auto mapData = mainLayer["MapData"];
	const int length = mainLayer["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = mapData[cnt];
		const std::string BlockID = blockData["BlockID"];
		const auto Pos = blockData["Position"];
		const Vector2 Position = Vector2(Pos["x"], Pos["y"]);
		
		__addBlock(BlockID, Position);
	}
}

// ブロックデータ読み込み処理
void BlockManager::__loadBlockData()
{
	// ブロックデータを読み込む
	const std::string filePath = "Resource/MapData/" + _blockDataFileName + ".swnjsn";
	const JSON blockDatas = FileAction::ReadJSON(filePath);

	const int length = blockDatas["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = blockDatas["BlockDatas"][cnt];
		BlockIDElem BlockID(blockData["BlockID"]);

		if (BlockID.isBlank()) continue;

		// テクスチャ関連
		const std::string ImageFileName = blockData["ImageFileName"];
		const std::string ImageFilePath = "Image/Blocks/" + ImageFileName;
		const spCTexture texture(new CTexture);
		const bool flg = texture->Load(ImageFilePath.c_str());

		if (!flg) {
			int a = 0;
		}

		__addBlockData({BlockID.ID(), texture});
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
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		BlockDataElem work = _blockDataArray[cnt];
		if (work.ID == blockID) return cnt;
	}
	return -1;
}

void BlockManager::__addBlock(std::string BlockID, Vector2 position)
{
	BlockIDElem ID(BlockID);

	const int blockIndex = __searchBlockID(BlockID);
	const bool isFound = blockIndex > -1;

	if (blockIndex != -1) {
		int a = 0;
	}

	// 存在しないIDならここで処理終了
	if (!isFound) return;

	// blankならここで処理終了
	if (ID.isBlank()) return;

	const BlockDataElem blockData = _blockDataArray[blockIndex];

	if (ID.isPlayer()) {
		// プレイヤー
		// TODO : Player初期座標の調整 (現状ブロックの配置インデックスになっている)
		position *= Vector2(40, 40);
		__getCharacterManager()->setPlayer(position);
	}
	else {
		// その他地形
		spBlock_Ground work(new Block_Ground(blockData));
		work->Initialize(position);
		work->setTexture(blockData.Texture);
		_blockArray.push_back(work);
	}
}

BlockManager::BlockManager(spCharacterManager characterManager, std::string blockDataFileName)
	: _characterManager(characterManager)
	, _blockDataFileName(blockDataFileName)
{
}



/////////////////////////////////////////////////////////////////////////////////////////////
// 
// public
// 
/////////////////////////////////////////////////////////////////////////////////////////////

void BlockManager::Load()
{
	__loadBlockData();
}

// 初期化処理
void BlockManager::Initialize(std::string mapFileName)
{
	__getCharacterManager()->Initialize();
	__loadMapData(mapFileName);
}

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

void BlockManager::Render()
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		spGameObject work = _blockArray[cnt];
		work->Render();

		// _blockArray[cnt]->Render();
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
