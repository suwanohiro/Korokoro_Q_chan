#include "CharacterManager.hpp"

int CharacterManager::__searchEnemyDataID(std::string ID)
{	std::vector<BlockDataElem>::iterator itr;

	BlockDataElem work;
	work.ID = ID;

	itr = std::find(_enemyDataArray.begin(), _enemyDataArray.end(), work);

	// Œ©‚Â‚©‚ç‚È‚©‚Á‚½ê‡
	if (itr == _enemyDataArray.end()) return -1;

	return std::distance(_enemyDataArray.begin(), itr);
}

CharacterManager::CharacterManager(spAudioManager audioManager, spEffectManager effectManager)
	: _audioManager(audioManager)
	, _effectManager(effectManager)
	, _player(nullptr)
	, _playerShotTexture(new CTexture)
	, _enemyShotTexture(new CTexture)
{
	_playerData.Texture = spCTexture(new CTexture);
}

void CharacterManager::Load()
{
	_playerData.Texture->Load("Image/Player/player.png");
	_playerShotTexture->Load("Image/Player/P_missile.png");
	_enemyShotTexture->Load("Image/Enemy/E_missile.png");
}

void CharacterManager::Initialize()
{
	if (_player != nullptr) _player->Release();
	_player = nullptr;
	_enemyArray.clear();
}

void CharacterManager::FixedUpdate(Vector2 scroll)
{
	if (_player != nullptr) _player->FixedUpdate(scroll);

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->FixedUpdate(scroll);
	}
}

void CharacterManager::Update()
{
	if (_player != nullptr) _player->Update();

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->Update();
	}
}

void CharacterManager::LateUpdate()
{
	if (_player != nullptr) _player->LateUpdate();

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->LateUpdate();
	}
}

void CharacterManager::Render()
{
	if (_player != nullptr) {
		_player->Render();
		_player->RenderRect();
	}

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->Render();
	}
}

void CharacterManager::Release()
{
	if (_player != nullptr) _player->Release();
	if (_playerShotTexture != nullptr) _playerShotTexture->Release();
	if (_enemyShotTexture != nullptr) _enemyShotTexture->Release();

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->Release();
	}

	for (int cnt = 0; cnt < _enemyDataArray.size(); cnt++) {
		BlockDataElem work = _enemyDataArray[cnt];
		work.Texture->Release();
	}
}

void CharacterManager::setPlayer(Vector2 initPos)
{
	spPlayer work(new Player(__getAudioManager(), __getEffectManager()));
	work->setTexture(_playerData.Texture);

	work->setShotTexture(_playerShotTexture);

	work->Initialize(initPos);

	_player = work;
}

void CharacterManager::addEnemy(std::string ID, Vector2 initPos)
{
	spEnemy work(new Enemy(__getAudioManager(), __getEffectManager()));

	const int dataTarget = __searchEnemyDataID(ID);
	const spCTexture texture = _enemyDataArray[dataTarget].Texture;

	work->setTexture(texture);
	work->setShotTexture(_enemyShotTexture);

	work->Initialize(initPos);

	_enemyArray.push_back(work);
}
