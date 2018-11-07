#pragma once
#include "entity.h"

class ENGINE_API Waypoint : public Entity
{
public:
	Waypoint(Scene* scene, const ID id) : Entity(scene, id) {}
	~Waypoint() {}

	void Create(const Vector2D& position, const Vector2D& size, Entity* owner);
	void Update();
protected:
	Entity* m_owner = nullptr;
};