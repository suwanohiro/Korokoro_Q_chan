#pragma once

#include "../swnLibrary/swnLibrary.h"
#include "./Scene_List.hpp"

class Scene_Base
{
private:
	/// <summary>
	/// シーン終了フラグ
	/// </summary>
	bool _isSceneEnd;

	/// <summary>
	/// 次のシーン
	/// </summary>
	Scene_List _NextScene;

protected:
	/// <summary>
	/// シーンを変更する
	/// </summary>
	/// <param name="next"></param>
	void __changeScene(Scene_List next);

public:
	Scene_Base();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// 開放処理
	/// </summary>
	virtual void Release() = 0;
};

