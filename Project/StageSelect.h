#pragma once
#include "Mof.h"
#include "Audio.h"

//選べるシーン数
#define SceneCount 4
class CStageSelect
{
private:
	CAudio*	m_Audio;
	int		m_Volume;

	CTexture m_Texture[SceneCount];				//ステージ選択時画像
	CTexture m_NoSelectTexture;					//選択されていないときの画像
	int m_Select;								//シーン数
	bool m_Change;								//シーンが変わるか
	int m_Alpha;								//クローズアップ用

	CTexture   m_StageSelectText;				//StageSelect文字の画像
	CTexture   m_BackTexture;

public:
	CStageSelect();
	~CStageSelect();
	void Load();
	void Initialize();
	void Update(int& ChangeScene);
	void Render();
	void RenderDebug();
	void Release();
	void SetAudio(CAudio* audio) { m_Audio = audio; }
};

