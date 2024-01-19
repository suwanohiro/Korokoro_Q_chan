#pragma once

#include "../GameObject/GameObject.hpp"
#include "./BlockData.hpp"

class Block_Base : public GameObject
{
protected:
	std::string _blockID;

public:
	Block_Base(BlockDataElem blockData);
	~Block_Base();

	virtual void Initialize(Vector2 initPos) override;

	/// <summary>
	/// BlockIDŽæ“¾
	/// </summary>
	/// <returns>BlockID</returns>
	std::string getBlockID() { return _blockID; }
};

using spBlock_Base = std::shared_ptr<Block_Base>;
