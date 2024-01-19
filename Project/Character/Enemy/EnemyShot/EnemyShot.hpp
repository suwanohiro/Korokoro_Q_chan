#pragma once

#include "../../Shot/Shot.hpp"

class EnemyShot : public Shot
{
private:
	Vector2 _vector;

	void __setVector(Vector2 value) { _vector = value; }
	void __setVector(float x, float y) { _vector = Vector2(x, y); }
	Vector2 __getVector() { return _vector; }

public:
	EnemyShot();

	void Initialize(Vector2 initPos) override;
	void Update() override;

	void Fire(Vector2 playerPos) override { Fire(playerPos, Vector2(0, 0)); };
	void Fire(Vector2 playerPos, Vector2 vector);
};

using spEnemyShot = std::shared_ptr<EnemyShot>;
