#pragma once

#include "../swnLibrary/swnLibrary.h"


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

protected:

public:
	GameObject();
	~GameObject();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="filePath">テクスチャファイルパス</param>
	virtual bool TextureLoad(std::string filePath);

	/// <summary>
	/// 読み込み処理
	/// </summary>
	virtual bool Load() { return true; };

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize(Vector2 initPos);

	virtual void FixedUpdate();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	virtual void LateUpdate();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Render();

	/// <summary>
	/// 当たり判定描画
	/// </summary>
	virtual void RenderRect();

	/// <summary>
	/// 当たり判定描画
	/// </summary>
	/// <param name="borderColor"></param>
	virtual void RenderRect(const char* borderColor);

	/// <summary>
	/// 開放処理
	/// </summary>
	virtual void Release();

	/// <summary>
	/// スクリーンサイズを取得する
	/// </summary>
	Vector2 getScreenSize();

	/// <summary>
	/// 座標を取得する
	/// </summary>
	/// <returns>座標</returns>
	Vector2 getPosition() { return _position; }

	/// <summary>
	/// 当たり判定用矩形取得
	/// </summary>
	/// <returns>当たり判定用矩形</returns>
	CRectangle getTextureRect();

	/// <summary>
	/// 当たり判定用矩形取得
	/// </summary>
	/// <returns>当たり判定用矩形</returns>
	virtual CRectangle getRect() { return getTextureRect(); };

	/// <summary>
	/// テクスチャ取得 (share ptr)
	/// </summary>
	spCTexture getspTexture() { return _texture; }

	/// <summary>
	/// テクスチャ取得
	/// </summary>
	CTexture* getTexture() { return getspTexture().get(); }

	/// <summary>
	/// テクスチャサイズ取得
	/// </summary>
	/// <returns>テクスチャサイズ</returns>
	Vector2 getTextureSize() { return _textureSize; }

	/// <summary>
	/// アクティブ状態かどうか
	/// </summary>
	bool isActive() { return _isActive; }
	
	/// <summary>
	/// 画像反転表示するかどうか
	/// </summary>
	bool isReverse() { return _isReverse; }

	void setTexture(spCTexture value);

	void setPosition(Vector2 pos) { _position = pos; }
	void setPosition(float x, float y) { _position = Vector2(x, y); }

	void setActive(bool value) { _isActive = value; }

	void setReverse(bool value) { _isReverse = value; }
};

using spGameObject = std::shared_ptr<GameObject>;
