#pragma once

#include "./Block_Base.h"

class Block_Ground : public Block_Base
{
public:
	Block_Ground(BlockDataElem blockData, Vector2 position);
};

using spBlock_Ground = std::shared_ptr<Block_Ground>;
