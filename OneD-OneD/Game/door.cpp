#include "door.h"
#include "spriteComponent.h"
#include "aabbComponent.h"
#include "animationComponent.h"

void Door::Create(const Vector2D & position)
{
	SetTag("door");
	m_transform.position = position;
	m_transform.scale = Vector2D(1.0f, 1.0f);

	SpriteComponent* doorSpritecomponent = AddComponent<SpriteComponent>();
	doorSpritecomponent->Create("", Vector2D(0.5f, 0.5f));

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	animationComponent->Create(m_idleanimation, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

	AABBComponent* doorAabbComponent = AddComponent<AABBComponent>();
	doorAabbComponent->Create(Vector2D(0.5, 1.0f));

	m_transform.scale = Vector2D(5.0f, 5.0f);
	doorSpritecomponent->SetDepth(2);
}

void Door::OnEvent(const Event & event)
{
	if (event.eventID == "collision") {
		if (event.sender->GetTag() == "hero")
		{


		}
	}
}