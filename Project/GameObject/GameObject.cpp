#include "GameObject.hpp"

void GameObject::__setTextureSize()
{
	_textureSize = Vector2(
		(float)getTexture()->GetWidth(),
		(float)getTexture()->GetHeight()
	);
}

GameObject::GameObject()
	: _isActive(true)
	, _textureSize(0, 0)
	, _position(0, 0)
	, _texture(new CTexture())
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
	setActive(true);
}

void GameObject::FixedUpdate()
{
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

	getTexture()->Render(_position.x, _position.y, rec);
}

void GameObject::RenderRect()
{
	RenderRect(WebColor::black);
}

void GameObject::RenderRect(const char* borderColor)
{
	CGraphicsUtilities::RenderRect(getTextureRect(), getRGB(borderColor));
}

void GameObject::Release()
{
	getTexture()->Release();
}

Vector2 GameObject::getScreenSize()
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

void GameObject::setTexture(spCTexture value)
{
	_texture = value;
	__setTextureSize();
}
