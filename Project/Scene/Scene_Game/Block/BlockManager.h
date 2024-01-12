#pragma once

#include "../../../swnLibrary/swnLibrary.h"
#include "./Block_Base.h"
#include "./Block_Ground.h"

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
	std::vector<BlockData> _blockDataArray;

	void __loadBlockData(std::string blockDataFileName);
	void __addBlockData(BlockData data);

	/// <summary>
	/// ������BlockID�������f�[�^�̉��Ԗڂɑ��݂��邩
	/// </summary>
	/// <param name="blockID">�����f�[�^�̓Y�� (���݂��Ȃ��ꍇ-1)</param>
	int __searchBlockID(std::string blockID);

public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="blockDataFileName">�u���b�N�f�[�^�t�@�C����</param>
	void Initialize(std::string blockDataFileName);

	/// <summary>
	/// �J������
	/// </summary>
	void Release();

	addBlockResult addBlock(std::string BlockID, Vector2 position);
};

