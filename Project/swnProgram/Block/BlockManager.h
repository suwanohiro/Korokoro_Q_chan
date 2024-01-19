#pragma once

#include "../../swnLibrary/swnLibrary.h"
#include "./Block_Base.h"
#include "./Block_Ground.h"

#include "../Character/CharacterManager.hpp"

class BlockManager
{
private:
	spCharacterManager _characterManager;
	spCharacterManager __getCharacterManager() { return _characterManager; };

	std::string _blockDataFileName;

	/// <summary>
	/// Block�f�[�^�z��
	/// </summary>
	std::vector<BlockDataElem> _blockDataArray;

	// �}�b�v�f�[�^�֘A
	JSON _mapData;
	void __loadMapData(std::string mapFileName);
	std::vector<spGameObject> _blockArray;

	void __loadBlockData();
	void __addBlockData(BlockDataElem data);

	/// <summary>
	/// ������BlockID�������f�[�^�̉��Ԗڂɑ��݂��邩
	/// </summary>
	/// <param name="blockID">�����f�[�^�̓Y�� (���݂��Ȃ��ꍇ-1)</param>
	int __searchBlockID(std::string blockID);

	void __addBlock(std::string BlockID, Vector2 position);
public:
	BlockManager(spCharacterManager characterManager, std::string blockDataFileName);

	void Load();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(std::string mapFileName);

	void FixedUpdate(Vector2 scroll);
	void Update();
	void LateUpdate();

	void Render();

	/// <summary>
	/// �J������
	/// </summary>
	void Release();
};

using spBlockManager = std::shared_ptr<BlockManager>;
