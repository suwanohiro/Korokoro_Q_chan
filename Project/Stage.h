#pragma once

#include "./swnLibrary/swnLibrary.h"


#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"



//ç∂åXéŒÉ`ÉbÉv
#define		LEFTSLOPE	2

class CStage {
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;
	CTexture*				m_pEnemyTexture;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char*					m_pChipData;

	int						m_EnemyTextureCount;
	char*					m_pEnemyData;
	int						m_EnamyCount;

	float					m_ScrollX;
	float					m_ScrollY;

	int						m_ItemTextureCount;
	CTexture*				m_pItemTexture;
	char*					m_pItemData;
	int						m_ItemCount;
	bool					m_StCollision;

public:
	CStage();
	~CStage();
	bool Load(char* pName);
	void Initialize(CEnemy* pEnemy,CItem* pItem);
	void Update(CPlayer& pl);
	bool Collision(CRectangle r, float& ox, float& oy);
	bool CollisionAttack(CRectangle r, float& ox, int type);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	float GetScrollX(){ return m_ScrollX; }
	float GetScrollY(){ return m_ScrollY; }
	int GetEnemyCount() { return m_EnamyCount; }
	int GetItemCount() { return m_ItemCount; }
	bool GetStageCollision() { return m_StCollision; }
};