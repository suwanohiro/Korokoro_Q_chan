#include "Block_Move.hpp"

float Block_Move::_wave()
{
	float result = _moveRange * sin(2 * 3.14 * _moveSpeed * _gameTime);

	if (_isReverseMove) result *= -1;

	return result;
}

int Block_Move::_rand(int min, int max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(mt);
}

Block_Move::Block_Move(BlockDataElem blockData)
	: Block_Base(blockData)
	, _gameTime(0)
	, _moveRange(30.0f)
	, _moveSpeed(0.35f)
	, _isReverseMove(false)
{
	_moveRange += _rand(-5, 5);
	_moveSpeed += _rand(-0.1, 0.1);

	// 1‚Ì—”‚ªo‚½Žž‚Í”½“]‚µ‚Ä“®ì‚·‚é
	_isReverseMove = (_rand(0, 1) == 1);
}

void Block_Move::Update()
{
	if (!isActive()) return;
	Block_Base::Update();

	_gameTime += CUtilities::GetFrameSecond();
}

void Block_Move::Render()
{
	if (!isActive()) return;

	CRectangle rec = getTextureRect();
	if (isReverse()) {
		const float work = rec.Right;
		rec.Right = rec.Left;
		rec.Left = work;
	}

	Vector2 renderPos = getPosition() - __getScroll();
	renderPos.y += _wave();
	getTexture()->Render(renderPos.x, renderPos.y, rec);
}

CRectangle Block_Move::getRect()
{
	CRectangle rec = Block_Base::getRect();

	rec.Top += _wave();
	rec.Bottom += _wave();

	return rec;
}
