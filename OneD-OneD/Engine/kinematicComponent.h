#pragma once

#include "physicsComponent.h"

class ENGINE_API KinematicComponent : public IPhysicsComponent
{
public:
	KinematicComponent(Entity* owner) : IPhysicsComponent(owner) {}

	void Create(float velocityMax = 500.0f, float dampening = 1.0f, bool enableGravity = false);
	void Destroy();
	void Update();

	void SetVelocity(const Vector2D& velocity) { m_velocity = velocity; }
	const Vector2D& GetVelocity() const { return m_velocity; }
	void SetVelocityMax(float velocityMax) { m_velocityMax = velocityMax; }
	
	void ApplyForce(const Vector2D& force, eForceType forceType);
	void EnableGravity(bool enableGravity = true) { m_enableGravity = enableGravity; }

protected:
	bool m_enableGravity = false;
	float m_dampening = 1.0f;
	eForceType m_forceType;
	Vector2D m_velocity;
	float m_velocityMax;
	Vector2D m_force;
};