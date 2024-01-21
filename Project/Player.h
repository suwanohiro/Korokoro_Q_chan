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

//プレイヤーのスピード
constexpr float PLAYER_SPEED = 3.0f;
//プレイヤーのマックススピード
constexpr float PLAYER_MAXSPEED = 10.0f;
//プレイヤーのジャンプ初速
constexpr float PLAYER_JUMP = -10.0f;
//攻撃時の横幅
constexpr int		PLAYER_ATTACKWIDTH = 30;
//当たり判定減衰幅
constexpr int		PLAYER_RECTDECREASE = 12;

//HP回復量
constexpr float		ADD_HP = 0.05f;// * 10000


//弾の発射限界数
constexpr int		PLAYERSHOT_COUNT = 2;
//弾の発射間隔
constexpr int		PLAYERSHOT_WAIT = 20;


class CPlayer
{
protected:
	/// <summary>
	/// キャラクター画像
	/// </summary>
	CTexture m_CharacterImage;

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 m_Position;

	/// <summary>
	/// 当たり判定
	/// </summary>
	CRectangle m_HitBox;

private:
	CSpriteMotionController	m_Motion;
	bool					m_bMoveX;
	bool					m_bMoveY;
	Vector2					m_Move;
	//壁での動き
	float					m_WallMove;
	//壁での動きの有無
	bool					m_bWallMove;

	bool					m_bJump;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	//弾が打てるかどうか
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

	//壁用当たり判定減衰幅
	int						m_PlayerWallRec;

	//モーション種類定義
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
	/// 読み込み処理
	/// </summary>
	//virtual bool 
	bool Load(void);
	/// <summary>
	/// 初期化処理
	/// </summary>
	//virtual 
	void Initialize(void);

	/// <summary>
	/// 更新処理
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
	/// 描画処理
	/// </summary>
	//virtual 
	void Render(float wx, float wy);
	//Game.cppでステージの値をもらう
	void RenderShot(float wx);

	void RenderUI(void);

	void RenderDebug(float wx, float wy);

	/// <summary>
	/// 解放処理
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
		//判定を返すようにする
		//反転中
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
	/// キャラクターの当たり判定の矩形を返す
	/// </summary>
	/// <returns>キャラクターの当たり判定の矩形</returns>
	CRectangle getHitBox();
	CRectangle getAttackBox();
	//判定を返すようにする
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
