#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Hero : public Entity
{
public:
	Hero(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Hero() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);
protected:
	bool m_isFlipped = false;
};