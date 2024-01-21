#pragma once
#include "Mof.h"
#include "Audio.h"


class CTitle
{
private:	
	CTexture	m_Texture;		//タイトルの画像
	int         m_Alpha;		//フェード用
	bool        m_Cange;		//画面遷移フラグ
	CTexture    m_TextTexure;	//文字画像
	int         m_TextAlpha;	//文字画像のアルファ値
	float		m_Tw;			//画像の横の長さ
	float       m_Th;			//画像の縦の長さ
	int         m_PlusRGB;		//文字画像の色の変動値
	int			m_RGB;			//文字画像の色のRGB値
	CTexture    m_BackTexture;  //バックの画像
	spCAudio		m_Audio;
	int			m_Volume;
public:
	CTitle();
	~CTitle();
	void Load(void);
	void Initialize(void);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	void SetAudio(spCAudio audio) {m_Audio = audio; }
};

