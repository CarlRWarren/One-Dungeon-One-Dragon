#pragma once
#include "engine.h"
#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "matrix22.h"
#include "controllerComponent.h"


class ENGINE_API TransformControllerComponent : public IControllerComponent
{
public:
	TransformControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float speed, float rotateRate);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
	float m_rotation;
	float m_rotateRate = 0.0f;
	Vector2D m_position;
};
