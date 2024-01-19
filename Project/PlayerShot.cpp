#include	"PlayerShot.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayerShot::CPlayerShot() :
m_pTexture(NULL) ,
m_Position(0,0),
m_bShow(false),
m_Reverse(false){
}

/**
 * �f�X�g���N�^
 *
 */
CPlayerShot::~CPlayerShot(){
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 */
void CPlayerShot::Initialize(void){
	m_Position = Vector2(0, 0);
	m_bShow = false;
}
/**
 * ����
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 */
void CPlayerShot::Fire(float px,float py, bool r){
	m_Position.x = px - m_pTexture->GetWidth() * 0.5f;
	m_Position.y = py + m_pTexture->GetHeight() * 0.5f;
	m_bShow = true;
	m_Reverse = r;
}

/**
 * �X�V
 *
 */
void CPlayerShot::Update(void){
	//��\��
	if(!m_bShow)
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
void CPlayerShot::Render(float wx){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//��ʏ��荶�ŏ���
	if (m_Position.x  < wx - m_pTexture->GetWidth())
	{
		m_bShow = false;
	}
	//��ʏ���E�ŏ���
	if (m_Position.x  > g_pGraphics->GetTargetWidth() + wx + m_pTexture->GetWidth())
	{
		m_bShow = false;
	}

	//
	//1024���߂�����̕`��ʒu����������*****************************************************************************************************//
	//�e�N�X�`���̕`��
	//�X�N���[���l���l������Ă��Ȃ�player�N���X��render�Q��
	m_pTexture->Render(m_Position.x - wx,m_Position.y);
}

/**
 * �f�o�b�O�`��
 *
 */
void CPlayerShot::RenderDebug(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CGraphicsUtilities::RenderRect(m_Position.x,m_Position.y,m_Position.x + m_pTexture->GetWidth(),m_Position.y + m_pTexture->GetHeight(),MOF_XRGB(0,255,0));
}
