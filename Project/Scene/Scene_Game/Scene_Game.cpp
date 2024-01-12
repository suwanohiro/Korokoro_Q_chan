#include "Scene_Game.hpp"

void Scene_Game::__loadMapData()
{
	const auto mainLayer = _mapData["MapData"]["Main"];
	const auto mapData = mainLayer["MapData"];
	const int length = mainLayer["Length"];

	std::vector<std::string> errorID;

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = mapData[cnt];
		const std::string BlockID = blockData["BlockID"];
		const auto Pos = blockData["Position"];
		const Vector2 Position = Vector2(Pos["x"], Pos["y"]);

		addBlockResult work = _blockManager.addBlock(BlockID, Position);

		if (std::holds_alternative<int>(work)) {
			if (std::get<int>(work) == NULL) {
				errorID.push_back(BlockID);
				continue;
			}
		}

		// ブロックデータは全て_blockDatasに格納
		// _blockDatas.push_back(std::get<spBlock_Base>(work));

		if (std::holds_alternative<spBlock_Ground>(work)) {
			_blockDatas.push_back(std::get<spBlock_Ground>(work));
		}

		// 別途格納すべきデータはこの下に記述
	}
}

Scene_Game::Scene_Game(std::string mapFileName)
	: _blockManager()
{
	// マップファイルを読み込む
	const std::string mapPath = "Resource/MapData/" + mapFileName + ".swnstg";
	_mapData = FileAction::ReadJSON(mapPath);

	_blockManager.Initialize("BlockDatas");

	__loadMapData();
}

void Scene_Game::Initialize()
{
}

void Scene_Game::Update()
{
}

void Scene_Game::Render()
{
	CGraphicsUtilities::RenderString(0, 0, "test");
	for (int cnt = 0; cnt < _blockDatas.size(); cnt++) {
		_blockDatas[cnt].get()->Render();
	}
}

void Scene_Game::Release()
{
	_blockManager.Release();
}
