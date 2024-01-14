#include "Scene_Game.hpp"

void Scene_Game::__loadMapData()
{
	const auto mainLayer = _mapData["MapData"]["Main"];
	const auto mapData = mainLayer["MapData"];
	const int length = mainLayer["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = mapData[cnt];
		const std::string BlockID = blockData["BlockID"];
		const auto Pos = blockData["Position"];
		const Vector2 Position = Vector2(Pos["x"], Pos["y"]);

		addBlockResult work = _blockManager.addBlock(BlockID, Position);

		if (std::holds_alternative<int>(work)) {
			if (std::get<int>(work) == NULL) continue;
		}

		// �u���b�N�f�[�^�͑S��_blockDatas�Ɋi�[
		if (std::holds_alternative<spBlock_Ground>(work)) {
			_blockDatas.push_back(std::get<spBlock_Ground>(work));
		}

		// �ʓr�i�[���ׂ��f�[�^�͂��̉��ɋL�q
	}
}

Scene_Game::Scene_Game(std::string mapFileName)
	: _blockManager()
{
	// �}�b�v�t�@�C����ǂݍ���
	const std::string mapPath = "Resource/MapData/" + mapFileName + ".swnstg";
	_mapData = FileAction::ReadJSON(mapPath);
}

void Scene_Game::Initialize()
{
	_blockManager.Initialize("BlockDatas");

	__loadMapData();
}

void Scene_Game::Update()
{
}

void Scene_Game::Render()
{
	for (int cnt = 0; cnt < _blockDatas.size(); cnt++) {
		_blockDatas[cnt]->Render();
	}
}

void Scene_Game::Release()
{
	_blockManager.Release();
}
