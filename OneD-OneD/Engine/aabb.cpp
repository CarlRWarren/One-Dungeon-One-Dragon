#include "aabb.h"
#include "renderer.h"

void AABB::Draw(const Color & color)
{
	float minx = m_min.x;
	float miny = m_min.y;
	float maxx = m_max.x;
	float maxy = m_max.y;

	Renderer::Instance()->DebugDrawLine(Vector2D(minx, miny), Vector2D(maxx, miny), color);
	Renderer::Instance()->DebugDrawLine(Vector2D(maxx, miny), Vector2D(maxx, maxy), color);
	Renderer::Instance()->DebugDrawLine(Vector2D(maxx, maxy), Vector2D(minx, maxy), color);
	Renderer::Instance()->DebugDrawLine(Vector2D(minx, maxy), Vector2D(minx, miny), color);
}