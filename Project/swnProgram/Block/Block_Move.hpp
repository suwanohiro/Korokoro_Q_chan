#pragma once

#include "./Block_Base.h"
#include <random>

class Block_Move : public Block_Base
{
private:
	float _gameTime;
	float _moveRange;
	float _moveSpeed;
	bool _isReverseMove;

	float _wave();

	int _rand(int min, int max);

public:
	Block_Move(BlockDataElem blockData);

	void Update() override;
	void Render() override;

	CRectangle getRect() override;
};

using spBlock_Move = std::shared_ptr<Block_Move>;
