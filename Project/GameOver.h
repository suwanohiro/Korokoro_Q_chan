#pragma once

#include	"Audio.h"

class CGameOver {
private:
	CTexture				m_BackImage;
	int						m_Alpha;
	bool					m_Change;
	CAudio*					m_Audio;
	int						m_Volume;

public:
	CGameOver();
	~CGameOver();
	bool Load(void);
	void Initialize(void);
	void Update(int& ChangeScene);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
	void SetAudio(CAudio* audio) { m_Audio = audio; }
};