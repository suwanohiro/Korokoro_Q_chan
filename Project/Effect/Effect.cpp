#include "Effect.hpp"

Effect::Effect()
	: GameObject()
{
}

void Effect::Initialize(Vector2 initPos)
{
	GameObject::Initialize(initPos);

	isActive(false);
}

void Effect::Update()
{
	if (!isActive()) return;

	// アニメーションの終了で非表示にする
	if (__isEndMotion()) isActive(false);
}

void Effect::LateUpdate()
{
	GameObjectMotion::Update();
}

void Effect::Render()
{
	if (!isActive()) return;

	const Vector2 scroll = __getScroll();
	const Vector2 pos = getPosition() + scroll;
	if(getTexture() != nullptr) getTexture()->Render(pos.x, pos.y);
}

void Effect::Start(Vector2 startPos)
{
	__setMotionRect();
	setPosition(startPos - __getMotionRectSize() * 0.5f);
	isActive(true);
	__getMotion()->ChangeMotion(0);
}
