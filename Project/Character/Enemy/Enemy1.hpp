#pragma once

#include "./Enemy.hpp"

class Enemy1 : public Enemy
{
private:
	int _shotWait;

	void __fire(Vector2 playerPos, Vector2 w);

	int __getShotWait() { return _shotWait; }
	void __setShotWait(int value) { _shotWait = value; }
	void __updateShotWait(int value) { _shotWait += value; }

public:
	Enemy1(spAudioManager audioManager, spEffectManager effectManager);

	void Attack() override { Attack(Vector2(0, 0), Vector2(0, 0)); };
	void Attack(Vector2 playerPos, Vector2 w);
};

using spEnemy1 = std::shared_ptr<Enemy1>;
