#pragma once
#include	"Mof.h"
#include "Audio.h"

//選べるシーン数
#define SceneCount 2

enum tag_Select
{
	SELECT_CONTINUE,
	SELECT_END,
};

class CGameContinue{
private:
	CTexture	m_BackImage;
	CTexture	m_BackImage02;
	CTexture	m_SelectUI;

	//文字の色
	MofU32  m_Col[SceneCount];

	//選んでいるシーン名
	char* m_String[SceneCount] = { "CONTINUE","END"};

	CRectangle m_StringRect[SceneCount];

	//シーン数
	int m_Select;

	int m_Alpha;

	bool m_Change;

	Vector2		m_Pos;

	spCAudio		m_Audio;
	int 		m_Volume;

public:
	CGameContinue();
	~CGameContinue();
	bool Load(void);
	void Initialize(void);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	void SetAudio(spCAudio audio) { m_Audio = audio; }
};

