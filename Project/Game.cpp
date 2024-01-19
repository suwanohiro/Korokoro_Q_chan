#include	"GameDefine.h"
#include	"Game.h"


/**
 * �R���X�g���N�^
 *
 */
CGame::CGame():
m_EnemyArray(),
m_ItemArray()
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
	//�v���C���[�̑f�ޓǂݍ���
	m_Player.Load();
	//�X�e�[�W�̑f�ޓǂݍ���
	m_Stage.Load("Stage1.txt");
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
	
	//�ύX����
	//�G�̑f�ޓǂݍ���
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].Load();
	}

	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
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
void CGame::Initialize(){

	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�������ύX�_
	//���j���[�̏�ԏ�����
	m_Menu.Initialize();
	//�I�[�f�B�I�̏�ԏ�����
	m_Audio->Initialize();
	//�J�E���g�_�E���̏�����
	m_Countdown.Initialize();

	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	//�v���C���[�ƓG�ɃI�[�f�B�I�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	m_Player.SetAudio(&*m_Audio);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
		m_EnemyArray[i].SetAudio(&*m_Audio);
	}
	
	m_Menu.SetAudio(&*m_Audio);

	//�J�E���g�_�E�����Ԃ̐ݒ�
	m_Countdown.SetCountdown(20);
	m_Countdown.Start();
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

	//�v���C���[�̍X�V
	m_Player.Update();
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.getHitBox(), ox, oy)) {
		m_Player.CollisionStage(ox, oy);
		m_Player.SetStCollision(m_Stage.GetStageCollision());
	}
	else {
		//�ύX�_����������������������������������������������������������������������������������������
		m_Player.NotCollisionStage();
	}
	//�ύX�_����������������������������������������������������������������������������������������������������
	if (m_Stage.CollisionAttack(m_Player.getAttackBox(), ox, 1)) {
		m_Player.CollisionStageAttackLeft();
	}
	else if (m_Stage.CollisionAttack(m_Player.getAttackBox(), ox, 0)) {
		m_Player.CollisionStageAttackRight();
	}
	//�G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].TypeCheck(m_Player.getPosition(), m_Stage.GetScrollX(), m_Stage.GetScrollY());
		if (!m_EnemyArray[i].GetShow()) {
			continue;
		}

		//�ύX����
		m_EnemyArray[i].Update();
		
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy)) {
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
		
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		if (!m_ItemArray[i].GetShow()) {
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy)) {
			m_ItemArray[i].CollisionStage(oy);
		}
	}
	//�����蔻��̎��s
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		//�������ύX�_
		
		//�G�Ɠ�����΃T�E���h��炷
		(m_Player.CollisionEnemy(m_EnemyArray[i]));

	}
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		m_Player.CollisionItem(m_ItemArray[i]);
	}
	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);
	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

	m_Player.UpdateUI();

	if (m_Player.IsGoal()) {
		ChangeScene = SCENENO_GAMECLEAR;
	}
	//F2�L�[�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2)) {
		ChangeScene = SCENENO_GAMECLEAR;
	}

	if (m_Player.IsDead()) {
		ChangeScene = SCENENO_CONTINUE;
	}
	if (g_pInput->IsKeyPush(MOFKEY_F4)) {
		ChangeScene = SCENENO_CONTINUE;
	}
	//�v���C���[�̏I���t���O�ŃQ�[���I�[�o�[��ʂ�
	if (m_Player.IsEnd()) {
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
	//�v���C���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	m_Player.RenderShot(m_Stage.GetScrollX());
	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//UI�̕`��
	m_Player.RenderUI();
	//�J�E���g�_�E���̕`��
	m_Countdown.Render();
	//�������ύX�_
	//���j���[�̕`��
	m_Menu.Render();

	//CGraphicsUtilities::RenderString(10,10,"�Q�[�����");
	//CGraphicsUtilities::RenderString(10,40,"F2�L�[�ŃQ�[���N���A�AF3�L�[�ŃQ�[���I�[�o�[");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGame::RenderDebug(void){
	//�X�e�[�W�̃f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�̃f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̃f�o�b�N�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++) {
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�N�`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++) {
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
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
	//�v���C���[�̉��
	m_Player.Release();
	//�G�̉��
	if (m_EnemyArray) {
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray) {
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//�G�t�F�N�g�̉��
	m_EffectManager.Release();

	//�������ύX�_
	//���j���[�̕`��
	m_Menu.Release();
}