#pragma once

#include "../GameObject/GameObject.hpp"
#include "../GameObject/GameObjectMotion.hpp"

class Effect : public GameObject, public GameObjectMotion
{
public:
	Effect();

	virtual void Initialize(Vector2 initPos) override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override { Render(Vector2(0, 0)); };
	virtual void Render(Vector2 value);

	virtual void Start(Vector2 startPos);
};

using spEffect = std::shared_ptr<Effect>;
