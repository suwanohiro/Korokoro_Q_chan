#include "StageSelect.h"
#include "GameDefine.h"



CStageSelect::CStageSelect():
	m_Volume(100),
	m_Alpha(0),
	m_Select(0),
	m_Change(false),
	m_BackTexture(),
	m_NoSelectTexture()
{
}

CStageSelect::~CStageSelect()
{
}

void CStageSelect::Load()
{
	m_BackTexture.Load("Title&Select/”wŒi.png");

	m_StageSelectText.Load("Title&Select/StageSelect.png");

	m_Texture[0].Load("Title&Select/ƒXƒe[ƒW‘I‘ð_”wŒi‚È‚µ0.png");
	m_Texture[1].Load("Title&Select/ƒXƒe[ƒW‘I‘ð_”wŒi‚È‚µ1.png");
	m_Texture[2].Load("Title&Select/ƒXƒe[ƒW‘I‘ð_”wŒi‚È‚µ2.png");
	m_Texture[3].Load("Title&Select/ƒXƒe[ƒW‘I‘ð_”wŒi‚È‚µ3.png");

	m_NoSelectTexture.Load("Title&Select/ƒXƒe[ƒW‘I‘ð_”wŒi‚È‚µa.png");

}

void CStageSelect::Initialize()
{
	m_Audio->Initialize();
	m_Alpha = 0;
	m_Select = -1;
	m_Change = false;
	m_Volume = 50;
	m_Audio->SetVolume(m_Volume);
}

void CStageSelect::Update(int& ChangeScene)
{
	if (m_Change)
	{
		if (m_Alpha <= 0)
		{
			switch (m_Select)
			{
			case 0:
				ChangeScene = SCENENO_TITLE;
				break;
			default:
				ChangeScene = SCENENO_GAME;
				break;
			}
		}
		else
		{
			m_Alpha -= 5;
		}
	}
	else
	{
		if (m_Alpha < 255)
		{
			m_Alpha += 5;
			return;
		}
		if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) { m_Select = 0; m_Change = true; m_Audio->Play(Audio_Button, false); }
		else if (g_pInput->IsKeyPush(MOFKEY_Z)) { m_Select = 1; m_Change = true; m_Audio->Play(Audio_Button, false); }
		else if (g_pInput->IsKeyPush(MOFKEY_X)) { m_Select = 2; m_Change = true; m_Audio->Play(Audio_Button, false); }
		else if (g_pInput->IsKeyPush(MOFKEY_C)) { m_Select = 3; m_Change = true; m_Audio->Play(Audio_Button, false); }
	}
}

void CStageSelect::Render()
{
	m_BackTexture.Render(0, 0);
	for (int i = 0; i < SceneCount; i++)
	{
		if (i == m_Select) {
			m_Texture[i].Render(0, 240);
		}
		else if (m_Select == -1)
		{
			m_NoSelectTexture.Render(0, 240);
		}
	}
	m_StageSelectText.Render(0, 0);
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(255 - m_Alpha, 0, 0, 0));
}

void CStageSelect::RenderDebug()
{
}

void CStageSelect::Release()
{
	m_BackTexture.Release();
	m_StageSelectText.Release();
	m_NoSelectTexture.Release();
	for (int i = 0; i < SceneCount; i++) {
		m_Texture[i].Release();
	}
}
