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

	// �}�b�v�f�[�^�֘A
	std::string _mapFileName;

	// �X�N���[���l
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

