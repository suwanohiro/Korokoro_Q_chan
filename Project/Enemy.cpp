#include "Enemy.h"

CEnemy::CEnemy():
m_Texture(NULL),
m_Motion(),
m_Pos(Vector2(0,0)),
m_Move(Vector2(0,0)),
m_Type(),
m_bShow(false),
m_ShotWait(0),
m_HP(10),
m_DamageWait(0),
m_bReverse(false),
m_bMove(false),
m_SrcRect(),
m_ShotMaxCount(10),
m_pEffectManager(),
m_ShotArray(),
m_Gravity()
{
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load(void)
{
	m_ShotArray = new CEnemyShot[m_ShotMaxCount];
	if (!m_ShotTexture.Load("E_missile.png")) {
		return false;
	}
	for (int i = 0; i < m_ShotMaxCount; i++) {
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}
	return true;
}

void CEnemy::Initialize(float px, float py, int type)
{
	m_Pos = Vector2(px, py);
	m_Type = type;
	m_Move = Vector2(-3.0f, 0);
	m_bShow = true;
	m_bReverse = true;
	m_bMove = false;
	m_HP = 10;
	m_DamageWait = 0;
	
	for (int i = 0; i < m_ShotMaxCount; i++) {
		m_ShotArray[i].Initialize();
	}

	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,60,64,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"�ړ�",
			0,0,60,64,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"�_���[�W",0,210,60,64,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

void CEnemy::Update(void)
{
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE) {
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion()) {
			m_Motion.ChangeMotion(MOTION_WAIT);
			if (m_HP <= 0) {
				m_bShow = false;
				//�����G�t�F�N�g�𔭐�������
				m_pEffectManager->Start(Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f), EFC_OFFENEMY);
				//���SSE�𗬂�
				m_Audio->Play(Audio_EnemyDead, false);
			}
			m_Move.x = ((m_bReverse) ? -3.0f : 3.0f);
		}
		else {
			if (m_Move.x > 0) {
				m_Move.x -= 0.2f;
				if (m_Move.x <= 0) {
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0) {
				m_Move.x += 0.2f;
				if (m_Move.x >= 0) {
					m_Move.x = 0;
				}
			}
		}
	}
	
	//�ړ�SE�𗬂�
	/*if (m_bMove && !m_Audio->IsPlay(Audio_EnemyMove)) {
		int volume = 10;
		m_Audio->SetVolume(volume);
		m_Audio->Play(Audio_EnemyMove, false);
	}
	else if (!m_bMove) {
		m_Audio->Stop(Audio_EnemyDead);
	}*/

	//�d�͏���
	m_Gravity.Gravity(m_Move.y);
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0) {
		m_DamageWait--;
	}
}

bool CEnemy::ScreenCheck(float wx, float wy)
{
	//�X�N���[����
	float sw = wx + CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	float sh = wy + CGraphicsUtilities::GetGraphics()->GetTargetHeight();

	//�G����ʂɉf���Ă��邩�ǂ���
	if (m_Pos.x + m_SrcRect.GetWidth() > wx && sw > m_Pos.x) {
		return true;
	}
	else {
		return false;
	}
}

void CEnemy::TypeCheck(Vector2 pPos, float wx, float wy)
{
	switch (m_Type) {
	case 0: {
		//�G1�̏ꍇ
		Attack01(pPos, wx, wy);
		break;
	}
	case 1: {
		//�G2�̏ꍇ
		Attack02(wx, wy);
		break;
	}
	}
}

void CEnemy::Attack01(Vector2 pPos, float wx, float wy)
{
	for (int i = 0; i < m_ShotMaxCount; i++) {
		if (!m_ShotArray[i].GetShow()) {
			continue;
		}
		m_ShotArray[i].Update(wx, wy);
	}

	//��ʓ����ǂ����`�F�b�N
	if (!ScreenCheck(wx, wy)){ return; }

	//�v���C���[�̕����Ɍ�����
	if (m_Pos.x + m_Motion.GetSrcRect().GetWidth() * 0.5f < pPos.x) {
		m_bReverse = false;
	}
	else {
		m_bReverse = true;
	}

	if (m_DamageWait <= 0 && m_ShotWait <= 0) {
		for (int i = 0; i < m_ShotMaxCount; i++) {
			if (m_ShotArray[i].GetShow()) {
				continue;
			}
			m_ShotWait = 120;
			m_ShotArray[i].AdvSet(pPos, m_Pos.x + GetRect().GetWidth() * 0.5, m_Pos.y + GetRect().GetHeight() * 0.5);
			//�U��SE�𗬂�
			m_Audio->Play(Audio_EnemyAttack, false);
			break;
		}
	}
	else {
		m_ShotWait--;
	}
}

void CEnemy::Attack02(float wx, float wy)
{
	//��ʓ����ǂ���
	if (!ScreenCheck(wx, wy)) { return; }

	if (m_Motion.GetMotionNo() == MOTION_WAIT) {
		m_Motion.ChangeMotion(MOTION_MOVE);
	}
	m_bMove = true;
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
}

void CEnemy::CollisionStage(float ox, float oy) {
	m_Pos.x += ox;
	m_Pos.y += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_Move.x > 0)
	{
		m_Move.x *= -1;
		m_bReverse = true;
	}
	else if (ox > 0 && m_Move.x < 0)
	{
		m_Move.x *= -1;
		m_bReverse = false;
	}
}

void CEnemy::Damage(int dmg, bool bRev)
{
	m_bMove = false;
	m_HP -= dmg;
	m_DamageWait = 60;
	if (bRev) {
		m_Move.x = -5.0f;
		m_bReverse = false;
	}
	else {
		m_Move.x = 5.0f;
		m_bReverse = true;
	}
	m_Motion.ChangeMotion(MOTION_DAMAGE);
	//�_���[�W�G�t�F�N�g�𔭐�������
	m_pEffectManager->Start(Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f), EFC_DAMEGE);
	//�_���[�WSE�𗬂�
	m_Audio->Play(Audio_EnemyDamege, false);
}

void CEnemy::Render(float wx, float wy) {
	//�e�̕`��
	for (int i = 0; i < m_ShotMaxCount; i++) {
		if (!m_ShotArray[i].GetShow()) { continue; }
		m_ShotArray[i].Render(wx, wy);
	}

	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2) {
		return;
	}
	//�`���`
	CRectangle dr = m_SrcRect;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_Texture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
	
}

void CEnemy::RenderDebug(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));
	for (int i = 0; i < m_ShotMaxCount; i++) {
		m_ShotArray[i].RenderDebug(wx, wy);
	}
}

void CEnemy::Release(void) {
	m_Motion.Release();
}
