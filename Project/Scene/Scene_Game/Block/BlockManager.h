#pragma once

#include "../../../swnLibrary/swnLibrary.h"
#include "./Block_Base.h"
#include "./Block_Ground.h"

#include "../../../Character/Player/Player.hpp"

using addBlockResult = std::variant<
	int,
	spBlock_Base,
	spBlock_Ground
>;

class BlockManager
{
private:
	/// <summary>
	/// Block�f�[�^�z��
	/// </summary>
	std::vector<BlockDataElem> _blockDataArray;

	// �}�b�v�f�[�^�֘A
	JSON _mapData;
	void __loadMapData();
	std::vector<spGameObject> _blockArray;

	void __loadBlockData(std::string blockDataFileName);
	void __addBlockData(BlockDataElem data);

	/// <summary>
	/// ������BlockID�������f�[�^�̉��Ԗڂɑ��݂��邩
	/// </summary>
	/// <param name="blockID">�����f�[�^�̓Y�� (���݂��Ȃ��ꍇ-1)</param>
	int __searchBlockID(std::string blockID);

	void __addBlock(std::string BlockID, Vector2 position);
public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="blockDataFileName">�u���b�N�f�[�^�t�@�C����</param>
	void Initialize(Vector2 initPos, std::string blockDataFileName);

	void FixedUpdate(Vector2 scroll);
	void Update();
	void LateUpdate();

	/// <summary>
	/// �J������
	/// </summary>
	void Release();
};

