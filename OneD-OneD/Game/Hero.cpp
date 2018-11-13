#include "hero.h"
#include "transform.h"
#include "HeroControllerComponent.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "explosion.h"
#include "eventManager.h"
#include "animationComponent.h"
#include "inputManager.h"
#include <iostream>
#include "textComponent.h"
#include "item.h"
void Hero::Create(const Vector2D & position)
{
	SetTag("hero");
	m_transform.position = position;
	m_transform.scale = Vector2D(5.0f, 5.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(800.0f, 0.3f, false);
	kinematic->Create(500.0f, 0.3f, false);

	HeroControllerComponent* heroControllerComponent = AddComponent<HeroControllerComponent>();
	heroControllerComponent->Create(0.5f);

	SpriteComponent* spritecomponent01 = AddComponent<SpriteComponent>();
	spritecomponent01->Create("", Vector2D(0.5f, 0.5f));
	spritecomponent01->SetDepth(100);

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	animationComponent->Create(m_idleanimation, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(1.0f, 1.0f));
}

void Hero::Update()
{
	Entity::Update();

	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)) {
		m_isFlipped = true;
	}
	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)) {
		m_isFlipped = false;
	}

	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)|| 
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		this->GetComponent<AnimationComponent>()->Create(m_runanimation, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP, m_isFlipped);
	} else {
		this->GetComponent<AnimationComponent>()->Create(m_idleanimation, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP, m_isFlipped);
	}

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 48.0f, size.x-48.0f);
	m_transform.position.y = Math::Clamp(m_transform.position.y, 32.0f, size.y-86.0f);


	if (InputManager::Instance()->GetActionButton("pick_up") == InputManager::eButtonState::PRESSED && ((ID)m_itemHeld->GetTag()).GetIDString() == "sword") {
		m_itemHeld->GetTransform().position = m_transform.position;
		m_itemHeld = (Item*)m_scene->GetEntitiesWithID("No Items");
	}

	//changes label for inventory
	Entity* Inventory = m_scene->GetEntitiesWithID("InventoryLabel");
	Inventory->GetComponent<TextComponent>()->SetText(((ID)m_itemHeld->GetTag()).GetIDString());

}

void Hero::OnEvent(const Event & event)
{
}
