#pragma once

#include "../Scene_Base.hpp"

class Scene_Game : public Scene_Base
{
private:
	JSON _mapData;

	void __loadMapData();

protected:

public:
	Scene_Game(std::string mapFileName);
	void Initialize();
	void Update();
	void Render();
	void Release();
};

