#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"Enemy.h"
#include	"EffectManager.h"
#include	"Item.h"
#include	"PlayerShot.h"
#include	"Gravity.h"
#include	"PlayerUI.h"
#include	"Audio.h"

//�v���C���[�̃X�s�[�h
constexpr float PLAYER_SPEED = 3.0f;
//�v���C���[�̃}�b�N�X�X�s�[�h
constexpr float PLAYER_MAXSPEED = 10.0f;
//�v���C���[�̃W�����v����
constexpr float PLAYER_JUMP = -10.0f;
//�U�����̉���
constexpr int		PLAYER_ATTACKWIDTH = 30;
//�����蔻�茸����
constexpr int		PLAYER_RECTDECREASE = 12;

//HP�񕜗�
constexpr float		ADD_HP = 0.05f;// * 10000


//�e�̔��ˌ��E��
constexpr int		PLAYERSHOT_COUNT = 2;
//�e�̔��ˊԊu
constexpr int		PLAYERSHOT_WAIT = 20;


class CPlayer
{
protected:
	/// <summary>
	/// �L�����N�^�[�摜
	/// </summary>
	CTexture m_CharacterImage;

	/// <summary>
	/// ���W
	/// </summary>
	Vector2 m_Position;

	/// <summary>
	/// �����蔻��
	/// </summary>
	CRectangle m_HitBox;

private:
	CSpriteMotionController	m_Motion;
	bool					m_bMoveX;
	bool					m_bMoveY;
	Vector2					m_Move;
	//�ǂł̓���
	float					m_WallMove;
	//�ǂł̓����̗L��
	bool					m_bWallMove;

	bool					m_bJump;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	//�e���łĂ邩�ǂ���
	bool					m_bShot;

	float					m_HP;
	float					m_MaxHP;
	int						m_DamageWait;



	CEffectManager* m_pEffectManager;

	CEffect* m_pEndEffect;

	bool					m_bDead;

	bool					m_bEnd;

	bool					m_bGoal;

	bool					m_bStCollision;
	bool					m_bPlayerHit;
	bool					m_bEnemyHit;

	//�Ǘp�����蔻�茸����
	int						m_PlayerWallRec;

	//���[�V������ޒ�`
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_ATTACK,
		MOTION_ATTACK2,
		MOTION_DAMAGE,
		MOTION_WALLMOVE,

		MOTION_COUNT,
	};

	enum class KeyContents {
		LEFTMOVE = MOFKEY_LEFT,
		RIGHTMOVE = MOFKEY_RIGHT,
		ATTACK = MOFKEY_S,
		ATTACK2 = MOFKEY_D,
		JUMP = MOFKEY_A,
		WALLUPMOVE = MOFKEY_UP,
		WALLDOWNMOVE = MOFKEY_DOWN
	};

	CTexture				m_ShotTexture;
	CPlayerShot				m_ShotArray[PLAYERSHOT_COUNT];
	int						m_ShotWait;

	CGravity				m_Gravity;
	CPlayerUI				m_PlayerUI;

	CAudio* m_Audio;

public:
	CPlayer();
	~CPlayer();
	/// <summary>
	/// �ǂݍ��ݏ���
	/// </summary>
	//virtual bool 
	bool Load(void);
	/// <summary>
	/// ����������
	/// </summary>
	//virtual 
	void Initialize(void);

	/// <summary>
	/// �X�V����
	/// </summary>
	//virtual
	void Update(float wx);
	void UpdateKey(void);
	void UpdateMove(void);

	void CollisionStage(float ox, float oy);
	void NotCollisionStage() {
		//m_bWallMove = false;
		m_bStCollision = false;
	}
	void CollisionStageAttackLeft();
	void CollisionStageAttackRight();
	bool CollisionEnemy(CEnemy& ene);
	bool CollisionItem(CItem& itm);

	void Damage(bool hit);

	void UpdateUI(void);

	/// <summary>
	/// �`�揈��
	/// </summary>
	//virtual 
	void Render(float wx, float wy);
	//Game.cpp�ŃX�e�[�W�̒l�����炤
	void RenderShot(float wx);

	void RenderUI(void);

	void RenderDebug(float wx, float wy);

	/// <summary>
	/// �������
	/// </summary>
	//virtual
	void Release(void);

	bool IsAttack() { return m_Motion.GetMotionNo() == MOTION_ATTACK; }
	bool IsAttack2() { return m_Motion.GetMotionNo() == MOTION_ATTACK2; }
	bool IsDead(void) { return m_bDead; }
	bool IsEnd(void) { return m_bEnd; }
	bool IsGoal(void) { return m_bGoal; }

	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	void SetAudio(CAudio* audio);
	void SetStCollision(bool flg) { m_bStCollision = flg; }
	void SetPos(Vector2 pos) { m_Position = pos; }
	void SetPos(float x, float y) { m_Position = Vector2(x, y); }
	Vector2 GetPos() { return m_Position; }

	void SetHP(float value) { m_HP = value; }

	CRectangle GetAttackRect() {
		//�����Ԃ��悤�ɂ���
		//���]��
		if (m_bReverse)
		{
			m_HitBox = CRectangle(m_Position.x + PLAYER_ATTACKWIDTH, m_Position.y,
				m_Position.x, m_Position.y + m_SrcRect.GetHeight());
			return m_HitBox;
		}
		m_HitBox = CRectangle(m_Position.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH, m_Position.y,
			m_Position.x + m_SrcRect.GetWidth(), m_Position.y + m_SrcRect.GetHeight());
		return m_HitBox;
	}


	/// <summary>
	/// �L�����N�^�[�̓����蔻��̋�`��Ԃ�
	/// </summary>
	/// <returns>�L�����N�^�[�̓����蔻��̋�`</returns>
	CRectangle getHitBox();
	CRectangle getAttackBox();
	//�����Ԃ��悤�ɂ���
	/*if (IsAttack())
	{
		return CRectangle(m_Position.x + PLAYER_RECTDECREASE, m_Position.y + PLAYER_RECTDECREASE,
			m_Position.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH, m_Position.y + m_SrcRect.GetHeight());
	}
	return CRectangle(m_Position.x + PLAYER_RECTDECREASE, m_Position.y + PLAYER_RECTDECREASE,
		m_Position.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_Position.y + m_SrcRect.GetHeight());*/

		/*float getGravity() {
			return 0.3f;
		}*/

	float getReverse() { return m_bReverse; }

	Vector2 getPosition() {
		return Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f, m_Position.y + m_SrcRect.GetHeight() * 0.5f);
	}

};

using spCPlayer = std::shared_ptr<CPlayer>;
