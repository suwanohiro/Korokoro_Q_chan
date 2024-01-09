#pragma once

#include "../swnLibrary/swnLibrary.h"
#include "./Scene_List.hpp"

class Scene_Base
{
private:
	/// <summary>
	/// �V�[���I���t���O
	/// </summary>
	bool _isSceneEnd;

	/// <summary>
	/// ���̃V�[��
	/// </summary>
	Scene_List _NextScene;

protected:
	/// <summary>
	/// �V�[����ύX����
	/// </summary>
	/// <param name="next"></param>
	void __changeScene(Scene_List next);

public:
	Scene_Base();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// �J������
	/// </summary>
	virtual void Release() = 0;
};

