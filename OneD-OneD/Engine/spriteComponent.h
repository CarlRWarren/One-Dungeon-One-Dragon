#pragma once

#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "renderComponent.h"

class Texture;

class ENGINE_API SpriteComponent : public IRenderComponent
{
public:
	SpriteComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& textureName, const Vector2D& origin = Vector2D::zero);
	void Destroy();
	void Update();

	void Draw();

	void SetTexture(Texture* texture) { m_texture = texture; }
	Texture* GetTexture() { return m_texture; }
	const Vector2D& GetOrigin() { return m_origin; }

protected:
	Texture* m_texture = nullptr;
	Vector2D m_uv1;
	Vector2D m_uv2;
	Vector2D m_origin;

};
