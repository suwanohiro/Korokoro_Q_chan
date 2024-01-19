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
	//�e�N�X�`���̓ǂݍ���
	if (!m_CharacterImage.Load("Player.png")) {
		return false;
	}

	//�e�̃e�N�X�`���i�ǂݍ��݂͈�ł��ׂĂ̒e�Ƀ|�C���^��ݒ�j
	if (!m_ShotTexture.Load("P_missile.png"))
	{
		return false;
	}
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}

	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"�ړ�",
			0,70,
			60,64,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"�W�����v�J�n",
			0,140,
			60,64,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"�W�����v�I��",
			240,140,
			60,64,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"�U��",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		{
			"�U��2",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		{
			"�_���[�W",
			480,0,
			60,64,
			FALSE,{{20,0,0},}
		},
		{
			"�Ǖ���",
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
	//HP���Ȃ��Ȃ�Ɣ����̏I����ҋ@���ďI��
	if (m_HP <= 0) {
		if (!m_pEndEffect || !m_pEndEffect->GetShow()) {
			m_bDead = true;
			m_PlayerUI.UpdateLife(m_bEnd);
		}
		return;
	}
	//�ړ��t���O�@�ړ�������������ۑ�
	m_bMoveX = false;
	m_bMoveY = false;
	//�U�����A���n�̏ꍇ�̓���
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_ATTACK2 || m_Motion.GetMotionNo() == MOTION_JUMPEND) {
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion()) {
			m_Motion.ChangeMotion(MOTION_WAIT);
			m_bPlayerHit = false;
		}
	}
	//�_���[�W���̓���
	else if (m_Motion.GetMotionNo() == MOTION_DAMAGE) {
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion()) {
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else {
		//�L�[���͂ɂ�铮��
		UpdateKey();
	}
	//�ړ��X�V
	UpdateMove();
	//���ۂɍ��W���ړ�������
	m_Position.x += m_Move.x;
	//m_Position.y += m_Move.y + m_WallMove;
	m_Position.y += m_Move.y;

	//�ړ�SE�𗬂�
	if (!m_Audio->IsPlay(Audio_PlayerMove) && m_bStCollision && (m_Move.x != 0 || (m_bWallMove && m_Move.y != 0))) {
		m_Audio->Play(Audio_PlayerMove, true);
	}
	else if (!m_bStCollision || (!m_bWallMove && m_Move.x == 0) || m_Move.y == 0 || (!m_bWallMove && m_bJump)) {
		m_Audio->Stop(Audio_PlayerMove);
	}

	//�e�̔���
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
				//�����ƃW���X�g
				if (m_bReverse) {
					m_ShotArray[i].Fire(m_Position.x, m_Position.y, m_bReverse);
				}
				else {
					m_ShotArray[i].Fire(m_Position.x + (m_CharacterImage.GetWidth() / 8) * 0.5f, m_Position.y, m_bReverse);
				}
				
				/*�ő�HP�����炷*/
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
	//�e�̍X�V
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}

	//��b���Ƃ�HP���񕜂�����
	if (m_HP < m_MaxHP) {
		while (true)
		{
			m_HP += ADD_HP;
			break;
		}
	}
	

	//��ʊO�ŗ����Ƃ���HP��0�ɂ���
	if (m_Position.y >= g_pGraphics->GetTargetHeight() && m_HP > 0) {
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f,
			m_Position.y + m_SrcRect.GetHeight() * 0.5f), EFC_OFFPLAYER);
		//���SSE�𗬂�
		m_Audio->Play(Audio_PlayerDead, false);
	}
	//�n�ʂɐڐG����ƃW�����v�I���i���������ʉ��[�Œ�~����悤�ɐݒ肷��j
	if (m_Position.y + m_SrcRect.GetHeight() >= g_pGraphics->GetTargetHeight()) {
		m_Position.y = g_pGraphics->GetTargetHeight() - m_SrcRect.GetHeight();
		m_Move.y = 0;
		if (m_bJump) {
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0) {
		m_DamageWait--;
	}

	

}

void CPlayer::UpdateKey(void)
{
	//�L�[�{�[�h�ړ�
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

	//A�L�[�ŃV�����v�[
	//���ӓ_�F�󒆂ł��W�����v�ł��Ă��܂�s
	if (g_pInput->IsKeyHold((int)KeyContents::JUMP) && !m_bJump && !m_bWallMove && m_bStCollision) {
		m_bJump = true;
		m_bStCollision = false;
		m_Move.y = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
		//�W�����vSE�𗬂�
		m_Audio->Play(Audio_PlayerJump, false);
	}
	//S�L�[�ōU��1
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK) && !m_bWallMove && m_ShotWait <= 0) {
		m_Motion.ChangeMotion(MOTION_ATTACK);
		m_bShot = true;
		//�U��1SE�𗬂�
		m_Audio->Play(Audio_PlayerAttack_1, false);
	}
	//D�L�[�ōU��2
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK2) && !m_bWallMove) {
		m_Motion.ChangeMotion(MOTION_ATTACK2);
		//�U��2SE�𗬂�
		m_Audio->Play(Audio_PlayerAttack_2, false);
	}
	//�ǂɍU�����������ď㉺�ɓ���
	if (g_pInput->IsKeyHold((int)KeyContents::WALLUPMOVE) && m_bWallMove) {


		m_bMoveY = true;
		m_Move.y -= m_WallMove;
		if (m_Move.y <= -1.0f) {
			m_Move.y = -1.0f;
		}
		//TODO:�l�͕ς���@��ʏ�O�ɂ����Ɩ߂�
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
	//���̃t���[���ł̈ړ����͂��Ȃ���Ό������������s
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
	//�ǂɒ���t���Ă�Ƃ��Ƃ��Ȃ��Ƃ��̋��
	if (!m_bWallMove) {
		//�d�͂ŉ�����
		m_Gravity.Gravity(m_Move.y);
		
	}
	else {
		if (m_bReverse) {
			m_Move.x -= 5.0f;
		}
		else if(!m_bReverse)
		m_Move.x += 5.0f;
	}

	//�ǂɒ���t���Ă���Ƃ��ɓG�Ɠ��������Ƃ�
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE && m_bWallMove) {
		m_bWallMove = false;
	}
	
}

void CPlayer::CollisionStage(float ox, float oy)
{
	m_Position.x += ox;
	m_Position.y += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������
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
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if (ox < 0 && m_Move.x > 0) {
		m_Move.x = 0;
	}
	else if (ox > 0 && m_Move.x < 0) {
		m_Move.x = 0;
	}
	//�ǂɒ���t���Ă���Ƃ��ɍU���{�^���������ƕǂ��甍�����
	if (g_pInput->IsKeyPush((int)KeyContents::ATTACK2) && m_bWallMove) {
		m_bWallMove = false;
		m_Motion.ChangeMotion(MOTION_JUMPEND);
	}
	//�U��2�̏ꍇ�U�����[�V�������I����Ă��璣��t��
	if (m_Motion.IsEndMotion() && m_Motion.GetMotionNo() == MOTION_ATTACK2 && m_bWallMove) {
		m_Motion.ChangeMotion(MOTION_WALLMOVE);
	}
}

void CPlayer::CollisionStageAttackLeft()
{
	//�v���C���[���ǂɒ���t���ď�ɓ���***********************************************************************
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
	//�v���C���[���ǂɒ���t���ď�ɓ���
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
	//HP���Ȃ��Ȃ�Ɠ����蔻�肵�Ȃ�
	if (m_HP <= 0) {
		return false;
	}
	//�G���_���[�W���̂��ߓ����蔻����s��Ȃ�
	if (ene.GetDamageWait() > 0&&ene.GetShow()) {
		m_bEnemyHit = true;
	}
	//�v���C���[���_���[�W���̂��߂����蔻����s��Ȃ�
	if (m_DamageWait > 0 || !ene.GetShow()) {
		m_bPlayerHit = true;
	}
	else if (m_bPlayerHit) {
		m_bPlayerHit = false;
	}
	//�e�Ƃ̔���
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
			//�U��
			if (m_Motion.GetMotionNo() == MOTION_ATTACK2) {
				//�G�̋�`�Ǝ����̍U����`�œG���_���[�W
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
		//�G���`�悳��Ă��邩
		if (!ene.GetShow()) {
			return false;
		}
		//�G�̋�`�Ǝ����̋�`�Ń_���[�W
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
		//�G�̒e��`�Ǝ����̋�`�Ń_���[�W
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
	//�U�����̏ꍇ�̂ݍU���Ƃ̂����蔻������s
	if ((m_Motion.GetMotionNo() != MOTION_ATTACK) || (m_Motion.GetMotionNo() != MOTION_ATTACK2)) {
		return false;
	}
	//�G�̋�`�Ǝ����̍U����`�œG���_���[�W
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
		//�A�C�e���擾SE�𗬂�

		switch (itm.GetType())
		{
		case ItemType::Recover:
			//��SE�𗬂�
			m_Audio->Play(Audio_Heel, false);
			m_HP += 30;
			if (m_HP >= m_MaxHP) {
				m_HP = m_MaxHP;
			}
			break;
		case ItemType::WayPoint:	//TODO �A�C�e������ꎞ�I�ɕύX	
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
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(
			Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f,
				m_Position.y + m_SrcRect.GetHeight() * 0.5f), EFC_OFFPLAYER);
		//���SSE�𗬂�
		m_Audio->Play(Audio_PlayerDead, false);
	}
	else {
		//�_���[�W�G�t�F�N�g����
		m_pEffectManager->Start(Vector2(m_Position.x + m_SrcRect.GetWidth() * 0.5f,
			m_Position.y + m_SrcRect.GetHeight() * 0.5f), EFC_DAMEGE);
		//�_���[�WSE�𗬂�
		m_Audio->Play(Audio_PlayerDamege, false);
	}
}

void CPlayer::UpdateUI(void)
{
	m_PlayerUI.UpdateHp(m_MaxHP, m_HP);
}



void CPlayer::Render(float wx, float wy)
{
	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2) {
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//�`��ʒu
	float px = m_Position.x - wx;
	float py = m_Position.y - wy;
	//���]�t���O��ON�̏ꍇ�`���`���]
	if (m_bReverse) {
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_ATTACK2) {
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//�`��
	m_CharacterImage.Render(px, py, dr);

}

void CPlayer::RenderShot(float wx)
{
	//�e�̕`��
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
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10, 70, "�v���C���[�ʒu X : %.0f , Y : %.0f", m_Position.x, m_Position.y);
	//�����蔻��̕\��
	CRectangle hr = getHitBox();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));
	//�U���̓����蔻��\��
	if (IsAttack() || IsAttack2())
	{
		CRectangle hr = GetAttackRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	}

	//�e�̕`��
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
	//�����Ԃ��悤�ɂ���
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
	//�����Ԃ��悤�ɂ���
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

