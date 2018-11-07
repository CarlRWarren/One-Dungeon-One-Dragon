#pragma once
#include "engine.h"
#include "singleton.h"
#include "color.h"
#include "vector2D.h"
#include <map>
#include "texture.h"
#include <SDL_image.h>

class ENGINE_API Renderer : public Singleton<Renderer>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

public:
	Renderer() {}
	~Renderer() {}

	SDL_Renderer* GetRenderer() { return m_renderer; }
	void BeginFrame();
	void EndFrame();
	void SetColor(const Color& color);
	void DrawTexture(SDL_Texture* texture, const Vector2D& position, float angle);
	void DrawTexture(SDL_Texture* texture, const Vector2D& position, const Vector2D&scale, float angle);
	void DrawTexture(Texture* texture, const Vector2D& position, const Vector2D&scale, float angle);
	void DebugDrawLine(const Vector2D& start, const Vector2D& end, const Color color = Color::red);

	Vector2D GetSize();

private:
	Engine * m_engine;
	SDL_Renderer* m_renderer = nullptr;
};

