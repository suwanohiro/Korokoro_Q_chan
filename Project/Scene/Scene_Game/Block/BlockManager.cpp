#include "BlockManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// 
// private
// 
/////////////////////////////////////////////////////////////////////////////////////////////

// �}�b�v�f�[�^�ǂݍ���
void BlockManager::__loadMapData(std::string mapFileName)
{
	// �����̃f�[�^����x�폜����
	_blockArray.clear();

	// �}�b�v�t�@�C����ǂݍ���
	const std::string mapPath = "Resource/MapData/" + mapFileName + ".swnstg";
	_mapData = FileAction::ReadJSON(mapPath);

	const auto mainLayer = _mapData["MapData"]["Main"];
	const auto mapData = mainLayer["MapData"];
	const int length = mainLayer["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = mapData[cnt];
		const std::string BlockID = blockData["BlockID"];
		const auto Pos = blockData["Position"];
		const Vector2 Position = Vector2(Pos["x"], Pos["y"]);
		
		__addBlock(BlockID, Position);
	}
}

// �u���b�N�f�[�^�ǂݍ��ݏ���
void BlockManager::__loadBlockData()
{
	// �u���b�N�f�[�^��ǂݍ���
	const std::string filePath = "Resource/MapData/" + _blockDataFileName + ".swnjsn";
	const JSON blockDatas = FileAction::ReadJSON(filePath);

	const int length = blockDatas["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = blockDatas["BlockDatas"][cnt];
		BlockIDElem BlockID(blockData["BlockID"]);

		if (BlockID.isBlank()) continue;

		// �e�N�X�`���֘A
		const std::string ImageFileName = blockData["ImageFileName"];
		const std::string ImageFilePath = "Image/Blocks/" + ImageFileName;
		const spCTexture texture(new CTexture);
		const bool flg = texture->Load(ImageFilePath.c_str());

		if (!flg) {
			int a = 0;
		}

		__addBlockData({BlockID.ID(), texture});
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
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		BlockDataElem work = _blockDataArray[cnt];
		if (work.ID == blockID) return cnt;
	}
	return -1;
}

void BlockManager::__addBlock(std::string BlockID, Vector2 position)
{
	BlockIDElem ID(BlockID);

	const int blockIndex = __searchBlockID(BlockID);
	const bool isFound = blockIndex > -1;

	if (blockIndex != -1) {
		int a = 0;
	}

	// ���݂��Ȃ�ID�Ȃ炱���ŏ����I��
	if (!isFound) return;

	// blank�Ȃ炱���ŏ����I��
	if (ID.isBlank()) return;

	const BlockDataElem blockData = _blockDataArray[blockIndex];

	if (ID.isPlayer()) {
		// �v���C���[
		// TODO : Player�������W�̒��� (����u���b�N�̔z�u�C���f�b�N�X�ɂȂ��Ă���)
		position *= Vector2(40, 40);
		__getCharacterManager()->setPlayer(position);
	}
	else {
		// ���̑��n�`
		spBlock_Ground work(new Block_Ground(blockData));
		work->Initialize(position);
		work->setTexture(blockData.Texture);
		_blockArray.push_back(work);
	}
}

BlockManager::BlockManager(spCharacterManager characterManager, std::string blockDataFileName)
	: _characterManager(characterManager)
	, _blockDataFileName(blockDataFileName)
{
}



/////////////////////////////////////////////////////////////////////////////////////////////
// 
// public
// 
/////////////////////////////////////////////////////////////////////////////////////////////

void BlockManager::Load()
{
	__loadBlockData();
}

// ����������
void BlockManager::Initialize(std::string mapFileName)
{
	__getCharacterManager()->Initialize();
	__loadMapData(mapFileName);
}

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

void BlockManager::Render()
{
	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		spGameObject work = _blockArray[cnt];
		work->Render();

		// _blockArray[cnt]->Render();
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
