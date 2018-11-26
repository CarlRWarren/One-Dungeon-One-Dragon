#include "Fountain.h"
#include "transform.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "eventManager.h"
#include "animationComponent.h"
#include <iostream>

void Fountain::Create(const Vector2D & position,int version)
{
	SetTag("fountain");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* fountainSpritecomponent = AddComponent<SpriteComponent>();
	fountainSpritecomponent->Create("", Vector2D(0.5f, 0.5f));

	AnimationComponent* fountainAnimation = AddComponent<AnimationComponent>();
	std::vector<std::string> animations;
	if (version == 1) animations = { "Sprites\\LavaFountainFrame1.png","Sprites\\LavaFountainFrame2.png" ,"Sprites\\LavaFountainFrame3.png" };
	if (version == 2) animations = { "Sprites\\WaterFountainFrame1.png","Sprites\\WaterFountainFrame2.png" ,"Sprites\\WaterFountainFrame3.png" };
	fountainAnimation->Create(animations, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

	m_transform.scale = Vector2D(5.0f, 5.0f);
	fountainSpritecomponent->SetDepth(2);
}

void Fountain::Update()
{
	Entity::Update();
}
void Fountain::OnEvent(const Event & event)
{
}