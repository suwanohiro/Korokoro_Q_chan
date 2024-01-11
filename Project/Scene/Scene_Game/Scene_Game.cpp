#include "Scene_Game.hpp"

Scene_Game::Scene_Game(std::string mapFileName)
{
	// マップファイルを読み込む
	const std::string mapPath = "Resource/MapData/" + mapFileName + ".swnstg";
	JSON mapData = FileAction::ReadJSON(mapPath);

	const int length = mapData["MapData"]["Main"]["Length"];

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
		auto work = mapData["MapData"]["Main"]["MapData"][cnt];


		const std::string str(mapData["MapData"]["Main"]["MapData"][cnt]["BlockID"]);


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
