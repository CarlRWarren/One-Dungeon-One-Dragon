#include "enemyControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transform.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "missile.h"
#include "audioSystem.h"

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
}

void EnemyControllerComponent::Destroy()
{

}

void EnemyControllerComponent::Update()
{
	Vector2D force = Vector2D::up;

	Entity* player = m_owner->GetScene()->GetEntitiesWithID("player");
	if (player) {
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -32.0f) force.x = -1.0f;
		if (dx > 32.0f) force.x = 1.0f;

	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic) {
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f) {
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create("enemyMissile", m_owner->GetTransform().position, Vector2D::up, 200.0f);
		m_owner->GetScene()->AddEntity(missile);
		AudioSystem::Instance()->PlaySound("fire", false);
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
	}
}

