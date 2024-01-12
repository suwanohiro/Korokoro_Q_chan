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
	}

	CTexture a;
	a.Load("");
}

Scene_Game::Scene_Game(std::string mapFileName)
{
	// マップファイルを読み込む
	const std::string mapPath = "Resource/MapData/" + mapFileName + ".swnstg";
	_mapData = FileAction::ReadJSON(mapPath);

	const int length = _mapData["MapData"]["Main"]["Length"];

	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	for (int cnt = 0; cnt < length; cnt++) {
		auto work = _mapData["MapData"]["Main"]["MapData"][cnt];


		const std::string str(_mapData["MapData"]["Main"]["MapData"][cnt]["BlockID"]);


		const int posX = work["Position"]["x"];
		const int posY = work["Position"]["y"];



		std::string x(std::to_string(posX));
		std::string y(std::to_string(posY));

		OutputDebugString(str.c_str());
		OutputDebugString("\n");
		OutputDebugString(x.c_str());
		OutputDebugString("\n");
		OutputDebugString(y.c_str());
		OutputDebugString("\n");
	}
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
	OutputDebugString("\n");
}

void Scene_Game::Initialize()
{
}

void Scene_Game::Update()
{
}

void Scene_Game::Render()
{
}

void Scene_Game::Release()
{
}
