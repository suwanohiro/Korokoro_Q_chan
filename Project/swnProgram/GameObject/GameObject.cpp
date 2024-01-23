#include "GameObject.hpp"

void GameObject::__setTextureSize()
{
	if (getTexture() == nullptr) return;

	_textureSize = Vector2(
		(float)getTexture()->GetWidth(),
		(float)getTexture()->GetHeight()
	);
}

GameObject::GameObject()
	: _isActive(true)
	, _textureSize(0, 0)
	, _position(0, 0)
	, _texture(nullptr)
	, _isReverse(false)
{
}

GameObject::~GameObject()
{
	Release();
}

bool GameObject::TextureLoad(std::string filePath)
{
	const bool result = getTexture()->Load(filePath.c_str());
	__setTextureSize();

	return result;
}

void GameObject::Initialize(Vector2 initPos)
{
	_position = initPos;
	isActive(true);
}

void GameObject::FixedUpdate(Vector2 scroll)
{
	__setScroll(scroll);
}

void GameObject::Update()
{
	if (!isActive()) return;
}

void GameObject::LateUpdate()
{
}

void GameObject::Render()
{
	if (!isActive()) return;

	CRectangle rec = getTextureRect();
	if (isReverse()) {
		const float work = rec.Right;
		rec.Right = rec.Left;
		rec.Left = work;
	}

	const Vector2 renderPos = getPosition() - __getScroll();
	getTexture()->Render(renderPos.x, renderPos.y, rec);
}

void GameObject::RenderRect()
{
	RenderRect(WebColor::black);
}

void GameObject::RenderRect(const char* borderColor)
{
	CRectangle rec = getTextureRect();

	rec.Left -= __getScroll().x;
	rec.Right -= __getScroll().x;
	rec.Top -= __getScroll().y;
	rec.Bottom -= __getScroll().y;


	CGraphicsUtilities::RenderRect(rec, getRGB(borderColor));
}

void GameObject::Release()
{
	if (getTexture() != nullptr) getTexture()->Release();
}

Vector2 GameObject::__getScreenSize()
{
	return Vector2(
		(float)g_pGraphics->GetTargetWidth(),
		(float)g_pGraphics->GetTargetHeight()
	);
}

CRectangle GameObject::getTextureRect()
{
	const Vector2 work = _position + _textureSize;
	return CRectangle(_position, work);
}

spCTexture GameObject::getTexture()
{
	if (_texture == nullptr) {
		OutputDebugString("[ Error ] Texture is nullptr\n");
	}
	return _texture;
}

void GameObject::setTexture(spCTexture value)
{
	_texture = value;
	__setTextureSize();
}
