#pragma once

#include "../Scene_Base.hpp"
#include "./Block/BlockManager.h"

class Scene_Game : public Scene_Base
{
private:
	// マップデータ関連
	JSON _mapData;
	void __loadMapData();

	BlockManager _blockManager;
	std::vector<spBlock_Base> _blockDatas;

protected:

public:
	Scene_Game(std::string mapFileName);
	void Initialize();
	void Update();
	void Render();
	void Release();
};

