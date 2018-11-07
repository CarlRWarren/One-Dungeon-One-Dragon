#pragma once
#include "entity.h"
#include "vector2D.h"

class EnemyMissile : public Entity
{
public:
	EnemyMissile(Scene* scene) : Entity(scene) {}
	~EnemyMissile() {}

	void Create(const Vector2D& position, const Vector2D& direction, float speed);
	void Update();


	void OnEvent(const Event & event);

protected:
	float m_lifetime;
};