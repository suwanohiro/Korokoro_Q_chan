#include "Block_Base.h"

Block_Base::Block_Base(BlockDataElem blockData)
{
	_blockID = blockData.ID;
	setTexture(blockData.Texture);
}

Block_Base::~Block_Base()
{
	Release();
}

void Block_Base::Initialize(Vector2 initPos)
{
	setPosition(initPos * getTextureSize());
}
