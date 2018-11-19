#pragma once

#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "matrix22.h"

#include "controllerComponent.h"


class HeroControllerComponent : public IControllerComponent
{
public:
	HeroControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();


protected:
	float m_speed;
};
