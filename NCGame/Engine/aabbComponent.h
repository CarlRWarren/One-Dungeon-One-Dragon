#pragma once
#include "engine.h"
#include "aabb.h"
#include "collisionComponent.h"
class ENGINE_API AABBComponent : public ICollisionComponent 
{
public:
	AABBComponent(Entity* owner) : ICollisionComponent(owner) {}
	void Create(const Vector2D& offset = Vector2D::one);
	void Destroy();
	void Update();

	bool Intersects(ICollisionComponent* other);
protected:
	AABB m_aabb;
	Vector2D m_offset;
};