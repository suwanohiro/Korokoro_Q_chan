#pragma once

#include "../../../swnLibrary/swnLibrary.h"

struct BlockDataElem {
	std::string ID = "";
	spCTexture Texture = nullptr;

	bool operator==(BlockDataElem r) {
		return (r.ID == ID) && (r.Texture == Texture);
	}
};

class BlockIDElem {
private:
	std::string _ID;

public:
	BlockIDElem(std::string ID)
		: _ID(ID)
	{}

	bool operator==(BlockIDElem data) {
		return data.ID() == _ID;
	}

	bool operator==(std::string data) {
		return data == _ID;
	}

	std::string ID() { return _ID; }
	bool isID(std::string ID) { return _ID == ID; }
	bool isBlank() { return isID("blank"); }
	bool isPlayer() { return isID("Player"); }
};
