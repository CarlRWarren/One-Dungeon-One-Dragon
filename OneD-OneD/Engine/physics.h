#pragma once

#include "engine.h"
#include "singleton.h"
#include "vector2D.h"

class ENGINE_API Physics : public Singleton<Physics>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SetGravity(const Vector2D& gravity) { m_gravity = gravity; }
	const Vector2D& GetGravity() { return m_gravity; }

	friend Singleton<Physics>;

protected:
	Engine * m_engine;
	Vector2D m_gravity;
};