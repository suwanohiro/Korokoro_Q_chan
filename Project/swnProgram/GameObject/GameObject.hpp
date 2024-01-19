#pragma once

#include "../../swnLibrary/swnLibrary.h"


class GameObject
{
private:
	Vector2 _screenSize;

	bool _isActive;

	Vector2 _textureSize;

	spCTexture _texture;
	bool _isReverse;

	void __setTextureSize();

	Vector2 _position;

	Vector2 _scroll;

protected:
	/// <summary>
	/// �X�N���[���T�C�Y���擾����
	/// </summary>
	Vector2 __getScreenSize();

	Vector2 __getScroll() { return _scroll; }
	void __setScroll(Vector2 value) { _scroll = value; }

public:
	GameObject();
	~GameObject();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="filePath">�e�N�X�`���t�@�C���p�X</param>
	virtual bool TextureLoad(std::string filePath);

	/// <summary>
	/// �ǂݍ��ݏ���
	/// </summary>
	virtual bool Load() { return true; };

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(Vector2 initPos);

	virtual void FixedUpdate(Vector2 scroll);

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();

	virtual void LateUpdate();

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render();

	/// <summary>
	/// �����蔻��`��
	/// </summary>
	virtual void RenderRect();

	/// <summary>
	/// �����蔻��`��
	/// </summary>
	/// <param name="borderColor"></param>
	virtual void RenderRect(const char* borderColor);

	/// <summary>
	/// �J������
	/// </summary>
	virtual void Release();

	/// <summary>
	/// ���W���擾����
	/// </summary>
	/// <returns>���W</returns>
	Vector2 getPosition() { return _position; }

	/// <summary>
	/// �����蔻��p��`�擾
	/// </summary>
	/// <returns>�����蔻��p��`</returns>
	CRectangle getTextureRect();

	/// <summary>
	/// �����蔻��p��`�擾
	/// </summary>
	/// <returns>�����蔻��p��`</returns>
	virtual CRectangle getRect() { return getTextureRect(); };

	/// <summary>
	/// �e�N�X�`���擾
	/// </summary>
	spCTexture getTexture();

	/// <summary>
	/// �e�N�X�`���T�C�Y�擾
	/// </summary>
	/// <returns>�e�N�X�`���T�C�Y</returns>
	Vector2 getTextureSize() { return _textureSize; }

	/// <summary>
	/// �A�N�e�B�u��Ԃ��ǂ���
	/// </summary>
	bool isActive() { return _isActive; }
	void isActive(bool value) { _isActive = value; }
	
	/// <summary>
	/// �摜���]�\�����邩�ǂ���
	/// </summary>
	bool isReverse() { return _isReverse; }
	void isReverse(bool value) { _isReverse = value; }

	void setTexture(spCTexture value);

	void setPosition(Vector2 pos) { _position = pos; }
	void setPosition(float x, float y) { setPosition(Vector2(x, y)); }
	void updatePosition(Vector2 pos) { _position += pos; }
	void updatePosition(float x, float y) { updatePosition(Vector2(x, y)); }
};

using spGameObject = std::shared_ptr<GameObject>;
