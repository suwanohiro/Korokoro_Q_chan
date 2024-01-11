#include	"GameApp.h"

void outputString(std::string msg) {
	OutputDebugString((msg + "\n").c_str());
}

CGameApp::CGameApp()
{
	_scene = new Scene_Game("debug");
}

MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	_scene->Initialize();

	return TRUE;
}

MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	_scene->Update();
	
	return TRUE;
}

MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	_scene->Render();

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}

MofBool CGameApp::Release(void){
	_scene->Release();

	return TRUE;
}