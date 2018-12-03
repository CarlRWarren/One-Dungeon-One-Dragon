#include "ship.h"
#include "transform.h"
#include "shipControllerComponent.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "explosion.h"
#include "eventManager.h"
#include "animationComponent.h"

void Ship::Create(const Vector2D & position)
{
	SetTag("player");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(800.0f, 0.3f, false);

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(150.0f);

	SpriteComponent* spritecomponent01 = AddComponent<SpriteComponent>();
	spritecomponent01->Create("galaga\\ship.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();
}

void Ship::Update()
{
	Entity::Update();
	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
	m_transform.position.y = Math::Clamp(m_transform.position.y, 0.0f, size.y);

}
void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision") {
		if (event.sender->GetTag() == "enemy" || event.sender->GetTag() == "enemyMissile") {
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position, Explosion::eType::PLAYER);
			SetState(Entity::DESTROY);
			Event _event;
			_event.eventID = "player_death";
			EventManager::Instance()->SendGameMessage(_event);
		}
	}
}