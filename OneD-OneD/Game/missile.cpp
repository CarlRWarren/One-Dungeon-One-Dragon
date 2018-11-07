#include "missile.h"
#include "transform.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "renderer.h"
#include "aabbComponent.h"
void Missile::Create(const ID& tag, const Vector2D & position, const Vector2D& direction, float speed)
{
	m_lifetime = 5.0f;
	SetTag(tag);
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	

	if (tag == "playerMissile") {
		KinematicComponent* kinematic = AddComponent<KinematicComponent>();
		kinematic->Create(500.0f, 0.9f, false);
		kinematic->ApplyForce(direction * speed, KinematicComponent::FORCE);

		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("missile01.png", Vector2D(0.5f, 0.5f));
	}
	else if (tag == "enemyMissile") {
		KinematicComponent* kinematic = AddComponent<KinematicComponent>();
		kinematic->Create(500.0f, 0.9f, false);
		kinematic->ApplyForce(direction * speed, KinematicComponent::VELOCITY);


		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("missile02.png", Vector2D(0.5f, 0.5f));
		m_transform.rotation += 180.0f;
	}

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(.5f,0.9f));
}

void Missile::Update()
{
	Entity::Update();
	

	m_lifetime = m_lifetime - Timer::Instance()->DeltaTime();
	if (m_lifetime <= 0.0f) {
		SetState(Entity::DESTROY);
	}
}


void Missile::OnEvent(const Event & event)
{
 	if (event.eventID == "collision") {
		if (event.sender->GetTag() == "enemy" && m_tag == "playerMissile") {
				SetState(Entity::DESTROY);
		}
	}
}
