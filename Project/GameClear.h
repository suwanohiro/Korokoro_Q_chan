#pragma once

#include	"Audio.h"

class CGameClear {
private:
	CTexture				m_BackImage;
	int						m_Alpha;
	bool					m_Change;
	spCAudio					m_Audio;
	int 					m_Volume;

public:
	CGameClear();
	~CGameClear();
	bool Load(void);
	void Initialize(void);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	void SetAudio(spCAudio audio) { m_Audio = audio; }
};