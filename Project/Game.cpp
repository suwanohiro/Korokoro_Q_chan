#include	"GameDefine.h"
#include	"Game.h"


/**
 * �R���X�g���N�^
 *
 */
CGame::CGame()
{
}

/**
 * �f�X�g���N�^
 *
 */
CGame::~CGame(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGame::Load(void){
	//�X�e�[�W�̑f�ޓǂݍ���
	// TODO : �X�e�[�W�̓ǂݍ��݂�1�X�e�[�W�������ł��Ă��Ȃ����
	// m_Stage.LoadMapData("test_stage_2024-01-12_1");
	m_Stage.LoadBKTexture();

	//�G�t�F�N�g�̑f�ޓǂݍ���
	m_EffectManager.Load();
	//���j���[�̑f�ޓǂݍ���
	m_Menu.Load();
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGame::Initialize(int stage){
	// �X�e�[�W�ԍ���1�ȏ�ɂȂ��Ă���̂Ŕz��Y���ɍ��킹�邽��1����
	stage--;

	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(&m_EffectManager, m_Audio);

	CSVData mapList = FileAction::ReadCSV("Resource/MapData/MapList.swn");

	const bool isFoundStage = stage < mapList.size();
	if (isFoundStage) {
		m_Stage.LoadMapData(mapList[stage][0]);
	}

	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�������ύX�_
	//���j���[�̏�ԏ�����
	m_Menu.Initialize();
	//�I�[�f�B�I�̏�ԏ�����
	m_Audio->Initialize();
	//�J�E���g�_�E���̏�����
	m_Countdown.Initialize();
	
	m_Menu.SetAudio(m_Audio);

	//�J�E���g�_�E�����Ԃ̐ݒ�
	m_Countdown.SetCountdown(300);
	m_Countdown.Start();

	m_Audio->Play(Audio_StageBGM, true);
}

/**
 * �X�V
 *
 */
void CGame::Update(int& ChangeScene){
	//�������ύX�_
	//���j���[
	m_Menu.Update(ChangeScene);
	if (m_Menu.GetMenu())
	{
		return;
	}

	//�J�E���g�_�E���̍X�V
	m_Countdown.Update();
	if (!m_Countdown.GetRemaining()) {
		ChangeScene = SCENENO_GAMEOVER;
		return;
	}

	m_Stage.Update();
	
	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

	if (m_Stage.IsGoal()) {
		ChangeScene = SCENENO_GAMECLEAR;
	}
	//F2�L�[�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2)) {
		ChangeScene = SCENENO_GAMECLEAR;
	}

	if (m_Stage.IsPlayerDead()) {
		ChangeScene = SCENENO_CONTINUE;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F4)) {
		ChangeScene = SCENENO_CONTINUE;
	}
	//�v���C���[�̏I���t���O�ŃQ�[���I�[�o�[��ʂ�
	if (m_Stage.IsEnd()) {
		ChangeScene = SCENENO_GAMEOVER;
	}
	//F3�L�[�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F3)) {
		ChangeScene = SCENENO_GAMEOVER;
	}
	//�f�o�b�O�p

}

/**
 * �`��
 *
 */
void CGame::Render(void){
	//�X�e�[�W�̕`��
	m_Stage.Render();

	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�J�E���g�_�E���̕`��
	m_Countdown.Render();
	//�������ύX�_
	//���j���[�̕`��
	m_Menu.Render();
}

/**
 * �f�o�b�O�`��
 *
 */
void CGame::RenderDebug(void){
	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();

	//�G�t�F�N�g�̃f�o�b�N�`��
	//m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * ���
 *
 */
void CGame::Release(void){
	//�X�e�[�W�̉��
	m_Stage.Release();

	//�G�t�F�N�g�̉��
	m_EffectManager.Release();

	//�������ύX�_
	//���j���[�̕`��
	m_Menu.Release();
}