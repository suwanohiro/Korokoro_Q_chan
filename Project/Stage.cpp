#include	"Stage.h"
#include	<sys/stat.h>

int CStage::__searchBlockID(std::string blockID)
{
	for (int cnt = 0; cnt < _blockDataArray.size(); cnt++) {
		BlockDataElem work = _blockDataArray[cnt];
		if (work.ID == blockID) return cnt;
	}
	return -1;
}

void CStage::__loadBlockData()
{
	// �u���b�N�f�[�^��ǂݍ���
	const std::string filePath = "Resource/MapData/BlockDatas.swnjsn";
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
		if (!flg) OutputDebugString("[ Error ] �u���b�N�摜�̓ǂݍ��݂Ɏ��s���܂����B");

		__addBlockData({ BlockID.ID(), texture });
	}
}

void CStage::__addBlockData(BlockDataElem data)
{
	// BlockID�����ɑ��݂��邩�ǂ���
	const bool isFoundID = __searchBlockID(data.ID) != -1;

	// ���ɑ��݂���Ȃ炱���ŏ����I��
	if (isFoundID) return;

	// �e�N�X�`���ő�T�C�Y�̍X�V
	const float w = data.Texture->GetWidth();
	const float h = data.Texture->GetHeight();
	if (w > _maxBlockTextureSize.x) _maxBlockTextureSize.x = w;
	if (h > _maxBlockTextureSize.y) _maxBlockTextureSize.y = h;

	// �f�[�^��ǉ�
	_blockDataArray.push_back(data);
}

void CStage::__addBlock(std::string BlockID, Vector2 position)
{
	BlockIDElem ID(BlockID);

	const int blockIndex = __searchBlockID(BlockID);
	const bool isFound = blockIndex > -1;

	// ���݂��Ȃ�ID�Ȃ炱���ŏ����I��
	if (!isFound) return;

	// blank�Ȃ炱���ŏ����I��
	if (ID.isBlank()) return;

	const BlockDataElem blockData = _blockDataArray[blockIndex];

	if (ID.isPlayer()) {
		// �v���C���[
		// TODO : Player�������W�̒��� (����u���b�N�̔z�u�C���f�b�N�X�ɂȂ��Ă���)
		position *= Vector2(40, 40);
		__setPlayer(position);
	}
	else if (ID.isID("Enemy")) {
		// TODO : Enemy�ǉ��������������
		spCEnemy work(new CEnemy);
		work->Initialize(position.x, position.y, 0);
		work->SetEffectManager(_pmng);
		work->SetAudio(_audio);

		_enemyArray.push_back(work);
	}
	else if (ID.isID("coin") || ID.isID("orb")) {
		// TODO : Item�ǉ��������������
		spCItem work(new CItem);
		ItemType type = (ID.isID("coin")) ? ItemType::WayPoint : ItemType::Recover;
		Vector2 pos = position;
		pos *= blockData.Texture->GetWidth();
		work->Initialize(pos.x, pos.y, (int)type);
		work->SetTexture(blockData.Texture.get());

		_itemArray.push_back(work);
	}
	else {
		// ���̑��n�`
		spBlock_Ground work(new Block_Ground(blockData));
		work->Initialize(position);
		work->setTexture(blockData.Texture);
		_blockArray.push_back(work);
	}
}

void CStage::__setPlayer(Vector2 pos)
{
	if (_isPlayerSeted) return;

	spCPlayer work(new CPlayer);
	work->Load();
	work->Initialize();
	work->SetPos(pos);
	work->SetEffectManager(_pmng);
	work->SetAudio(_audio);
	_isPlayerSeted = true;

	_player = work;
}

void CStage::__updateScroll()
{
	//�v���C���[�̋�`�擾
	CRectangle prec = _player->getHitBox();
	//�X�N���[���̕�
	const float screenWidth = CGraphicsUtilities::GetGraphics()->GetTargetWidth();

	//�X�e�[�W�S�̂̕�
	// const float stageWidth = _maxBlockTextureSize.x * _mapTileCount.x;
	const float stageWidth = _mapSize.x;

	//���W����ʒ[�ɂ���Ă���i�e�[����400pixel�j�ꍇ�X�N���[�����s���ĕ␳����
	const float limit = 400.0f;

	struct {
		float Left;
		float Right;
	} scrollLimit;

	scrollLimit.Left = m_ScrollX;
	scrollLimit.Right = m_ScrollX;

	scrollLimit.Left += limit;
	scrollLimit.Right += screenWidth - limit;

	if (prec.Left < scrollLimit.Left) {
		m_ScrollX -= (scrollLimit.Left - prec.Left);
		if (m_ScrollX < 0) m_ScrollX = 0;
	}
	else if (prec.Right > scrollLimit.Right) {
		m_ScrollX += (prec.Right - scrollLimit.Right);
		const float limitScrollRight = stageWidth - screenWidth;
		if (m_ScrollX > limitScrollRight) m_ScrollX = limitScrollRight;

		// �����X�e�[�W�̑S������ʕ���菬�������
		// if (stageWidth < screenWidth) m_ScrollX = 0;
	}

	return;


	// const float limit = 200.0f;
	// if (prec.Left - m_ScrollX < scrollLimit.Left) {
	// 	m_ScrollX -= limit - (prec.Left - m_ScrollX);
	// 	if (m_ScrollX < 0) m_ScrollX = 0;
	// }
	// else if (prec.Right - m_ScrollX > screenWidth - scrollLimit.Right) {
	// 	m_ScrollX += (prec.Right - m_ScrollX) - (screenWidth - limit);
	// 	if (m_ScrollX >= stageWidth - screenWidth) m_ScrollX = stageWidth - screenWidth;
	// }
}

void CStage::__updatePlayer()
{
	if (!_isPlayerSeted) return;

	_player->Update();
	_player->UpdateUI();

	//�X�N���[���̕�
	const float screenWidth = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	Vector2 pos = _player->GetPos();
	const float recRight = _player->getHitBox().Right;
	// if (pos.x < 0) pos.x = 0;

	const float rightLimit = m_ScrollX + screenWidth;
	// if (rightLimit < recRight) pos.x = rightLimit;

	_player->SetPos(pos);

	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	const bool flg = Collision(_player->getHitBox(), ox, oy);
	if (flg) {
		_player->CollisionStage(ox, oy);
		_player->SetStCollision(GetStageCollision());
	}
	else {
		_player->NotCollisionStage();
	}

	if (CollisionAttack(_player->getAttackBox(), ox, 1)) {
		_player->CollisionStageAttackLeft();
	}
	else if (CollisionAttack(_player->getAttackBox(), ox, 0)) {
		_player->CollisionStageAttackRight();
	}

	// �A�C�e���Ƃ̔���
	for (int cnt = 0; cnt < _itemArray.size(); cnt++) {
		// TODO : spItem�𖳗���ϊ����Ă���̂Ńo�O�̔����\���L
		_player->CollisionItem(*_itemArray[cnt].get());
	}

	// �G�Ƃ̔���
	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		// TODO : spCEnemy�𖳗���ϊ����Ă���̂Ńo�O�̔����\���L
		_player->CollisionEnemy(*_enemyArray[cnt].get());
	}
}

void CStage::__updateItem(spCItem targetElem)
{
	targetElem->Update();

	if (!targetElem->GetShow()) return;

	float ox = 0, oy = 0;
	const bool flg = Collision(targetElem->GetRect(), ox, oy);

	if (flg) targetElem->CollisionStage(oy);
}

// �G �X�V
void CStage::__updateEnemy(spCEnemy targetElem)
{
	targetElem->TypeCheck(_player->getPosition(), m_ScrollX, m_ScrollY);

	if (!targetElem->GetShow()) return;

	targetElem->Update();

	float ox = 0, oy = 0;
	const bool flg = Collision(targetElem->GetRect(), ox, oy);

	if (flg) targetElem->CollisionStage(ox, oy);
}

void renderVector2(const std::string& title, const Vector2& value) {
	std::string msg = "[ Info ] " + title + " | x : " + std::to_string(value.x) + "\t y : " + std::to_string(value.y) + "\n";
	OutputDebugString(msg.c_str());
}

void CStage::__renderBackGround()
{
	//���i�̕`��
	Vector2 screenSize = { (float)g_pGraphics->GetTargetWidth(),(float) g_pGraphics->GetTargetHeight() };
	Vector2 bkSize = { (float)m_BackTexture.GetWidth(), (float)m_BackTexture.GetHeight() };

	struct count {
		int Start;
		int Count;
		int End;
	};

	count y;
	y.Start = (int)(m_ScrollY / bkSize.y);
	y.End = (int)((m_ScrollY + screenSize.y) / bkSize.y) + 1;
	for (y.Count = y.Start; y.Count < y.End; y.Count++) {
		count x;
		x.Start = (int)(m_ScrollX / bkSize.x);
		x.End = (int)((m_ScrollX + screenSize.x) / bkSize.x) + 1;
		for (x.Count = x.Start; x.Count < x.End; x.Count++) {
			Vector2 renderPos(x.Count, y.Count);
			renderPos *= bkSize;
			m_BackTexture.Render(renderPos.x - m_ScrollX, renderPos.y - m_ScrollY);
		}
	}
}

void CStage::__collisionBottom(CRectangle cr, CRectangle r, bool& re, float& oy)
{
	CRectangle brec = r;
	brec.Top = brec.Bottom - 1;
	brec.Expansion(-6, 0);

	if (cr.CollisionRect(brec)) {
		re = true;

		//���̖��܂�Ȃ̂Ń`�b�v��[�����`�̉��[�̒l���������l�����܂�̒l
		oy += cr.Top - brec.Bottom;
		r.Top += cr.Top - brec.Bottom;
		r.Bottom += cr.Top - brec.Bottom;
	}
}

void CStage::__collisionTop(CRectangle cr, CRectangle r, bool& re, float& oy)
{
	CRectangle trec = r;
	trec.Bottom = trec.Top + 1;
	trec.Expansion(-6, 0);
	//��Ɠ����蔻��
	if (cr.CollisionRect(trec)) {
		re = true;
		//��̖��܂�Ȃ̂Ń`�b�v�̉��[�����`�̏�[�̒l���������l�����܂�̒l
		oy += cr.Bottom - trec.Top;
		r.Top += cr.Bottom - trec.Top;
		r.Bottom += cr.Bottom - trec.Top;
	}
}

void CStage::__collisionLeftRight(CRectangle cr, CRectangle r, bool& re, float& ox)
{
	CRectangle lrec = r;
	lrec.Right = lrec.Left + 1;
	lrec.Expansion(0, -6);
	CRectangle rrec = r;
	rrec.Left = rrec.Right - 1;
	rrec.Expansion(0, -6);

	//���Ɠ����蔻��
	if (cr.CollisionRect(lrec)) {
		re = true;
		//���̖��܂�Ȃ̂Ń`�b�v�E�[�����`�̍��[�̒l���������l�����܂�̒l
		ox += cr.Right - lrec.Left;
		r.Left += cr.Right - lrec.Left;
		r.Right += cr.Right - lrec.Left;
		return;
	}
	//�E�Ƃ̓����蔻��
	if (cr.CollisionRect(rrec)) {
		re = true;
		//�E�̖��܂�Ȃ̂Ń`�b�v���[�����`�̉E�[���������l�����܂�̒l
		ox += cr.Left - rrec.Right;
		r.Left += cr.Left - rrec.Right;
		r.Right += cr.Left - rrec.Right;
	}
}

/**
 * �R���X�g���N�^
 *
 */
CStage::CStage()
	: m_BackTexture()
	, m_ScrollX(0)
	, m_ScrollY(0)
	, m_StCollision(false)
	, _player(nullptr)
	, _mapTileCount(0, 0)
	, _mapSize(0, 0)
	, _maxBlockTextureSize(0, 0)
{
}

/**
 * �f�X�g���N�^
 *
 */
CStage::~CStage(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ��ށB
 *
 * ����
 * [in]			pName				�X�e�[�W�t�@�C���̖��O
 */
bool CStage::LoadMapData(std::string mapFileName){
	// �����̃f�[�^����x�폜����
	_blockArray.clear();
	_enemyArray.clear();
	_itemArray.clear();
	_isPlayerSeted = false;

	_blockDataArray.clear();
	__loadBlockData();

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

		if (Position.x > _mapTileCount.x) _mapTileCount.x = Position.x;
		if (Position.y > _mapTileCount.y) _mapTileCount.y = Position.y;

		_mapSize = _maxBlockTextureSize * _mapTileCount;
		
		__addBlock(BlockID, Position);
	}

	int a = _blockArray.size();
	return true;
}

bool CStage::LoadBKTexture()
{
	return m_BackTexture.Load("bg.png");
}

/**
 * ������
 * �p�����[�^�[����W������������B
 */
void CStage::Initialize(CEffectManager* pmng, CAudio* audio){
	m_ScrollX = 0;
	m_ScrollY = 0;
	m_StCollision = false;

	_pmng = pmng;
	_audio = audio;
}

/**
 * �X�V
 *
 * ����
 * [in]			pl					�v���C���[�A�X�N���[���̔���Ɏg�p
 */
void CStage::Update(){
	////////////////////////////////////////////////////////////////////////
	// 
	// FixedUpdate
	// 
	////////////////////////////////////////////////////////////////////////

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->FixedUpdate(Vector2(m_ScrollX, m_ScrollY));
	}

	////////////////////////////////////////////////////////////////////////
	// 
	// Update
	// 
	////////////////////////////////////////////////////////////////////////

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Update();
	}

	for (int cnt = 0; cnt < _itemArray.size(); cnt++) {
		spCItem targetElem = _itemArray[cnt];
		__updateItem(targetElem);

		if (targetElem->GetShow()) continue;

		// ��\����ԂȂ�z�񂩂�폜����
		_itemArray.erase(_itemArray.begin() + cnt);
	}

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		spCEnemy targetElem = _enemyArray[cnt];
		__updateEnemy(targetElem);

		if (targetElem->GetShow()) continue;

		// ��\����ԂȂ�z�񂩂�폜����
		_enemyArray.erase(_enemyArray.begin() + cnt);
	}

	__updatePlayer();

	////////////////////////////////////////////////////////////////////////
	// 
	// LateUpdate
	// 
	////////////////////////////////////////////////////////////////////////

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		spGameObject targetElem = _blockArray[cnt];
		targetElem->LateUpdate();

		if (targetElem->isActive()) continue;

		// ������Ԃ̗v�f�͔z�񂩂�폜����
		_blockArray.erase(_blockArray.begin() + cnt);
	}

	__updateScroll();
}

bool CStage::Collision(CRectangle r, float& ox, float& oy)
{
	m_StCollision = true;
	bool re = false;

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		spGameObject targetElem = _blockArray[cnt];
		CRectangle cr = targetElem->getRect();

		// �������̔���
		__collisionBottom(cr, r, re, oy);

		// ���E�����̔���
		__collisionLeftRight(cr, r, re, ox);

		// ������̔���
		__collisionTop(cr, r, re, oy);
		
	}
	return re;
}

bool CStage::CollisionAttack(CRectangle r, float& ox, int type)
{
	bool re = false;
	m_StCollision = true;

	// �U��type���K��̂��̂łȂ��Ȃ炱���ŏ����I��
	const bool isAttack = (type == 0 || type == 1);
	if (!isAttack) return false;

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		spGameObject targetElem = _blockArray[cnt];
		CRectangle cr = targetElem->getRect();

		//�����蔻��p�̃L�����N�^�[��`
		//���E�Ŕ͈͂����肵����p�̋�`���쐬����
		CRectangle lrec = r;
		lrec.Right = lrec.Left + 1;//���̋�`�͉E�������Ɠ����l�ɂ���
		lrec.Expansion(0, -6);		//�c�͈̔͂��������߂�

		//�����蔻��p�̃L�����N�^�[��`
		//���E�Ŕ͈͂����肵����p�̋�`���쐬����
		CRectangle rrec = r;
		rrec.Left = rrec.Right - 1;//�E�̋�`�͍������E�Ɠ����l�ɂ���
		rrec.Expansion(0, -6);		//�c�͈̔͂��������߂�

		CRectangle targetRect = (type == 0) ? lrec : rrec;
		re = cr.CollisionRect(targetRect);
	}
	return re;
}

/**
 * �`��
 *
 */
void CStage::Render(void){
	__renderBackGround();

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Render();
	}

	for (int cnt = 0; cnt < _itemArray.size(); cnt++) {
		_itemArray[cnt]->Render(m_ScrollX, m_ScrollY);
	}

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		_enemyArray[cnt]->Render(m_ScrollX, m_ScrollY);
	}

	Vector2 pos = _player->GetPos();
	const float screenHeight = g_pGraphics->GetTargetHeight();
	const float BottomLimit = m_ScrollY + screenHeight;

	// TODO : ���Ƃŏ���
	if (BottomLimit < pos.y) _player->SetHP(0);
	CGraphicsUtilities::RenderString(0, 150, "PlayerPos : %0.2f, %0.2f", pos.x, pos.y);


	CGraphicsUtilities::RenderString(0, 100, "X : %0.2f\nY : %0.2f", m_ScrollX, m_ScrollY);

	if (!_isPlayerSeted) return;
	_player->Render(m_ScrollX, m_ScrollY);
	_player->RenderUI();
}

/**
 * �f�o�b�O�`��
 *
 */
void CStage::RenderDebug(void){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,100,"�X�N���[�� X : %.0f , Y : %.0f",m_ScrollX,m_ScrollY);

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->RenderRect();
	}

	for (int cnt = 0; cnt < _itemArray.size(); cnt++) {
		_itemArray[cnt]->RenderDebug(m_ScrollX, m_ScrollY);
	}

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		_enemyArray[cnt]->RenderDebug(m_ScrollX, m_ScrollY);
	}

	if (_player != nullptr) _player->RenderDebug(m_ScrollX, m_ScrollY);
}

/**
 * ���
 *
 */
void CStage::Release(void){

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		_blockArray[cnt]->Release();
	}

	for (int cnt = 0; cnt < _itemArray.size(); cnt++) {
		_itemArray[cnt]->Release();
	}

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		_enemyArray[cnt]->Release();
	}

	if (_player != nullptr) _player->Release();

	m_BackTexture.Release();
}