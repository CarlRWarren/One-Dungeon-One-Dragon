#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Ship : public Entity
{
public:
	Ship(Scene* scene, const ID& id) : Entity(scene,id) {}
	~Ship() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);

};