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
	virtual void Render() override;

	virtual void Start(Vector2 startPos);
};

using spEffect = std::shared_ptr<Effect>;
