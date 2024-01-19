#pragma once

#include "../../../swnLibrary/swnLibrary.h"

struct BlockDataElem {
	std::string ID;
	spCTexture Texture;

	bool operator==(BlockDataElem r) {
		return (r.ID == ID) && (r.Texture == Texture);
	}
};