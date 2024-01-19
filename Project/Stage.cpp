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
	// ブロックデータを読み込む
	const std::string filePath = "Resource/MapData/BlockDatas.swnjsn";
	const JSON blockDatas = FileAction::ReadJSON(filePath);

	const int length = blockDatas["Length"];

	for (int cnt = 0; cnt < length; cnt++) {
		const auto blockData = blockDatas["BlockDatas"][cnt];
		BlockIDElem BlockID(blockData["BlockID"]);

		if (BlockID.isBlank()) continue;

		// テクスチャ関連
		const std::string ImageFileName = blockData["ImageFileName"];
		const std::string ImageFilePath = "Image/Blocks/" + ImageFileName;
		const spCTexture texture(new CTexture);
		const bool flg = texture->Load(ImageFilePath.c_str());
		if (!flg) OutputDebugString("[ Error ] ブロック画像の読み込みに失敗しました。");

		__addBlockData({ BlockID.ID(), texture });
	}
}

void CStage::__addBlockData(BlockDataElem data)
{
	// BlockIDが既に存在するかどうか
	const bool isFoundID = __searchBlockID(data.ID) != -1;

	// 既に存在するならここで処理終了
	if (isFoundID) return;

	// テクスチャ最大サイズの更新
	const float w = data.Texture->GetWidth();
	const float h = data.Texture->GetHeight();
	if (w > _maxBlockTextureSize.x) _maxBlockTextureSize.x = w;
	if (h > _maxBlockTextureSize.y) _maxBlockTextureSize.y = h;

	// データを追加
	_blockDataArray.push_back(data);
}

void CStage::__addBlock(std::string BlockID, Vector2 position)
{
	BlockIDElem ID(BlockID);

	const int blockIndex = __searchBlockID(BlockID);
	const bool isFound = blockIndex > -1;

	// 存在しないIDならここで処理終了
	if (!isFound) return;

	// blankならここで処理終了
	if (ID.isBlank()) return;

	const BlockDataElem blockData = _blockDataArray[blockIndex];

	if (ID.isPlayer()) {
		// プレイヤー
		// TODO : Player初期座標の調整 (現状ブロックの配置インデックスになっている)
		position *= Vector2(40, 40);
		__setPlayer(position);
	}
	else if (ID.isID("Enemy")) {
		// TODO : Enemy追加処理仮実装状態
		spCEnemy work(new CEnemy);
		work->Initialize(position.x, position.y, 0);
		work->SetEffectManager(_pmng);
		work->SetAudio(_audio);

		_enemyArray.push_back(work);
	}
	else if (ID.isID("item")) {
		// TODO : Item追加処理仮実装状態
		spCItem work(new CItem);
		work->Initialize(position.x, position.y, 0);

		_itemArray.push_back(work);
	}
	else {
		// その他地形
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
	//プレイヤーの矩形取得
	CRectangle prec = _player->getHitBox();
	//スクリーンの幅
	const float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();

	//ステージ全体の幅
	const float stgw = _maxBlockTextureSize.x * _mapSize.x;

	//座標が画面端によっている（各端から200pixel）場合スクロールを行って補正する
	const float scrollLimit = 200.0f;
	if (prec.Left - m_ScrollX < scrollLimit) {
		m_ScrollX -= scrollLimit - (prec.Left - m_ScrollX);
		if (m_ScrollX < 0) m_ScrollX = 0;
	}
	else if (prec.Right - m_ScrollX > sw - scrollLimit) {
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - scrollLimit);
		if (m_ScrollX >= stgw - sw) m_ScrollX = stgw - sw;
	}
}

void CStage::__updatePlayer()
{
	if (!_isPlayerSeted) return;

	_player->Update();
	_player->UpdateUI();

	//ステージとプレイヤーの当たり判定
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

	// アイテムとの判定
	for (int cnt = 0; cnt < _itemArray.size(); cnt++) {
		// TODO : spItemを無理矢理変換しているのでバグの発生可能性有
		_player->CollisionItem(*_itemArray[cnt].get());
	}

	// 敵との判定
	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		// TODO : spCEnemyを無理矢理変換しているのでバグの発生可能性有
		_player->CollisionEnemy(*_enemyArray[cnt].get());
	}
}

void CStage::__updateItem(spCItem targetElem)
{
	targetElem->Update();

	float ox = 0, oy = 0;
	const bool flg = Collision(targetElem->GetRect(), ox, oy);

	if (flg) targetElem->CollisionStage(oy);
}

// 敵 更新
void CStage::__updateEnemy(spCEnemy targetElem)
{
	targetElem->TypeCheck(_player->getPosition(), m_ScrollX, m_ScrollY);

	if (!targetElem->GetShow()) return;

	targetElem->Update();

	float ox = 0, oy = 0;
	const bool flg = Collision(targetElem->GetRect(), ox, oy);

	if (flg) targetElem->CollisionStage(ox, oy);
}

void CStage::__renderBackGround()
{
	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollX % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-m_ScrollX % wn) - wn; y < scw; y += wn) {
			m_BackTexture.Render(x, y);
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

		//下の埋まりなのでチップ上端から矩形の下端の値を引いた値が埋まりの値
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
	//上と当たり判定
	if (cr.CollisionRect(trec)) {
		re = true;
		//上の埋まりなのでチップの下端から矩形の上端の値を引いた値が埋まりの値
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

	//左と当たり判定
	if (cr.CollisionRect(lrec)) {
		re = true;
		//左の埋まりなのでチップ右端から矩形の左端の値を引いた値が埋まりの値
		ox += cr.Right - lrec.Left;
		r.Left += cr.Right - lrec.Left;
		r.Right += cr.Right - lrec.Left;
		return;
	}
	//右との当たり判定
	if (cr.CollisionRect(rrec)) {
		re = true;
		//右の埋まりなのでチップ左端から矩形の右端を引いた値が埋まりの値
		ox += cr.Left - rrec.Right;
		r.Left += cr.Left - rrec.Right;
		r.Right += cr.Left - rrec.Right;
	}
}

/**
 * コンストラクタ
 *
 */
CStage::CStage()
	: m_BackTexture()
	, m_ScrollX(0)
	, m_ScrollY(0)
	, m_StCollision(false)
	, _player(nullptr)
	, _mapSize(0, 0)
	, _maxBlockTextureSize(0, 0)
{
}

/**
 * デストラクタ
 *
 */
CStage::~CStage(){
}

/**
 * 読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pName				ステージファイルの名前
 */
bool CStage::LoadMapData(std::string mapFileName){
	// 既存のデータを一度削除する
	_blockArray.clear();
	_isPlayerSeted = false;

	__loadBlockData();

	// マップファイルを読み込む
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

		if (Position.x > _mapSize.x) _mapSize.x = Position.x;
		if (Position.y > _mapSize.y) _mapSize.y = Position.y;
		
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
 * 初期化
 * パラメーターや座標を初期化する。
 */
void CStage::Initialize(CEffectManager* pmng, CAudio* audio){
	m_ScrollX = 0;
	m_ScrollY = 0;
	m_StCollision = false;

	_pmng = pmng;
	_audio = audio;
}

/**
 * 更新
 *
 * 引数
 * [in]			pl					プレイヤー、スクロールの判定に使用
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

		// 非表示状態なら配列から削除する
		_itemArray.erase(_itemArray.begin() + cnt);
	}

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		spCEnemy targetElem = _enemyArray[cnt];
		__updateEnemy(targetElem);

		if (targetElem->GetShow()) continue;

		// 非表示状態なら配列から削除する
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

		// 無効状態の要素は配列から削除する
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

		// 下方向の判別
		__collisionBottom(cr, r, re, oy);

		// 左右方向の判別
		__collisionLeftRight(cr, r, re, ox);

		// 上方向の判別
		__collisionTop(cr, r, re, oy);
		
	}
	return re;
}

bool CStage::CollisionAttack(CRectangle r, float& ox, int type)
{
	bool re = false;
	m_StCollision = true;

	// 攻撃typeが規定のものでないならここで処理終了
	const bool isAttack = (type == 0 || type == 1);
	if (!isAttack) return false;

	for (int cnt = 0; cnt < _blockArray.size(); cnt++) {
		spGameObject targetElem = _blockArray[cnt];
		CRectangle cr = targetElem->getRect();

		//あたり判定用のキャラクター矩形
		//左右で範囲を限定した専用の矩形を作成する
		CRectangle lrec = r;
		lrec.Right = lrec.Left + 1;//左の矩形は右側を左と同じ値にする
		lrec.Expansion(0, -6);		//縦の範囲を少し狭める

		//あたり判定用のキャラクター矩形
		//左右で範囲を限定した専用の矩形を作成する
		CRectangle rrec = r;
		rrec.Left = rrec.Right - 1;//右の矩形は左側を右と同じ値にする
		rrec.Expansion(0, -6);		//縦の範囲を少し狭める

		CRectangle targetRect = (type == 0) ? lrec : rrec;
		re = cr.CollisionRect(targetRect);
	}
	return re;
}

/**
 * 描画
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

	if (!_isPlayerSeted) return;
	_player->Render(m_ScrollX, m_ScrollY);
	_player->RenderUI();
}

/**
 * デバッグ描画
 *
 */
void CStage::RenderDebug(void){
	//位置の描画
	CGraphicsUtilities::RenderString(10,100,"スクロール X : %.0f , Y : %.0f",m_ScrollX,m_ScrollY);

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
 * 解放
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