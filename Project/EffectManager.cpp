#include "EffectManager.h"

/* コンストラクタ*/
CEffectManager::CEffectManager()
{
}

/* デストラクタ*/
CEffectManager::~CEffectManager()
{
}

/* テクスチャの読み込み*/
bool CEffectManager::Load(void)
{
	//テクスチャの読み込み
	char* name[] = {
		"effect01.png",
		"effect02.png",
		"effect03.png",
	};
	for (int i = 0; i < EFC_COUNT; i++)
	{
		if (!m_Texture[i].Load(name[i]))
		{
			return false;
		}
	}

    return false;
}

/* 初期化*/
void CEffectManager::Initialize(void)
{
	//エフェクトの基礎設定
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize({0, 0},j);
		}
	}

}

/* 開始
座標を指定してモーションを開始する
引数
[in]        pos         x,y座標
[in]        type        エフェクトタイプ
*/
CEffect* CEffectManager::Start(Vector2 pos, int type)
{
	for (int i = 0; i < EFFECTCOUNT; i++)
	{
		if (m_Effect[i][type].GetShow())
		{
			continue;
		}
		m_Effect[i][type].Start(pos);
		return &m_Effect[i][type];
	}

    return nullptr;
}

/* 更新*/
void CEffectManager::Update(void)
{
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}

}

/* 描画*/
void CEffectManager::Render(float wx, float wy)
{
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(wx,wy);
		}
	}

}

/* 解放*/
void CEffectManager::Release(void)
{
	for (int j = 0; j < EFC_COUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}

}
