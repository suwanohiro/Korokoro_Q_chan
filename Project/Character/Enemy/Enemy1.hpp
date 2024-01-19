#pragma once

#include "./Enemy.hpp"

class Enemy1 : public Enemy
{
private:
	void __fire(Vector2 playerPos);

public:
	Enemy1(spAudioManager audioManager, spEffectManager effectManager);

	void Attack() override { Attack(Vector2(0, 0), Vector2(0, 0)); };
	void Attack(Vector2 playerPos, Vector2 w);
};

using spEnemy1 = std::shared_ptr<Enemy1>;
