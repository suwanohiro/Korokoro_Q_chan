#pragma once

#include "Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"
#include	"Audio.h"


//#include "Character_Base.h"

#include "Gravity.h"

#include "EnemyShot.h"


class CEnemy{
private:
	//�G�̉摜
	CTexture* m_Texture;

	//�e�̉摜
	CTexture m_ShotTexture;

	CSpriteMotionController	m_Motion;


	//���W
	Vector2 m_Pos;
	//�ړ����x
	Vector2 m_Move;
	//�G�̃^�C�v
	int m_Type;
	//�G�̕\���t���O
	bool					m_bShow;
	bool					m_bReverse;
	bool					m_bMove;
	CRectangle				m_SrcRect;
	CRectangle				m_ShotRect;
	int						m_HP;
	int						m_DamageWait;

	//�e�̏����;
	const int				m_ShotMaxCount;

	CEffectManager*			m_pEffectManager;

	CAudio*					m_Audio;

	//���[�V������ޒ�`
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};

	//���ˊԊu
	int m_ShotWait;

	CEnemyShot* m_ShotArray;
	CGravity m_Gravity;


public:
	CEnemy();
	~CEnemy();
	bool Load(void);
	void Initialize(float px, float py, int type);
	void Update(void);
	bool ScreenCheck(float wx, float wy);
	void TypeCheck(Vector2 pPos, float wx, float wy);
	void Attack01(Vector2 pPos,float wx,float wy);
	void Attack02(float wx, float wy);
	void CollisionStage(float ox, float oy);
	void Damage(int dmg, bool bRev);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);

	void SetTexture(CTexture* pt) { m_Texture = pt; }
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	void SetShotShow(bool* bs, int i) { m_ShotArray[i].SetShow(bs); }
	void SetAudio(CAudio* audio) { m_Audio = audio; }

	bool GetShow(void) { return m_bShow; }
	int  GetDamageWait(void) { return m_DamageWait; }
	CRectangle GetRect() {
		return CRectangle(m_Pos.x + 10, m_Pos.y + 10, m_Pos.x + m_SrcRect.GetWidth() - 10, m_Pos.y + m_SrcRect.GetHeight());
	}
	CRectangle GetShotRect(int i) { return m_ShotArray[i].GetRect(); }
	int GetShotCount() { return m_ShotMaxCount; }
	bool GetShotShow(int i) { return m_ShotArray[i].GetShow(); }
};

using spCEnemy = std::shared_ptr<CEnemy>;