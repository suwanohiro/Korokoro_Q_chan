#include "PlayerShot.hpp"

PlayerShot::PlayerShot()
	: Shot()
{
}

void PlayerShot::Update()
{
	if (!isActive()) return;

	const float x = (isReverse()) ? -PlayerShot_Speed : PlayerShot_Speed;
	updatePosition(x, 0);

	// 画面外なら無効化
	// TODO : TextureSizeで実行可能か確認
	const bool isOutLeft = (getPosition().x < __getScroll().x - getTextureSize().x);
	const bool isOutRight = (getPosition().x > __getScreenSize().x + __getScroll().x + getTextureSize().x);
	if (isOutLeft || isOutRight) isActive(false);
}

void PlayerShot::Render()
{
	if (!isActive()) return;

	const float x = getPosition().x - __getScroll().x;
	getTexture()->Render(x, getPosition().y);
}

void PlayerShot::Fire(Vector2 playerPos, bool IsReverse)
{
	Shot::Fire(playerPos);
	isReverse(IsReverse);
}

