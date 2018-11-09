#include "dragon.h"
#include "transform.h"
#include "shipControllerComponent.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "explosion.h"
#include "eventManager.h"
#include "animationComponent.h"
#include <iostream>

void Dragon::Create(const Vector2D & position)
{
	SetTag("dragon");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* dragonSpritecomponent = AddComponent<SpriteComponent>();
	dragonSpritecomponent->Create("", Vector2D(0.5f, 0.5f));

	AnimationComponent* dragonAnimation = AddComponent<AnimationComponent>();
	std::vector<std::string> animations = { "Sprites\\sleepingdragonframe1.png","Sprites\\sleepingdragonframe2.png" ,"Sprites\\sleepingdragonframe3.png" ,"Sprites\\sleepingdragonframe4.png" ,"Sprites\\sleepingdragonframe5.png" };
	dragonAnimation->Create(animations, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

	AABBComponent* dragonAabbComponent = AddComponent<AABBComponent>();
	dragonAabbComponent->Create();
	m_transform.scale = Vector2D(5.0f, 5.0f);
	dragonSpritecomponent->SetDepth(2);
}

void Dragon::Update()
{
	Entity::Update();
	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
	m_transform.position.y = Math::Clamp(m_transform.position.y, 0.0f, size.y);

}
void Dragon::OnEvent(const Event & event)
{
	if (event.eventID == "collision") {
		if (event.sender->GetTag() == "player" || event.sender->GetTag() == "player") {
			std::cout << "Dragon Hit" << std::endl;
		}
	}
}