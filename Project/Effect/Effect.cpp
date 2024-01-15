#include "Effect.hpp"

Effect::Effect()
	: GameObject()
{
}

void Effect::Initialize(Vector2 initPos)
{
	GameObject::Initialize(initPos);

	setActive(false);
}

void Effect::Update()
{
	if (!isActive()) return;

	// �A�j���[�V�����̏I���Ŕ�\���ɂ���
	if (__isEndMotion()) setActive(false);
}

void Effect::LateUpdate()
{
	GameObjectMotion::Update();
}

void Effect::Render(Vector2 value)
{
	if (!isActive()) return;

	const Vector2 pos = getPosition() + value;
	getTexture()->Render(pos.x, pos.y);
}

void Effect::Start(Vector2 startPos)
{
	__setMotionRect();
	setPosition(startPos - __getMotionRectSize() * 0.5f);
	setActive(true);
	__getMotion().ChangeMotion(0);
}
