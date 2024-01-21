#pragma once
#include "Mof.h"
#include "GameDefine.h"
#include "Audio.h"

class CMenu
{
private:
	
	bool         m_Menu;			//メニュー画面が開かれているかの判定

	//文字の位置調整のために使用する
	CRectangle  MenuStringRect;

	CTexture m_SelectTexture[3];

	int m_Select;					//何のシーンを選んでいるか

	spCAudio m_Audio;

public:
	CMenu();
	~CMenu();
	void Load();
	void Initialize();
	void Update(int& ChangeScene);
	void Render();
	void Release();

	void SetAudio(spCAudio audio) { m_Audio = audio; }

	//メニュー画面が開かれているか
	bool GetMenu() { return m_Menu; }
};

