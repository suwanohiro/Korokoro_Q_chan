#pragma once
#include "../swnLib/swnLib.h"

#include "./MapTile/Tiles/Tile_Ground.h"

class RenderMap
{
private:
	/// <summary>
	/// マップファイルパス
	/// </summary>
	std::string _mapFilePath;

	/// <summary>
	/// マップファイルから取得したマップデータ
	/// </summary>
	CsvData _mapData;

	std::vector<std::vector<std::shared_ptr<Tile_Ground>>> _grounds;

	CTexture _mapTile;

public:
	RenderMap(std::string mapFilePath);

	void Load();
	void Initialize();
	void Update();
	void Render();
	void Release();
};

