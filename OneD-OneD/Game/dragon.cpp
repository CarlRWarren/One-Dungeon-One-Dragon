#include "dragon.h"
#include "transform.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "eventManager.h"
#include "animationComponent.h"
#include <iostream>

void Dragon::Create(const Vector2D & position, std::string anim)
{
	SetTag("dragon");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* dragonSpritecomponent = AddComponent<SpriteComponent>();
	dragonSpritecomponent->Create("", Vector2D(0.5f, 0.5f));

	if (anim == "default") 
	{
	AnimationComponent* dragonAnimation = AddComponent<AnimationComponent>();
	std::vector<std::string> animations = { "Sprites\\sleepingdragonframe1.png","Sprites\\sleepingdragonframe2.png" ,"Sprites\\sleepingdragonframe3.png" ,"Sprites\\sleepingdragonframe4.png" ,"Sprites\\sleepingdragonframe5.png" };
	dragonAnimation->Create(animations, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);
	}
	else if (anim == "green")
	{
		AnimationComponent* dragonAnimation = AddComponent<AnimationComponent>();
		std::vector<std::string> animations = { "Sprites\\sleepingdragonframe1.png","Sprites\\sleepingdragongreenframe2.png" ,"Sprites\\sleepingdragongreenframe3.png" ,"Sprites\\sleepingdragongreenframe4.png" ,"Sprites\\sleepingdragongreenframe5.png" };
		dragonAnimation->Create(animations, 12.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME);
	}
	else if (anim == "stab")
	{
		AnimationComponent* dragonAnimation = AddComponent<AnimationComponent>();
		std::vector<std::string> animations = { "Sprites\\sleepingdragonframe1.png","Sprites\\sleepingdragonstabframe2.png" ,"Sprites\\sleepingdragonstabframe3.png" ,"Sprites\\sleepingdragonstabframe4.png" ,"Sprites\\sleepingdragonstabframe5.png" };
		dragonAnimation->Create(animations, 12.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME);
	}
	AABBComponent* dragonAabbComponent = AddComponent<AABBComponent>();
	dragonAabbComponent->Create(Vector2D(0.75f, 0.75f));

	m_transform.scale = Vector2D(5.0f, 5.0f);
	dragonSpritecomponent->SetDepth(2);
}

void Dragon::Update()
{
	Entity::Update();
}
void Dragon::OnEvent(const Event & event)
{
}