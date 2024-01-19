#pragma once

#include	"Mof.h"
#include	"Gravity.h"

//�A�C�e���̎��
enum tag_ITEMTYPE {
	ITEM_RECOVER,		//��
	ITEM_WAYPOINT,		//���Ԓn�_
	ITEM_GOAL,			//�S�[��	

	ITEM_COUNT,
};

enum class ItemType {
	Recover,
	WayPoint,
	Goal
};

class CItem {
protected:
	ItemType				m_ItemType;
	CTexture*				m_itemTexture;
	CSpriteMotionController	m_Motion;
	Vector2					m_pos = {0,0};
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
	CGravity				m_Gravity;

public:
	CItem();
	~CItem();
	void Initialize(float px, float py, int typee);						//������
	void Update(void);													//�X�V
	void CollisionStage(float oy);										//�X�e�[�W�ƏՓ˂����ۂ̕␳����
	void Render(float wx, float wy);									//�`��
	void RenderDebug(float wx, float wy);
	void Release(void);													//���

	void SetTexture(CTexture* pt) { m_itemTexture = pt; }				//�e�N�X�`���̐ݒ�
	void SetShow(bool flg) { m_bShow = flg; }							// �\����Ԃ�ݒ肷��
	bool GetShow(void) { return m_bShow; }								//�A�C�e���̕\���L��
	CRectangle GetRect();												//�������`
	ItemType GetType() { return m_ItemType; }							//�A�C�e���̎��
};

using spCItem = std::shared_ptr<CItem>;