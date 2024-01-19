#include "Scene_Game.hpp"

Scene_Game::Scene_Game(std::string mapFileName, spBlockManager blockManager, spCharacterManager characterManager)
	: _blockManager(blockManager)
	, _characterManager(characterManager)
	, _scroll()
{
	_mapFileName = mapFileName;
}

void Scene_Game::Initialize()
{
	__getBlockManager()->Initialize(_mapFileName);
}

void Scene_Game::FixedUpdate()
{
	// TODO : scroll‚ð’è‹`‚·‚é
	if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {
		_scroll.x--;
	}

	if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
		_scroll.x++;
	}

	__getBlockManager()->FixedUpdate(_scroll);
	__getCharacterManager()->FixedUpdate(_scroll);
}

void Scene_Game::Update()
{
	__getBlockManager()->Update();
	__getCharacterManager()->Update();
}

void Scene_Game::LateUpdate()
{
	__getBlockManager()->LateUpdate();
	__getCharacterManager()->LateUpdate();
}

void Scene_Game::Render()
{
	__getBlockManager()->Render();
	__getCharacterManager()->Render();

	CGraphicsUtilities::RenderString(0, 0, "scroll [x] : %0.2f", _scroll.x);
}

void Scene_Game::Release()
{
}
