#pragma once

#include "../../../swnLibrary/swnLibrary.h"

struct BlockData {
	std::string BlockID;
	spCTexture Texture;
};

class Block_Base
{
protected:
	BlockData _blockData;

	/// <summary>
	/// ���W
	/// </summary>
	Vector2 _position;

	/// <summary>
	/// �����蔻��
	/// </summary>
	CRectangle _rect;

public:
	Block_Base(BlockData blockData, Vector2 position);
	~Block_Base();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �����蔻��`��
	/// </summary>
	void RenderRect();

	/// <summary>
	/// �J������
	/// </summary>
	void Release();

	/// <summary>
	/// BlockID�擾
	/// </summary>
	/// <returns>BlockID</returns>
	std::string getBlockID() { return _blockData.BlockID; }

	/// <summary>
	/// �e�N�X�`���擾 (share ptr)
	/// </summary>
	spCTexture getspTexture() { return _blockData.Texture; }

	/// <summary>
	/// �e�N�X�`���擾
	/// </summary>
	CTexture* getTexture() { return getspTexture().get(); }

	/// <summary>
	/// �����蔻��p��`�擾
	/// </summary>
	/// <returns>�����蔻��p��`</returns>
	CRectangle getRect() { return _rect; }
};

using spBlock_Base = std::shared_ptr<Block_Base>;
