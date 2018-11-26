#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Fountain : public Entity
{
public:
	Fountain(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Fountain() {}

	void Create(const Vector2D& position,int version);
	void Update();

	void OnEvent(const Event & event);
};