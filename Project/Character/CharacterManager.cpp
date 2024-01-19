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
{
}

void CharacterManager::FixedUpdate(Vector2 scroll)
{
	_player->FixedUpdate(scroll);

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->FixedUpdate(scroll);
	}
}

void CharacterManager::Update()
{
	_player->Update();

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->Update();
	}
}

void CharacterManager::LateUpdate()
{
	_player->LateUpdate();

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->LateUpdate();
	}
}

void CharacterManager::Render()
{
	_player->Render();

	for (int cnt = 0; cnt < _enemyArray.size(); cnt++) {
		const spEnemy work = _enemyArray[cnt];
		work->Render();
	}
}

void CharacterManager::Release()
{
	_player->Release();
	_playerData.Texture->Release();

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

	// TODO : ShotTexture‚ÌŽÀ‘•‚ð‚Ç‚¤‚É‚©‚·‚é
	work->setShotTexture(spCTexture());

	work->Initialize(initPos);

	_player = work;
}

void CharacterManager::addEnemy(std::string ID, Vector2 initPos)
{
	spEnemy work(new Enemy(__getAudioManager(), __getEffectManager()));

	const int dataTarget = __searchEnemyDataID(ID);
	const spCTexture texture = _enemyDataArray[dataTarget].Texture;

	work->setTexture(texture);

	work->Initialize(initPos);

	_enemyArray.push_back(work);
}
