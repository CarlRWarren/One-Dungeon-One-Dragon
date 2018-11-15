#pragma once
#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "matrix22.h"
#include "controllerComponent.h"


class EnemyControllerComponent : public IControllerComponent
{
public:
	EnemyControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();

protected:
	float m_speed;
	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 5.0f;
};
