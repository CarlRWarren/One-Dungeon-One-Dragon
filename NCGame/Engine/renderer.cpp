#include "renderer.h"
#include <cassert>
#include "texture.h"


bool Renderer::Initialize(Engine* engine)
{
	m_engine = engine;
	m_renderer = SDL_CreateRenderer(m_engine->GetWindow(), -1, 0);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	return true;
}

void Renderer::Shutdown()
{
	IMG_Quit();
}

void Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);
}

void Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);
}

void Renderer::SetColor(const Color & color)
{
	SDL_SetRenderDrawColor(m_renderer, color.ConvertU8(0), color.ConvertU8(1), color.ConvertU8(2),255);
}

void Renderer::DrawTexture(SDL_Texture * texture, const Vector2D & position, float angle)
{
	SDL_Point point = position;
	SDL_Rect dest = { point.x,point.y, 0,0 };
	SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);

}

void Renderer::DrawTexture(SDL_Texture * texture, const Vector2D & position, const Vector2D & scale, float angle)
{
	SDL_Point point = position;
	SDL_Rect dest = { point.x,point.y, 0,0 };
	SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
	Vector2D size(dest.w, dest.h);
	size = size * scale;
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);

}

void Renderer::DrawTexture(Texture * texture, const Vector2D & position, const Vector2D & scale, float angle)
{
	DrawTexture(texture->m_sdlTexture, position, scale, angle);
}

void Renderer::DebugDrawLine(const Vector2D & start, const Vector2D & end, const Color color)
{
	if (m_engine->IsDebug()) {
		int x1 = static_cast<int>(start.x);
		int y1 = static_cast<int>(start.y);
		int x2 = static_cast<int>(end.x);
		int y2 = static_cast<int>(end.y);

		SetColor(color);
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}
}

Vector2D Renderer::GetSize()
{
	SDL_Point size;
	SDL_GetRendererOutputSize(m_renderer, &size.x, &size.y);
	return size;
}
