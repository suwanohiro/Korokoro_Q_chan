#pragma once

#include "../Scene_Base.hpp"
#include "./Block/BlockManager.h"

class Scene_Game : public Scene_Base
{
private:
	spBlockManager _blockManager;
	spBlockManager __getBlockManager() { return _blockManager; };


	spCharacterManager _characterManager;
	spCharacterManager __getCharacterManager() { return _characterManager; };

	// マップデータ関連
	std::string _mapFileName;

	// スクロール値
	Vector2 _scroll;

protected:

public:
	Scene_Game(std::string mapFileName, spBlockManager blockManager, spCharacterManager characterManager);
	void Initialize();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
};

