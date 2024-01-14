#include "Block_Base.h"

Block_Base::Block_Base(BlockData blockData, Vector2 position)
{
	_blockID = blockData.BlockID;
	setTexture(blockData.Texture);

	setPosition(position * getTextureSize());
}

Block_Base::~Block_Base()
{
	Release();
}
