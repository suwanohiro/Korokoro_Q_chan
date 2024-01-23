/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"





void CGameApp::__renderLoading()
{
	Vector2 screenSize = {
			(float)g_pGraphics->GetTargetWidth(),
			(float)g_pGraphics->GetTargetHeight()
	};

	CRectangle bk(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	CGraphicsUtilities::RenderFillRect(bk, getRGB(WebColor::white));

	std::string nowloading = "Now Loading";
	Vector2 size = StringAction::GetStringSize(nowloading.c_str());
	Vector2 padding(30, 30);
	size += padding;

	Vector2 pos = screenSize * 0.5 - size * 0.5;

	CGraphicsUtilities::RenderString(pos.x, pos.y, getRGB(WebColor::black), "Now Loading");
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	m_Audio = spCAudio(new CAudio);

	_isLoaded = false;

	_loadThread = std::thread([=]() {
		//�V�[���̕K�v���\�[�X��S�ēǂݍ���
		m_TitleScene.Load();
		//�������ύX�_
		m_StageSelect.Load();
		m_GameScene.Load();
		m_GameClearScene.Load();
		m_GameOverScene.Load();
		m_GameContinue.Load();
		m_Audio->Load();

		m_Scene = SCENENO_TITLE;
		m_ChangeScene = SCENENO_TITLE;
		m_bDebug = false;

		m_TitleScene.SetAudio(m_Audio);
		m_StageSelect.SetAudio(m_Audio);
		m_GameScene.SetAudio(m_Audio);
		m_GameClearScene.SetAudio(m_Audio);
		m_GameOverScene.SetAudio(m_Audio);
		m_GameContinue.SetAudio(m_Audio);

		//�ŏ��Ɏ��s�����V�[���̏�����
		m_TitleScene.Initialize();

		_isLoaded = true;
	});
	_loadThread.detach();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	if (!_isLoaded) return TRUE;
	
	//�V�[���ԍ��ɂ���čX�V
	switch(m_Scene)
	{
		case SCENENO_TITLE:
			m_TitleScene.Update(m_ChangeScene);
			break;
		//�������ύX�_
		case SCENENO_SELECT:
			m_StageSelect.Update(m_ChangeScene);
			break;
		case SCENENO_GAME:
			m_GameScene.Update(m_ChangeScene);
			break;
		case SCENENO_GAMECLEAR:
			m_GameClearScene.Update(m_ChangeScene);
			break;
		case SCENENO_GAMEOVER:
			m_GameOverScene.Update(m_ChangeScene);
			break;
		case SCENENO_CONTINUE:
			m_GameContinue.Update(m_ChangeScene);
			break;
	}
	
	//�V�[���ύX���������ꍇ�ύX��V�[���̏�����
	if(m_ChangeScene != m_Scene)
	{
		switch(m_ChangeScene)
		{
			case SCENENO_TITLE:
				m_TitleScene.Initialize();
				break;
			//�������ύX�_
			case SCENENO_SELECT:
				m_StageSelect.Initialize();
				break;
			case SCENENO_GAME:
				m_GameScene.Initialize(m_StageSelect.getStageNumber());
				break;
			case SCENENO_GAMECLEAR:
				m_GameClearScene.Initialize();
				break;
			case SCENENO_GAMEOVER:
				m_GameOverScene.Initialize();
				break;
			case SCENENO_CONTINUE:
				m_GameContinue.Initialize();
				break;
		}
		m_Scene = m_ChangeScene;
	}

	//�f�o�b�O�\���̐؂�ւ�
	if(g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_bDebug = ((m_bDebug) ? false : true);
	}
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	if (!_isLoaded) {
		__renderLoading();

		//�`��̏I��
		g_pGraphics->RenderEnd();
		return TRUE;
	}

	
	//�V�[���ԍ��ɂ���ĕ`��
	switch(m_Scene)
	{
		case SCENENO_TITLE:
			m_TitleScene.Render();
			break;
		//�������ύX�_
		case SCENENO_SELECT:
			m_StageSelect.Render();
			break;
		case SCENENO_GAME:
			m_GameScene.Render();
			break;
		case SCENENO_GAMECLEAR:
			m_GameClearScene.Render();
			break;
		case SCENENO_GAMEOVER:
			m_GameOverScene.Render();
			break;
		case SCENENO_CONTINUE:
			m_GameContinue.Render();
			break;
	}
	
	//�f�o�b�O�\��������ꍇ
	if(m_bDebug)
	{
		//�V�[���ԍ��ɂ���ĕ`��
		switch(m_Scene)
		{
			case SCENENO_TITLE:
				m_TitleScene.RenderDebug();
				break;
			//�������ύX�_
			case SCENENO_SELECT:
				m_StageSelect.RenderDebug();
				break;
			case SCENENO_GAME:
				m_GameScene.RenderDebug();
				break;
			case SCENENO_GAMECLEAR:
				m_GameClearScene.RenderDebug();
				break;
			case SCENENO_GAMEOVER:
				m_GameOverScene.RenderDebug();
				break;
			case SCENENO_CONTINUE:
				m_GameContinue.RenderDebug();
				break;
		}
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	if (!_isLoaded) _loadThread.join();

	m_TitleScene.Release();
	//�������ύX�_
	m_StageSelect.Release();
	m_GameScene.Release();
	m_GameClearScene.Release();
	m_GameOverScene.Release();
	m_GameContinue.Release();
	m_Audio->Release();

	return TRUE;
}