#pragma once

#include "../../Shot/Shot.hpp"

constexpr int PlayerShot_Speed = 6;

class PlayerShot : public Shot
{
public:
	PlayerShot();

	void Update() override;
	void Render() override;

	void Fire(Vector2 playerPos) override { Fire(playerPos, false); };
	void Fire(Vector2 playerPos, bool IsReverse);
};

using spPlayerShot = std::shared_ptr<PlayerShot>;
