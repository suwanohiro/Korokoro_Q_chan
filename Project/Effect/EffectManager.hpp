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
