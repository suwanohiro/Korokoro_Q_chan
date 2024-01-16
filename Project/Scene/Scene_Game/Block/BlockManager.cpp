#include "BlockManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// 
// private
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// �u���b�N�f�[�^�ǂݍ��ݏ���
void BlockManager::__loadBlockData(std::string blockDataFileName)
{
	// �u���b�N�f�[�^��ǂݍ���
	const std::string filePath = "Resource/MapData/" + blockDataFileName + ".swnjsn";
	JSON blockDatas = FileAction::ReadJSON(filePath);

	const int length = blockDatas["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = blockDatas["BlockDatas"][cnt];
		const std::string BlockID = blockData["BlockID"];

		if (BlockID == "blank") continue;

		// �e�N�X�`���֘A
		const std::string ImageFileName = blockData["ImageFileName"];
		const std::string ImageFilePath = "Image/Blocks/" + ImageFileName;
		const spCTexture texture(new CTexture);
		const bool flg = texture->Load(ImageFilePath.c_str());

		const BlockData work = { BlockID, texture };
		__addBlockData(work);
	}
}

// �u���b�N�f�[�^�ǉ�����
void BlockManager::__addBlockData(BlockData data)
{
	// BlockID�����ɑ��݂��邩�ǂ���
	const bool isFoundID = __searchBlockID(data.BlockID) != -1;

	// ���ɑ��݂���Ȃ炱���ŏ����I��
	if (isFoundID) return;

	// �f�[�^��ǉ�
	_blockDataArray.push_back(data);
}

// �u���b�NID��������
int BlockManager::__searchBlockID(std::string blockID)
{
	int index = -1;
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		const BlockData work = _blockDataArray[cnt];
		if (work.BlockID != blockID) continue;

		index = cnt;
		break;
	}
	return index;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// 
// public
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// ����������
void BlockManager::Initialize(std::string blockDataFileName)
{
	__loadBlockData(blockDataFileName);
}

// �J������
void BlockManager::Release()
{
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		CTexture* texture = _blockDataArray[cnt].Texture.get();
		texture->Release();
	}
}

// �u���b�N�ǉ�����
addBlockResult BlockManager::addBlock(std::string ID, Vector2 position)
{
	const int blockIndex = __searchBlockID(ID);
	const bool isFound = blockIndex != -1;

	// ���݂��Ȃ�ID�Ȃ炱���ŏ����I��
	if (!isFound) return NULL;

	// blank�Ȃ炱���ŏ����I��
	if (ID == "blank") return NULL;

	const BlockData blockData = _blockDataArray[blockIndex];

	if (ID == "Player") {
		// �v���C���[
	}
	else {
		// ���̑��n�`
		return spBlock_Ground(new Block_Ground(blockData, position));
	}

	return NULL;
}
