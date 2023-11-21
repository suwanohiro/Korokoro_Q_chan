#include "RenderMap.h"

RenderMap::RenderMap(std::string mapFilePath)
{
	_mapFilePath = mapFilePath;
}

void RenderMap::Load()
{
	_mapData = FileAction::ReadCSV(_mapFilePath);
	_mapTile.Load("Ground3.png");
}

void RenderMap::Initialize()
{
	Vector2 cnt;
	for (cnt.y = 0; cnt.y < _mapData.size(); cnt.y++) {
		_grounds.push_back(std::vector<std::shared_ptr<Tile_Ground>>());
		for (cnt.x = 0; cnt.x < _mapData[cnt.y].size(); cnt.x++) {
			// csvから読み取ったタイル情報を取得
			std::string tileDataStr = _mapData[cnt.y][cnt.x];

			if (tileDataStr == "-1") continue;

			// 2桁の数値を1桁ずつの配列に変換
			std::vector<std::string> tileDataArray = StringAction::split(tileDataStr, 1);

			GroundTypes type(
				(GroundTypeHorizontal)std::atoi(tileDataArray[0].c_str()),
				(GroundTypeVertical)std::atoi(tileDataArray[1].c_str())
			);

			Vector2 pos = cnt * 30;

			std::shared_ptr<Tile_Ground> work = std::shared_ptr<Tile_Ground>(
				new Tile_Ground(pos, &_mapTile, type)
			);

			_grounds[(int)cnt.y].push_back(work);
		}
	}
}

void RenderMap::Update()
{
}

void RenderMap::Render()
{
	Vector2 cnt;
	for (cnt.y = 0; cnt.y < _grounds.size(); cnt.y++) {
		for (cnt.x = 0; cnt.x < _grounds[cnt.y].size(); cnt.x++) {
			_grounds[cnt.y][cnt.x]->Render();
		}
	}
}

void RenderMap::Release()
{
	_mapTile.Release();
}
