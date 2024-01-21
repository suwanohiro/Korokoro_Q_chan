/*************************************************************************//*!
					
					@file	GameApp.h
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

#pragma once

//INCLUDE
#include	"Mof.h"
#include	"GameDefine.h"
#include	"Title.h"

#include "./swnLibrary/swnLibrary.h"
//�������ύX�_
#include	"StageSelect.h"
#include	"Game.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"GameContinue.h"
#include	"Audio.h"
#include <thread>
/*******************************//*!
@brief	��{�Q�[���A�v���B

@author	�_�c�@��
*//********************************/
class CGameApp : public CSingleGameApplication {
private:
	//���݂̃V�[��
	int						m_Scene;
	//�ύX����V�[��
	int						m_ChangeScene;

	//�e�V�[���N���X
	CTitle					m_TitleScene;
	CGame					m_GameScene;
	CGameClear				m_GameClearScene;
	CGameOver				m_GameOverScene;
	//�������ύX�_
	CStageSelect			m_StageSelect;
	CGameContinue			m_GameContinue;
	spCAudio				m_Audio;

	//�f�o�b�O�\���t���O
	bool					m_bDebug;

	std::thread				_loadThread;
	bool					_isLoaded;

	void __renderLoading();

public:
	/*************************************************************************//*!
			@brief			�R���X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	CGameApp() {}
	/*************************************************************************//*!
			@brief			�f�X�g���N�^
			@param			None

			@return			None
	*//**************************************************************************/
	virtual ~CGameApp(){	Release();	}
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̏�����
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Initialize(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̍X�V
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Update(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̕`��
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Render(void);
	/*************************************************************************//*!
			@brief			�A�v���P�[�V�����̉��
			@param			None
				
			@return			TRUE		����<br>
							����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
	*//**************************************************************************/
	virtual MofBool Release(void);
};
