#include "GameDefine.h"
#include "Title.h"


CTitle::CTitle():
	m_Texture(),
	m_Alpha(0),
	m_Cange(false),
	m_TextAlpha(0),
	m_Tw(0),
	m_Th(0),
	m_PlusRGB(),
	m_RGB(0),
	m_BackTexture(),
	m_Volume(50)
{
}

CTitle::~CTitle()
{
}

void CTitle::Load()
{
	if (!m_Texture.Load("Title&Select/ƒ^ƒCƒgƒ‹_”wŒi‚È‚µ.png"))
	{
		return;
	}
	if (!m_TextTexure.Load("Title&Select/PUSH_START.png"))
	{
		return;
	}
	if (!m_BackTexture.Load("Title&Select/”wŒi.png"))
	{
		return;
	}
}

void CTitle::Initialize()
{
	m_Audio->Initialize();
	m_Alpha = 0;
	m_TextAlpha = 0;
	m_Tw = m_TextTexure.GetWidth() * 0.5;
	m_Th = m_TextTexure.GetHeight() * 0.5;
	m_Cange = false;
	m_PlusRGB = -1;
	m_RGB = 255;
	m_Volume = 50;
	m_Audio->SetVolume(m_Volume);
	m_Audio->Play(Audio_TitleBGM, true);
}

void CTitle::Update(int& ChangeScene)
{
	if (m_Cange)
	{
		if (m_Alpha <= 0)
		{
			ChangeScene = SCENENO_SELECT;
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
		if (m_Alpha >= 255 && m_TextAlpha < 255)
		{
			m_TextAlpha += 5;
		}
		else if (m_TextAlpha >= 255)
		{
			m_RGB += m_PlusRGB;

			if (m_RGB >= 254)
			{
				m_PlusRGB = -1;
			}
			else if (m_RGB <= 203)
			{
				m_PlusRGB = 1;
			}
			if (g_pInput->IsKeyPush(MOFKEY_RETURN))
			{
				//ƒ{ƒ^ƒ“SE‚ð—¬‚·
				m_Audio->Play(Audio_Button, false);
				m_Cange = true;
			}
		}
	}

}

void CTitle::Render()
{
	m_BackTexture.Render(0, 0);
	m_Texture.Render(g_pGraphics->GetTargetWidth() * 0.5 - m_Texture.GetWidth() * 0.5,
		g_pGraphics->GetTargetHeight() * 0.15);
	m_TextTexure.Render(g_pGraphics->GetTargetWidth() * 0.5 - m_Tw,
		g_pGraphics->GetTargetHeight() * 0.75 - m_Th, MOF_ARGB(m_TextAlpha, m_RGB, m_RGB, m_RGB));
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_ARGB(255 - m_Alpha, 0, 0, 0));
}

void CTitle::RenderDebug(void)
{
}

void CTitle::Release()
{
	m_Texture.Release();
	m_TextTexure.Release();
	m_BackTexture.Release();
}
