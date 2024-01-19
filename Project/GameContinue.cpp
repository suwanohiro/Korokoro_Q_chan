#include "GameContinue.h"
#include "GameDefine.h"

CGameContinue::CGameContinue():
m_BackImage(),
m_SelectUI(),
m_Col(),
m_Select(SELECT_CONTINUE),
m_Pos(400,500),
m_Alpha(0),
m_Change(false),
m_Volume(50){
}

CGameContinue::~CGameContinue()
{
}

bool CGameContinue::Load(void)
{
	if (!m_BackImage.Load("GameOver02.png")) { return false; }
	if(!m_SelectUI.Load("sentaku.png")){ return false; }
	if (!m_BackImage02.Load("GameOver.png")) { return false; }
}

void CGameContinue::Initialize(void)
{
	m_Audio->Initialize();
	for (int i = 0; i < SceneCount; i++)
	{
		if (i == 0) {
			m_Col[i] = MOF_COLOR_RED;
		}
		else
		{
			m_Col[i] = MOF_COLOR_WHITE;
		}
		CGraphicsUtilities::CalculateStringRect(0, 0, m_String[i], m_StringRect[i]);
	}
	m_Select = SELECT_CONTINUE;
	m_Pos = Vector2(400, 500);
	m_Alpha = 0;
	m_Change = false;
	m_Volume = 50;
	m_Audio->SetVolume(m_Volume);
	m_Audio->Play(Audio_GameContinueBGM, false);
}

void CGameContinue::Update(int& ChangeScene)
{
	if (m_Change)
	{
		if (m_Alpha <= 0) {
			switch (m_Select)
			{
			case SELECT_CONTINUE:
				ChangeScene = SCENENO_GAME;
				break;
			default:
				ChangeScene = SCENENO_SELECT;
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
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		//ボタンSEを流す
		m_Audio->Play(Audio_Button, false);
		m_Change = true;
	}

	if (!m_Change) {
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			if (m_Select == SELECT_CONTINUE){
				//セレクトSEを流す
				m_Audio->Play(Audio_Select, false);
				m_Select = SELECT_END;
			}
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			if (m_Select == SELECT_END) {
				//セレクトSEを流す
				m_Audio->Play(Audio_Select, false);
				m_Select = SELECT_CONTINUE;
			}
		}
	}
	for (int i = 0; i < SceneCount; i++)
	{
		if (m_Select == i)
		{
			m_Pos.y = (i * 100) + 500;
			m_Col[i] = MOF_COLOR_RED;
		}
		else
		{
			m_Col[i] = MOF_COLOR_WHITE;
		}
	}
}

void CGameContinue::Render(void)
{
	m_BackImage.Render(0,0);
	if (m_Change && m_Select == SELECT_END) {
		m_BackImage02.Render(0, 0);
	}
	for (int i = 0; i < SceneCount; i++)
	{
		CGraphicsUtilities::RenderString(450, 500 + (i * 100), m_Col[i], m_String[i]);
	}
	m_SelectUI.Render(m_Pos.x, m_Pos.y);
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(255 - m_Alpha, 0, 0, 0));
	
}

void CGameContinue::RenderDebug(void)
{
}

void CGameContinue::Release(void)
{
	m_BackImage.Release();
	m_SelectUI.Release();
}
