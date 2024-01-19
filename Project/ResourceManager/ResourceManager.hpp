#pragma once

#include "../swnLibrary/swnLibrary.h"

enum class ImageTag {
	Null = -1,
	Player,
	Enemy,
	Length
};

class ResourceManager
{
private:
	std::vector<CTexture> _images;
};

class player {
public:
	CTexture texture;
};

class enemy {
public:
	CTexture texture;
};

int main() {
	CTexture image;

	player a;
	a.texture = image;

	player b;
	b.texture = image;
}