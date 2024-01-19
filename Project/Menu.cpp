#include "Menu.h"
#include "stdlib.h"



CMenu::CMenu():
	m_Menu(false),
	m_Select(0),
	m_SelectTexture()
{
}

CMenu::~CMenu()
{
}

void CMenu::Load()
{
	m_SelectTexture[0].Load("Menu/ポーズ1.png");
	m_SelectTexture[1].Load("Menu/ポーズ2.png");
	m_SelectTexture[2].Load("Menu/ポーズ3.png");
}

void CMenu::Initialize()
{
	m_Menu = false;
	m_Select = 0;
	CGraphicsUtilities::CalculateStringRect(0, 0, "メニュー", MenuStringRect);
}

void CMenu::Update(int& ChangeScene)
{
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		m_Menu = !m_Menu;
		m_Select = 0;
	}
	if (m_Menu)
	{
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			if (m_Select < 2)
			{
				m_Audio->Play(Audio_Select, false);
				m_Select = m_Select + 1;
			}
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			if (m_Select > 0)
			{
				m_Audio->Play(Audio_Select, false);
				m_Select = m_Select - 1;
			}
		}
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
			m_Audio->Play(Audio_Button, false);
			if (m_Select == 0) {
				m_Menu = false;
			}
			else if (m_Select == 1)
			{
				ChangeScene = SCENENO_SELECT;
			}
			else
			{
				ChangeScene = SCENENO_TITLE;
			}
		}
		return;
	}
}

void CMenu::Render()
{
	if (m_Menu)
	{
		float Posx, Posy;
		Posx = g_pGraphics->GetTargetWidth() * 0.5 - m_SelectTexture->GetWidth() * 0.5;
		Posy = 300;

		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(),
			MOF_ARGB(128, 0, 0, 0));
		CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5 - MenuStringRect.GetWidth() * 0.5, 10,
			MOF_COLOR_WHITE, "メニュー");
		for (int i = 0; i < 3; i++) {
			if (m_Select == i)
				m_SelectTexture[i].Render(Posx, Posy);
		}
	}
}

void CMenu::Release()
{
	for (int i = 0; i < 3; i++) {
		m_SelectTexture[i].Release();
	}
}
