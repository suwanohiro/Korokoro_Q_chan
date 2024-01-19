#pragma once

#include "./Effect.hpp"

enum class EffectType {
	Damage,					// ダメージ
	DownEnemy,				// やられエネミー
	DownPlayer,				// やられプレイヤー
	Length					// 総数
};

class EffectManager
{
private:
	std::vector<spCTexture> _effectTexture;
	std::vector<spEffect> _effectArray;

	spCTexture __getTexture(EffectType type);

public:
	EffectManager();
	~EffectManager() { Release(); }

	bool Load();
	void FixedUpdate(Vector2 scroll);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

	void startEffect(EffectType type, Vector2 pos);
};

using spEffectManager = std::shared_ptr<EffectManager>;
