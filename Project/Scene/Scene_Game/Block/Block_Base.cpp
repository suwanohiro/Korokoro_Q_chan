#include "Block_Base.h"

Block_Base::Block_Base(BlockDataElem blockData, Vector2 position)
{
	_blockID = blockData.ID;
	setTexture(blockData.Texture);

	setPosition(position * getTextureSize());
}

Block_Base::~Block_Base()
{
	Release();
}
