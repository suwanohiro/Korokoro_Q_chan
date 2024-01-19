#include "Player.h"

CPlayer::CPlayer():
	m_CharacterImage(),
	m_Motion(),
	m_Position(0, 0),
	m_bMoveX(false),
	m_bMoveY(false),
	m_Move(0,0),
	m_WallMove(1.0f),
	m_bWallMove(false),
	m_bJump(false),
	m_bReverse(false),
	m_bShot(false),
	m_HP(100),
	m_MaxHP(100),
	m_DamageWait(0),
	m_pEffectManager(),
	m_pEndEffect(),
	m_bDead(false),
	m_bEnd(false),
	m_bGoal(false),
	m_bStCollision(false),
	m_bPlayerHit(false),
	m_bEnemyHit(false),
	m_SrcRect(),
	m_ShotTexture(),
	m_ShotArray(),
	m_ShotWait(),
	m_PlayerWallRec(0)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load(void)
{
	//テクスチャの読み込み
	if (!m_CharacterImage.Load("Player.png")) {
		return false;
	}

	//弾のテクスチャ（読み込みは一つですべての弾にポインタを設定）
	if (!m_ShotTexture.Load("P_missile.png"))
	{
		return false;
	}
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}

	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		{
			"待機",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"移動",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"ジャンプ開始",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"ジャンプ終了",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"攻撃",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		{
			"攻撃2",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		{
			"ダメージ",
			480,0,
			60,64,
			FALSE,{{20,0,0},}
		},
		{
			"壁歩き",
			0,140,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);

	if (!m_PlayerUI.Load()) { return false; }

	return true;
}


void CPlayer::Initialize(void)
{
	m_PlayerUI.Initializ(m_bEnd);
	
	m_Position = Vector2(200, 0);
	m_bMoveX = false;
	m_bMoveY = false;
	m_Move = Vector2(0, 0);
	m_WallMove = 1.0f;
	m_bWallMove = false;
	m_bReverse = false;
	m_bJump = false;
	m_bShot = false;
	m_HP = 100;
	m_MaxHP = 100;
	m_DamageWait = 0;
	m_bDead = false;
	m_bEnd = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_bStCollision = false;
	m_bEnemyHit = false;
	m_bPlayerHit = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
	m_PlayerWallRec = (m_Motion.GetSrcRect().Bottom - m_Motion.GetSrcRect().Top) * 0.5f;

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}


void CPlayer::Update(void)
{
	//HPがなくなると爆発の終了を待機して終了
	if (m_HP <= 0) {
		if (!m_pEndEffect || !m_pEndEffect->GetShow()) {
			m_bDead = true;
			m_PlayerUI.UpdateLife(m_bEnd);
		}
		return;
	}
	//移動フラグ　移動があったかを保存
	m_bMoveX = false;
	m_bMoveY = false;
	//攻撃中、着地の場合の動作
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_ATTACK2 || m_Motion.GetMotionNo() == MOTION_JUMPEND) {
		//終了で待機に戻す
		if (m_Motion.IsEndMotion()) {
			m_Motion.ChangeMotion(MOTION_WAIT);
			m_bPlayerHit = false;
		}
	}
	//ダメージ中の動作
	else if (m_Motion.GetMotionNo() == MOTION_DAMAGE) {
		//終了で待機に戻す
		if (m_Motion.IsEndMotion()) {
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else {
		//キー入力による動作
		UpdateKey();
	}
	//移動更新
	UpdateMove();
	//実際に座標を移動させる
	m_Position.x += m_Move.x;
	//m_Position.y += m_Move.y + m_WallMove;
	m_Position.y += m_Move.y;

	//移動SEを流す
	if (!m_Audio->IsPlay(Audio_PlayerMove) && m_bStCollision && (m_Move.x != 0 || (m_bWallMove && m_Move.y != 0))) {
		m_Audio->Play(Audio_PlayerMove, true);
	}
	else if (!m_bStCollision || (!m_bWallMove && m_Move.x == 0) || m_Move.y == 0 || (!m_bWallMove && m_bJump)) {
		m_Audio->Stop(Audio_PlayerMove);
	}

	//弾の発射
	if (m_ShotWait <= 0)
	{
		if (m_bShot)
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				if (m_ShotArray[i].GetShow())
				{
					continue;
				}
				m_ShotWait = PLAYERSHOT_WAIT;
				//+m_CharacterImage.GetWidth() * 0.5f
				//左だとジャスト
				if (m_bReverse) {
					m_ShotArray[i].Fire(m_Position.x, m_Position.y, m_bReverse);
				}
				else {
					m_ShotArray[i].Fire(m_Position.x + (m_CharacterImage.GetWidth() / 8) * 0.5f, m_Position.y, m_bReverse);
				}
				
				/*最大HPを減らす*/
				if (i == 1) {
					m_MaxHP = m_HP;
				}
				m_HP -= 10;
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
		m_bShot = false;
	}
	//弾の更新
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}

	//一秒ごとにHPを回復させる
	if (m_HP < m_MaxHP) {
		while (true)
		{
			m_HP += ADD_HP;
			break;
		}
	}
	

	//画面外で落下としてHPを0にする
	if (m_Position.y >= g_pGraphics->GetTargetHeight() && m_HP > 0) {
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f,
			m_Position.y + m_SrcRect.GetHeight() * 0.5f), EFC_OFFPLAYER);
		//死亡SEを流す
		m_Audio->Play(Audio_PlayerDead, false);
	}
	//地面に接触するとジャンプ終了（いったん画面下端で停止するように設定する）
	if (m_Position.y + m_SrcRect.GetHeight() >= g_pGraphics->GetTargetHeight()) {
		m_Position.y = g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight();
		m_Move.y = 0;
		if (m_bJump) {
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//ダメージのインターバルを減らす
	if (m_DamageWait > 0) {
		m_DamageWait--;
	}

	

}

void CPlayer::UpdateKey(void)
{
	//キーボード移動
	if (g_pInput->IsKeyHold((int)KeyContents::LEFTMOVE) && !m_bWallMove) {
		m_Move.x -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMoveX = true;
		if (m_Move.x < -PLAYER_MAXSPEED) {
			m_Move.x = -PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_WALLMOVE) {
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	else if (g_pInput->IsKeyHold((int)KeyContents::RIGHTMOVE) && !m_bWallMove) {
		m_Move.x += PLAYER_SPEED;
		m_bReverse = false;
		m_bMoveX = true;
		if (m_Move.x > PLAYER_MAXSPEED) {
			m_Move.x = PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT || m_Motion.GetMotionNo() == MOTION_WALLMOVE) {
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}

	//Aキーでシャンプー
	//注意点：空中でもジャンプできてしまうs
	if (g_pInput->IsKeyHold((int)KeyContents::JUMP) && !m_bJump && !m_bWallMove && m_bStCollision) {
		m_bJump = true;
		m_bStCollision = false;
		m_Move.y = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
		//ジャンプSEを流す
		m_Audio->Play(Audio_PlayerJump, false);
	}
	//Sキーで攻撃1
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK) && !m_bWallMove && m_ShotWait <= 0) {
		m_Motion.ChangeMotion(MOTION_ATTACK);
		m_bShot = true;
		//攻撃1SEを流す
		m_Audio->Play(Audio_PlayerAttack_1, false);
	}
	//Dキーで攻撃2
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK2) && !m_bWallMove) {
		m_Motion.ChangeMotion(MOTION_ATTACK2);
		//攻撃2SEを流す
		m_Audio->Play(Audio_PlayerAttack_2, false);
	}
	//壁に攻撃が当たって上下に動く
	if (g_pInput->IsKeyHold((int)KeyContents::WALLUPMOVE) && m_bWallMove) {


		m_bMoveY = true;
		m_Move.y -= m_WallMove;
		if (m_Move.y <= -1.0f) {
			m_Move.y = -1.0f;
		}
		//TODO:値は変える　画面上外にいくと戻す
		if (m_Position.y < 0) {//20
			m_Position.y = 0; 
		}
	

	}
	else if (g_pInput->IsKeyHold((int)KeyContents::WALLDOWNMOVE) && m_bWallMove == true) {

		m_bMoveY = true;
		
		m_Move.y += m_WallMove;
		if (m_Move.y >= 1.0f) {
			m_Move.y = 1.0f;
		}
	}
}

void CPlayer::UpdateMove(void)
{
	//このフレームでの移動入力がなければ減速処理を実行
	if (!m_bMoveX) {
		if (m_Move.x > 0) {
			m_Move.x -= PLAYER_SPEED;
			if (m_Move.x <= 0) {
				m_Move.x = 0;
			}
		}
		else if (m_Move.x < 0) {
			m_Move.x += PLAYER_SPEED;
			if (m_Move.x >= 0) {
				m_Move.x = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE) {
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	
	if (!m_bMoveY && m_bWallMove) {
		if (m_Move.y > 0) {
			m_Move.y -=m_WallMove;
			if (m_Move.y <= 0) {
				m_Move.y = 0;
			}
		}
		else if (m_Move.y < 0) {
			m_Move.y += m_WallMove;
			if (m_Move.y >= 0) {
				m_Move.y = 0;
			}
		}
	}
	//壁に張り付いてるときといないときの区別
	if (!m_bWallMove) {
		//重力で下がる
		m_Gravity.Gravity(m_Move.y);
		
	}
	else {
		if (m_bReverse) {
			m_Move.x -= 5.0f;
		}
		else if(!m_bReverse)
		m_Move.x += 5.0f;
	}

	//壁に張り付いているときに敵と当たったとき
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE && m_bWallMove) {
		m_bWallMove = false;
	}
	
}

void CPlayer::CollisionStage(float ox, float oy)
{
	m_Position.x += ox;
	m_Position.y += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する
	if (oy < 0 && m_Move.y > 0) {
		m_Move.y = 0;
		if (m_bJump) {
			m_bJump = false;
			m_bStCollision = true;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	else if (oy > 0 && m_Move.y < 0) {
		m_Move.y = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	if (ox < 0 && m_Move.x > 0) {
		m_Move.x = 0;
	}
	else if (ox > 0 && m_Move.x < 0) {
		m_Move.x = 0;
	}
	//壁に張り付いているときに攻撃ボタンを押すと壁から剥がれる
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK2) && m_bWallMove) {
		m_bWallMove = false;
		m_Motion.ChangeMotion(MOTION_JUMPEND);
	}
	//攻撃2の場合攻撃モーションが終わってから張り付く
	if (m_Motion.IsEndMotion() && m_Motion.GetMotionNo() == MOTION_ATTACK2 && m_bWallMove) {
		m_Motion.ChangeMotion(MOTION_WALLMOVE);
	}
}

void CPlayer::CollisionStageAttackLeft()
{
	//プレイヤーが壁に張り付いて上に動く***********************************************************************
	if (m_Motion.GetMotionNo() == MOTION_ATTACK2) {
		//m_Motion.ChangeMotion(MOTION_WALLMOVE);
		m_bWallMove = true;
		m_Move.x = -5.0f;
		m_Move.y = 0;
	}
	else {
		return;
	}

	
}

void CPlayer::CollisionStageAttackRight()
{
	//プレイヤーが壁に張り付いて上に動く
	if (m_Motion.GetMotionNo() == MOTION_ATTACK2) {
		//m_Motion.ChangeMotion(MOTION_WALLMOVE);
		m_bWallMove = true;
		m_Move.x = 5.0f;
		m_Move.y = 0;
	}
	else {
		return;
	}
}

bool CPlayer::CollisionEnemy(CEnemy& ene)
{
	//HPがなくなると当たり判定しない
	if (m_HP <= 0) {
		return false;
	}
	//敵がダメージ中のため当たり判定を行わない
	if (ene.GetDamageWait() > 0&&ene.GetShow()) {
		m_bEnemyHit = true;
	}
	//プレイヤーがダメージ中のためあたり判定を行わない
	if (m_DamageWait > 0 || !ene.GetShow()) {
		m_bPlayerHit = true;
	}
	else if (m_bPlayerHit) {
		m_bPlayerHit = false;
	}
	//弾との判定
	CRectangle erec = ene.GetRect();
	CRectangle prec = getHitBox();
	if (!m_bEnemyHit) {
		if (!ene.GetShow()) {
			return false;
		}
		for (int i = 0; i < PLAYERSHOT_COUNT; i++)
		{
			if (!m_ShotArray[i].GetShow())
			{
				continue;
			}
			CRectangle srec = m_ShotArray[i].GetRect();

			if (srec.CollisionRect(erec))
			{
				ene.Damage(5, m_bReverse);
				m_ShotArray[i].SetShow(false);
				break;
			}
			//攻撃
			if (m_Motion.GetMotionNo() == MOTION_ATTACK2) {
				//敵の矩形と自分の攻撃矩形で敵がダメージ
				prec = GetAttackRect();
				if (prec.CollisionRect(erec)) {
					ene.Damage(5, m_bReverse);
					return true;
				}
			}
		}
	}
	if (ene.GetDamageWait() == 0 && m_bEnemyHit) {
		m_bEnemyHit = false;
	}
	if (!m_bPlayerHit) {
		//敵が描画されているか
		if (!ene.GetShow()) {
			return false;
		}
		//敵の矩形と自分の矩形でダメージ
		if (prec.CollisionRect(erec)) {
			bool lefthit = false;
			if (prec.Left < erec.Left) {
				lefthit = true;
			}
			Damage(lefthit);
			return true;
		}
	}
	if (!m_bPlayerHit) {
		//敵の弾矩形と自分の矩形でダメージ
		bool lefthit = false;
		for (int i = 0; i < ene.GetShotCount(); i++) {
			if (!ene.GetShotShow(i)) {
				return false;
			}
			CRectangle srec = ene.GetShotRect(i);
			if (prec.CollisionRect(srec)) {
				if (prec.Left < srec.Left) {
					lefthit = true;
				}
				Damage(lefthit);
				ene.SetShotShow(false, i);
				return true;
			}
		}
		
	}
	/******************************************************************************************/
	
	/********************************************************************************************/
	//攻撃中の場合のみ攻撃とのあたり判定を実行
	if ((m_Motion.GetMotionNo() != MOTION_ATTACK) || (m_Motion.GetMotionNo() != MOTION_ATTACK2)) {
		return false;
	}
	//敵の矩形と自分の攻撃矩形で敵がダメージ
	prec = GetAttackRect();
	if (prec.CollisionRect(erec)) {
		ene.Damage(5, m_bReverse);
		return true;
	}

	return false;
}

bool CPlayer::CollisionItem(CItem& itm)
{
	if (!itm.GetShow()) {
		return false;
	}
	CRectangle prec = getHitBox();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec)) {
		itm.SetShow(false);
		//アイテム取得SEを流す

		switch (itm.GetType())
		{
		case ItemType::Recover:
			//回復SEを流す
			m_Audio->Play(Audio_Heel, false);
			m_HP += 30;
			if (m_HP >= m_MaxHP) {
				m_HP = m_MaxHP;
			}
			break;
		case ItemType::WayPoint:	//TODO アイテム判定一時的に変更	
			m_bGoal = true;
			break;
		case ItemType::Goal:
			m_bGoal = true;
			break;
		}

		
	}

	return false;
}

void CPlayer::Damage(bool hit)
{
	m_HP -= 20;
	m_DamageWait = 60;
	if (hit) {
		m_Move.x = -5.0f;
		m_bReverse = false;
	}
	else {
		m_Move.x = 5.0f;
		m_bReverse = true;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
	if (m_HP <= 0) {
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(
			Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f,
				m_Position.y + m_SrcRect.GetHeight() * 0.5f), EFC_OFFPLAYER);
		//死亡SEを流す
		m_Audio->Play(Audio_PlayerDead, false);
	}
	else {
		//ダメージエフェクト発生
		m_pEffectManager->Start(Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f,
			m_Position.y + m_SrcRect.GetHeight() * 0.5f), EFC_DAMEGE);
		//ダメージSEを流す
		m_Audio->Play(Audio_PlayerDamege, false);
	}
}

void CPlayer::UpdateUI(void)
{
	m_PlayerUI.UpdateHp(m_MaxHP, m_HP);
}



void CPlayer::Render(float wx, float wy)
{
	//インターバル2フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2) {
		return;
	}
	//描画矩形
	CRectangle dr = m_SrcRect;
	//描画位置
	float px = m_Position.x - wx;
	float py = m_Position.y - wy;
	//反転フラグがONの場合描画矩形反転
	if (m_bReverse) {
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_ATTACK2) {
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//描画
	m_CharacterImage.Render(px, py, dr);

}

void CPlayer::RenderShot(float wx)
{
	//弾の描画
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render(wx);
	}
}

void CPlayer::RenderUI(void)
{
	m_PlayerUI.Render(m_CharacterImage);
}

void CPlayer::RenderDebug(float wx, float wy)
{
	//位置の描画
	CGraphicsUtilities::RenderString(10, 70, "プレイヤー位置 X : %.0f , Y : %.0f", m_Position.x, m_Position.y);
	//当たり判定の表示
	CRectangle hr = getHitBox();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	//攻撃の当たり判定表示
	if (IsAttack() || IsAttack2())
	{
		CRectangle hr = GetAttackRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	}

	//弾の描画
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug();
	}

	if (m_bPlayerHit)
		CGraphicsUtilities::RenderString(10, 120, "true");
	else CGraphicsUtilities::RenderString(10, 120, "false");
}

void CPlayer::Release(void)
{
	m_CharacterImage.Release();
	m_Motion.Release();

	m_ShotTexture.Release();

	m_PlayerUI.Release();
}

CRectangle CPlayer::getHitBox()
{
	//判定を返すようにする
		if (IsAttack() || IsAttack2())
		{
			m_HitBox = CRectangle(m_Position.x + PLAYER_RECTDECREASE, m_Position.y + PLAYER_RECTDECREASE,
				m_Position.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH, m_Position.y + m_SrcRect.GetHeight());
			return m_HitBox;
		}
		m_HitBox = CRectangle(m_Position.x + PLAYER_RECTDECREASE, m_Position.y + PLAYER_RECTDECREASE,
			m_Position.x + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE, m_Position.y + m_SrcRect.GetHeight());
	return m_HitBox;
}

CRectangle CPlayer::getAttackBox()
{
	CRectangle rec;
	//判定を返すようにする
	if (IsAttack2())
	{
		if (m_bReverse) {
			rec = CRectangle(m_Position.x - PLAYER_ATTACKWIDTH,
				m_Position.y + m_PlayerWallRec,
				m_Position.x + 12,
				m_Position.y + m_SrcRect.GetHeight());
		}
		else {
			rec = CRectangle(m_Position.x + m_SrcRect.GetWidth() - PLAYER_ATTACKWIDTH - 12,
				m_Position.y + m_PlayerWallRec,
				m_Position.x + m_SrcRect.GetWidth(),
				m_Position.y + m_SrcRect.GetHeight());
		}
		return rec;
	}
	rec = CRectangle(0, 0, 0, 0);
	return rec;
}

