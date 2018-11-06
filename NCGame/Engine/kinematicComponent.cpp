#include"kinematicComponent.h"
#include "timer.h"
#include "physics.h"
#include "entity.h"
#include "transform.h"
void KinematicComponent::Create(float velocityMax, float dampening, bool enableGravity)
{
	m_velocityMax = velocityMax;
	m_dampening = dampening;
	m_enableGravity = enableGravity;

	m_forceType = eForceType::FORCE;
	m_force = Vector2D::zero;
	m_velocity = Vector2D::zero;

}

void KinematicComponent::Destroy()
{
	//
}

void KinematicComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	Vector2D force = (m_enableGravity) ? m_force + Physics::Instance()->GetGravity() : m_force;

	m_velocity = m_velocity + (force * dt);
	float length = m_velocity.Length();
	if (length > m_velocityMax) {
		m_velocity = m_velocity.Normalized() * m_velocityMax;
	}
	
	m_owner->GetTransform().position = m_owner->GetTransform().position + (m_velocity * dt);

	m_velocity = m_velocity * pow(m_dampening, dt);
	if (m_forceType == eForceType::IMPULSE) {
		m_force = Vector2D::zero;
	}
}

void KinematicComponent::ApplyForce(const Vector2D & force, eForceType forceType)
{
	m_forceType = forceType;
	switch (m_forceType) {
	case FORCE:
	case IMPULSE:
		m_force = force;
		break;
	case VELOCITY:
		m_force = Vector2D::zero;
		m_velocity = force;
		break;
	}

}
