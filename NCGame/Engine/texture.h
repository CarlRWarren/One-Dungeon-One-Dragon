#pragma once
#include "engine.h"
#include "object.h"
#include "vector2D.h"

class ENGINE_API Texture : public Object
{
public:
	Texture();
	~Texture();

	bool Create(const std::string& textureName);
	bool CreateTextureFromSurface(SDL_Surface * surface);
	void Destroy();
	void Draw(const Vector2D& position, const Vector2D& origin = Vector2D::zero, const Vector2D& scale = Vector2D::one, float angle = 0.0f);


	Vector2D GetSize() const;

	friend class Renderer;

protected:
	SDL_Texture* m_sdlTexture;
};