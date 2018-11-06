#pragma once
#include "vector2D.h"
#include "color.h"

class ENGINE_API AABB
{
public:
	AABB() : m_min(Vector2D::zero), m_max(Vector2D::zero) {}
	AABB(const Vector2D& min, const Vector2D& max) : m_min(min), m_max(max) {}
		
	void Build(const Vector2D& center, float halfSize) 
	{
		Build(center, Vector2D(halfSize, halfSize));
	}
	
	void Build(const Vector2D& center, const Vector2D& halfSize)
	{
		m_min = center - halfSize;
		m_max = center + halfSize;
	}

	void Translate(const Vector2D& v) { m_min += v; m_max += v; }
	void Scale(float s) { m_min *= s; m_max *= s; }

	const Vector2D& Max() const { return m_max; }
	const Vector2D& Min() const { return m_min; }
	
	Vector2D Center() const { return (m_min + m_max) * 0.5f; }
	Vector2D Extents() const { return (m_max - m_min) * 0.5f; }

	bool Contains(const Vector2D& point)
	{
		return (point.x >= m_min.x && point.x <= m_max.x && point.y >= m_min.y && point.y <= m_max.y);
	}

	bool Intersects(const AABB& aabb)
	{
		return (aabb.m_min.x < m_max.x && aabb.m_max.x > m_min.x &&aabb.m_min.y < m_max.y && aabb.m_max.y > m_min.y);
	}

	void Draw(const Color& color = Color::red);

protected:
	Vector2D m_min;
	Vector2D m_max;
};