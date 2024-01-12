#include "Block_Base.h"

Block_Base::Block_Base(BlockData blockData, Vector2 position)
{
	_blockData = blockData;

	Vector2 textureSize = {
		(float)getTexture()->GetWidth(),
		(float)getTexture()->GetHeight()
	};

	textureSize.x = 40;
	textureSize.y = 40;

	_position = Vector2(
		position.x * textureSize.x,
		position.y * textureSize.y
	);

	textureSize += _position;

	_rect = CRectangle(_position, textureSize);
}

Block_Base::~Block_Base()
{
	Release();
}

void Block_Base::Render()
{
	getTexture()->Render(_position.x, _position.y);
	CGraphicsUtilities::RenderRect(_rect, getRGB(WebColor::lightblue));
}

void Block_Base::Release()
{
	getTexture()->Release();
}
