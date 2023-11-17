#include "MapTile.h"

MapTile::MapTile(Vector2 position, CTexture* mapTexture)
{
	_mapTexture = mapTexture;
	_position = position;
	_renderRec = CRectangle(
		0, 0,
		_mapTexture->GetWidth(),
		_mapTexture->GetHeight()
	);
}

void MapTile::Render()
{
	_mapTexture->Render(_position.x, _position.y, _renderRec);
}
