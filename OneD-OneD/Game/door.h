#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Door : public Entity
{
public:
	Door(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Door() {}

	void Create(const Vector2D& position);

	void OnEvent(const Event & event);
};