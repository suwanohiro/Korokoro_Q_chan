#pragma once

#include "./Effect.hpp"

enum class EffectType {
	Damage,					// �_���[�W
	DownEnemy,				// ����G�l�~�[
	DownPlayer,				// ����v���C���[
	Length					// ����
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
