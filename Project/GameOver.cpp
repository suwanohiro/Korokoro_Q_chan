#include	"GameDefine.h"
#include	"GameOver.h"



/**
 * �R���X�g���N�^
 *
 */
CGameOver::CGameOver() :
m_BackImage(),
m_Alpha(0),
m_Change(false) {
}

/**
 * �f�X�g���N�^
 *
 */
CGameOver::~CGameOver(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameOver::Load(void){
	if (!m_BackImage.Load("GameOver.png")) {
		return false;
	}
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGameOver::Initialize(void){
	m_Audio->Initialize();
	m_Alpha = 0;
	m_Change = false;
	m_Volume = 50;
	m_Audio->SetVolume(m_Volume);
	m_Audio->Play(Audio_GameOverBGM, false);
}

/**
 * �X�V
 *
 */
void CGameOver::Update(int& ChangeScene){
	if (m_Change)
	{
		if (m_Alpha <= 0) {
			ChangeScene = SCENENO_SELECT;
		}
		else {
			m_Alpha -= 5;
		}
	}
	else
	{
		if (m_Alpha < 255)
		{
			m_Alpha += 5;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		//�{�^��SE�𗬂�
		m_Audio->Play(Audio_Button, false);
		m_Change = true;
	}
}

/**
 * �`��
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Pree Enter Key");
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(255 - m_Alpha, 0, 0, 0));
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameOver::RenderDebug(void){
}

/**
 * ���
 *
 */
void CGameOver::Release(void){
	m_BackImage.Release();
}