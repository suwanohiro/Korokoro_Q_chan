#include	"GameApp.h"

CGameApp::CGameApp()
	: _audioManager(new AudioManager)
	, _effectManager(new EffectManager)
{
	_characterManager = spCharacterManager(new CharacterManager(_audioManager, _effectManager));

	_blockManager = spBlockManager(new BlockManager(_characterManager, "BlockDatas"));

	_scene = spScene_Base(new Scene_Game("test_stage_2024-01-12_1", _blockManager, _characterManager));
}

MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	_audioManager->Load();
	_effectManager->Load();
	_characterManager->Load();
	_blockManager->Load();

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
	// TODO : FixedUpdate�̈����𐳏�Ȃ��̂ɏC������
	_effectManager->FixedUpdate(Vector2(0, 0));
	_scene->FixedUpdate();


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
	_scene->LateUpdate();
	
	return TRUE;
}

MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	_scene->Render();

	_effectManager->Render();

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