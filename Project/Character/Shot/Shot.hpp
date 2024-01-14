#pragma once

#include "../../GameObject/GameObject.hpp"

class Shot : public GameObject
{
private:
	float _speed;

protected:
	void __setSpeed(float value) { _speed = value; }
	float __getSpeed() { return _speed; }

public:
	Shot();

	virtual void Initialize(Vector2 initPos) override;
	virtual void Render() override { Render(Vector2(0, 0)); };
	virtual void Render(Vector2 w);

	virtual void Fire(Vector2 playerPos);

};

using spShot = std::shared_ptr<Shot>;
