#pragma once

#include "../../../GameObject/GameObject.hpp"

struct BlockData {
	std::string BlockID;
	spCTexture Texture;
};

class Block_Base : public GameObject
{
protected:
	std::string _blockID;

public:
	Block_Base(BlockData blockData, Vector2 position);
	~Block_Base();

	/// <summary>
	/// BlockIDŽæ“¾
	/// </summary>
	/// <returns>BlockID</returns>
	std::string getBlockID() { return _blockID; }
};

using spBlock_Base = std::shared_ptr<Block_Base>;
