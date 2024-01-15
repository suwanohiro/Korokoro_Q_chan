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

	spCTexture __getTexture(EffectType type) { return _effectTexture[(int)type]; }

public:
	EffectManager();
	~EffectManager() { Release(); }

	bool Load();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render(Vector2 value);
	void Release();

	void startEffect(EffectType type, Vector2 pos);
};

using spEffectManager = std::shared_ptr<EffectManager>;
