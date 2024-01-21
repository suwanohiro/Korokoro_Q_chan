#include	"PlayerShot.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayerShot::CPlayerShot() :
	m_pTexture(NULL),
	m_Position(0, 0),
	m_bShow(false),
	m_Reverse(false) {
}

/**
 * �f�X�g���N�^
 *
 */
CPlayerShot::~CPlayerShot() {
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 */
void CPlayerShot::Initialize(void) {
	m_Position = Vector2(0, 0);
	m_bShow = false;
	SpriteAnimationCreate shotanim = {
	"����",
	0,0,
	120,96,
	TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
	};

	m_ShotMotion.Create(shotanim);
}
/**
 * ����
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 */
void CPlayerShot::Fire(float px, float py, bool r) {
	m_Position.x = px - m_pTexture->GetWidth() * 0.5f;
	m_Position.y = py + m_pTexture->GetHeight() * 0.5f;
	m_bShow = true;
	m_Reverse = r;
}

/**
 * �X�V
 *
 */
void CPlayerShot::Update(void) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�E�̎��ɉE�ɔ��ˁA���̎��ɍ��ɔ��˂ɕς���*******************************************************************

	if (m_Reverse) {
		m_Position.x -= PLAYERSHOT_SPEED;
	}
	else {
		m_Position.x += PLAYERSHOT_SPEED;
	}

	m_ShotMotion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcShotRect = m_ShotMotion.GetSrcRect();
	//��ʏ��荶�ŏ���
	//+ m_pTexture->GetWidth()
	/*if (m_Position.x  < 0)
	{
		m_bShow = false;
	}*/
	//��ʏ���E�ŏ���
	//if (m_Position.x  > g_pGraphics->GetTargetWidth())
	//{
		//m_bShow = false;
	//}
}

/**
 * �`��
 *
 */
void CPlayerShot::Render(float wx) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//��ʏ��荶�ŏ���
	if (m_Position.x < wx - m_pTexture->GetWidth() + 200)
	{
		m_bShow = false;
	}
	//��ʏ���E�ŏ���
	if (m_Position.x > g_pGraphics->GetTargetWidth() + wx + m_pTexture->GetWidth() - 790)
	{
		m_bShow = false;
	}

	CRectangle dr = m_SrcShotRect;
	//�e�N�X�`���̕`��
	//�X�N���[���l���l������Ă��Ȃ�player�N���X��render�Q��
	if (m_Reverse) {
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		m_pTexture->Render(m_Position.x + m_SrcShotRect.GetWidth() - wx, m_Position.y - (m_SrcShotRect.GetHeight() * 0.5f), dr);
	}
	else {
		m_pTexture->Render(m_Position.x + m_SrcShotRect.GetWidth() + 150 - wx, m_Position.y - (m_SrcShotRect.GetHeight() * 0.5f), dr);
	}
}

/**
 * �f�o�b�O�`��
 *
 */
void CPlayerShot::RenderDebug(float wx) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	if (m_Reverse) {
		CGraphicsUtilities::RenderRect(m_Position.x + m_SrcShotRect.GetWidth() + 30 - wx, m_Position.y - (m_pTexture->GetHeight() * 0.5f),
			m_Position.x + (m_SrcShotRect.GetWidth() * 2) - wx, m_Position.y + (m_pTexture->GetHeight() * 0.5f), MOF_XRGB(0, 255, 0));
	}
	else {
		CGraphicsUtilities::RenderRect(m_Position.x + m_SrcShotRect.GetWidth() + 150 - wx, m_Position.y - (m_pTexture->GetHeight() * 0.5f),
			m_Position.x + 360 - wx, m_Position.y + (m_pTexture->GetHeight() * 0.5f), MOF_XRGB(0, 255, 0));
	}
}
