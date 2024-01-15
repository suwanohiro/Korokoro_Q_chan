#include	"GameApp.h"

CGameApp::CGameApp()
	: _audioManager()
	, _effectManager()
{
	_scene = spScene_Base(new Scene_Game("mario"));
}

MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	_audioManager->Load();
	_effectManager->Load();

	_scene->Initialize();

	return TRUE;
}

MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	/////////////////////////////////////////////////////
	// 
	// FixedUpdate
	// 
	/////////////////////////////////////////////////////
	_effectManager->FixedUpdate();


	/////////////////////////////////////////////////////
	// 
	// Update
	// 
	/////////////////////////////////////////////////////
	_effectManager->Update();
	_scene->Update();


	/////////////////////////////////////////////////////
	// 
	// LateUpdate
	// 
	/////////////////////////////////////////////////////
	_effectManager->LateUpdate();
	
	return TRUE;
}

MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	_scene->Render();

	// TODO : _effectManager->Render(Vector2())�̈������ǂ��ɂ�����
	_effectManager->Render(Vector2());

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}

MofBool CGameApp::Release(void){
	_audioManager->Release();
	_effectManager->Release();
	_scene->Release();

	return TRUE;
}