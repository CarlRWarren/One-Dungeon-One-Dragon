#include "renderer.h"
#include "texture.h"
#include "assert.h"
#include "textureManager.h"

Texture::Texture()
{
	//
}

Texture::~Texture()
{
	Destroy();
}

Vector2D Texture::GetSize() const
{
	SDL_Point point;
	SDL_QueryTexture(m_sdlTexture, nullptr, nullptr, &point.x, &point.y);
	
	return point;
}

bool Texture::Create(const std::string& textureName)
{
	m_sdlTexture = TextureManager::Instance()->GetTexture(textureName);
	assert(m_sdlTexture);
	return (m_sdlTexture);
}

bool Texture::CreateTextureFromSurface(SDL_Surface * surface)
{
	m_sdlTexture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
	assert(m_sdlTexture);
	return true;
}

void Texture::Destroy()
{
	/*if (m_sdlTexture)
	{
		SDL_DestroyTexture(m_sdlTexture);
		m_sdlTexture = nullptr;
	}*/
}

void Texture::Draw(const Vector2D & position, const Vector2D & origin, const Vector2D & scale, float angle)
{
	Vector2D size = GetSize();
	size = size * scale;
	Vector2D _position = position - (size * origin);

	SDL_Rect dest;
	dest.x = static_cast<int>(_position.x);
	dest.y = static_cast<int>(_position.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (m_IsFlipped) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	SDL_RenderCopyEx(Renderer::Instance()->GetRenderer(), m_sdlTexture, nullptr, &dest, angle, nullptr, flip);
}