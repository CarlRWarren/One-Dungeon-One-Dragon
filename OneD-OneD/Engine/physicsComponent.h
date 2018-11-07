#pragma once

#include "component.h"
#include "vector2D.h"

class ENGINE_API IPhysicsComponent : public Component
{
public:
	enum eForceType
	{
		FORCE,
		IMPULSE,
		VELOCITY
	};

public:
	IPhysicsComponent(Entity* owner) : Component(owner) {}

	virtual void SetVelocity(const Vector2D& velocity) = 0;
	virtual const Vector2D& GetVelocity() const = 0;
	virtual void SetVelocityMax(float velocityMax) = 0;

	virtual void ApplyForce(const Vector2D& force, eForceType forceType) = 0;
	virtual void EnableGravity(bool enableGravity = true) = 0;
};