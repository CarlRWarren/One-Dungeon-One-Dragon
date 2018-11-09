#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Dragon : public Entity
{
public:
	Dragon(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Dragon() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);
};