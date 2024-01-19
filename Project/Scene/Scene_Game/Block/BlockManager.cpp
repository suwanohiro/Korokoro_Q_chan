#include "BlockManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// 
// private
// 
/////////////////////////////////////////////////////////////////////////////////////////////

void BlockManager::__loadMapData()
{
	//const auto mainLayer = _mapData["MapData"]["Main"];
	//const auto mapData = mainLayer["MapData"];
	//const int length = mainLayer["Length"];

	//for (int cnt = 0; cnt < length; cnt++) {
	//	const auto blockData = mapData[cnt];
	//	const std::string BlockID = blockData["BlockID"];
	//	const auto Pos = blockData["Position"];
	//	const Vector2 Position = Vector2(Pos["x"], Pos["y"]);
	//	
	//	__addBlock(BlockID, Position);

	//	if (std::holds_alternative<int>(work)) {
	//		if (std::get<int>(work) == NULL) continue;
	//	}

	//	// �u���b�N�f�[�^�͑S��_blockDatas�Ɋi�[
	//	if (std::holds_alternative<spBlock_Ground>(work)) {
	//		_blockDatas.push_back(std::get<spBlock_Ground>(work));
	//	}

	//	// �ʓr�i�[���ׂ��f�[�^�͂��̉��ɋL�q
	//}
}

// �u���b�N�f�[�^�ǂݍ��ݏ���
void BlockManager::__loadBlockData(std::string blockDataFileName)
{
	// �u���b�N�f�[�^��ǂݍ���
	const std::string filePath = "Resource/MapData/" + blockDataFileName + ".swnjsn";
	const JSON blockDatas = FileAction::ReadJSON(filePath);

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

		const BlockDataElem work = { BlockID, texture };
		__addBlockData(work);
	}
}

// �u���b�N�f�[�^�ǉ�����
void BlockManager::__addBlockData(BlockDataElem data)
{
	// BlockID�����ɑ��݂��邩�ǂ���
	const bool isFoundID = __searchBlockID(data.ID) != -1;

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
		const BlockDataElem work = _blockDataArray[cnt];
		if (work.ID != blockID) continue;

		index = cnt;
		break;
	}
	return index;
}

void BlockManager::__addBlock(std::string BlockID, Vector2 position)
{
	const int blockIndex = __searchBlockID(BlockID);
	const bool isFound = blockIndex != -1;

	// ���݂��Ȃ�ID�Ȃ炱���ŏ����I��
	if (!isFound) return;

	// blank�Ȃ炱���ŏ����I��
	if (BlockID == "blank") return;

	const BlockDataElem blockData = _blockDataArray[blockIndex];

	if (BlockID == "Player") {
		// �v���C���[
		// TODO : Player�������ꍇ�̏�����ǉ�
	}
	else {
		// ���̑��n�`
		spBlock_Ground work(new Block_Ground(blockData, position));
		_blockArray.push_back(work);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////
// 
// public
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// ����������
void BlockManager::Initialize(Vector2 initPos, std::string blockDataFileName)
{
	__loadBlockData(blockDataFileName);

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Initialize(initPos);
	}
;}

void BlockManager::FixedUpdate(Vector2 scroll)
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->FixedUpdate(scroll);
	}
}

void BlockManager::Update()
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Update();
	}
}

void BlockManager::LateUpdate()
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->LateUpdate();
	}
}

// �J������
void BlockManager::Release()
{
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		spCTexture texture = _blockDataArray[cnt].Texture;
		texture->Release();
	}

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Release();
	}
}
