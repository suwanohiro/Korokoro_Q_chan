#pragma once

#include "./swnLibrary/swnLibrary.h"
#include "./swnProgram/Block/BlockData.hpp"
#include "./swnProgram/Block/Block_Base.h"
#include "./swnProgram/Block/Block_Ground.h"

#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"

class CStage {
private:
	CTexture				m_BackTexture;

	float					m_ScrollX;
	float					m_ScrollY;
	bool					m_StCollision;

	CEffectManager* _pmng;
	CAudio* _audio;

	///////////////////////////////////////////////////////
	// 
	// swnProgram
	// 
	///////////////////////////////////////////////////////

	spCPlayer _player;
	bool _isPlayerSeted;

	std::vector<spCEnemy> _enemyArray;
	std::vector<spCItem> _itemArray;

	/// <summary>
	/// 引数のBlockIDが既存データの何番目に存在するか
	/// </summary>
	/// <param name="blockID">既存データの添字 (存在しない場合-1)</param>
	int __searchBlockID(std::string blockID);

	/// <summary>
	/// Blockデータ配列
	/// </summary>
	std::vector<BlockDataElem> _blockDataArray;
	Vector2 _maxBlockTextureSize;
	void __loadBlockData();
	void __addBlockData(BlockDataElem data);

	// マップデータ関連
	JSON _mapData;
	Vector2 _mapTileCount;
	Vector2 _mapSize;
	std::vector<spGameObject> _blockArray;
	void __addBlock(std::string BlockID, Vector2 position);

	void __setPlayer(Vector2 pos);

	void __updateScroll();
	void __updatePlayer();
	void __updateItem(spCItem targetElem);
	void __updateEnemy(spCEnemy targetElem);

	void __renderBackGround();

	/////////////////////////////////////////////////////////////////
	// 
	// Collision
	// 
	/////////////////////////////////////////////////////////////////

	void __collisionBottom(CRectangle cr, CRectangle r, bool& re, float& oy);
	void __collisionTop(CRectangle cr, CRectangle r, bool& re, float& oy);
	void __collisionLeftRight(CRectangle cr, CRectangle r, bool& re, float& ox);

public:
	CStage();
	~CStage();
	bool LoadMapData(std::string mapFileName);
	bool LoadBKTexture();
	void Initialize(CEffectManager* pmng, CAudio* audio);
	void Update();
	bool Collision(CRectangle r, float& ox, float& oy);
	bool CollisionAttack(CRectangle r, float& ox, int type);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX(){ return m_ScrollX; }
	float GetScrollY(){ return m_ScrollY; }
	bool GetStageCollision() { return m_StCollision; }
	bool IsGoal() { return _player->IsGoal(); }
	bool IsPlayerDead() { return _player->IsDead(); }
	bool IsEnd() { return _player->IsEnd(); }
};