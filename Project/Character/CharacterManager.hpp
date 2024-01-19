#pragma once

#include "../Scene/Scene_Game/Block/BlockData.hpp"
#include "./Player/Player.hpp"
#include "./Enemy/Enemy.hpp"

class CharacterManager
{
private:
	spAudioManager _audioManager;
	spEffectManager _effectManager;
	spAudioManager __getAudioManager() { return _audioManager; }
	spEffectManager __getEffectManager() { return _effectManager; }

	spPlayer _player;
	spCTexture _playerShotTexture;
	BlockDataElem _playerData;

	std::vector<BlockDataElem> _enemyDataArray;
	spCTexture _enemyShotTexture;
	std::vector<spEnemy> _enemyArray;

	int __searchEnemyDataID(std::string ID);

public:
	CharacterManager(spAudioManager audioManager, spEffectManager effectManager);

	void PlayerData(BlockDataElem data) { _playerData = data; }
	BlockDataElem PlayerData() { return _playerData; }
	void addEnemyData(BlockDataElem data) { _enemyDataArray.push_back(data); };
	BlockDataElem EnemyData(int target) { return _enemyDataArray[target]; };

	void Load();

	void Initialize();

	void FixedUpdate(Vector2 scroll);
	void Update();
	void LateUpdate();

	void Render();

	void Release();

	void setPlayer(Vector2 initPos);
	void addEnemy(std::string ID, Vector2 initPos);
};

using spCharacterManager = std::shared_ptr<CharacterManager>;
