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

	if (!(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("pick up") == InputManager::eButtonState::HELD))
	{
		m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
		if (m_timerRate <= 0.0f)
		{
			std::cout << "idle" << std::endl;
			m_idled = true;
		}
	}
	else
	{
		m_timerRate = m_timerReset;
	}
	



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
		this->GetComponent<AnimationComponent>()->Create(m_runanimation, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP, m_isFlipped);
	}

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 48.0f, size.x-48.0f);
	m_transform.position.y = Math::Clamp(m_transform.position.y, 32.0f, size.y-86.0f);

	//changes label for inventory
	Entity* Inventory = m_scene->GetEntitiesWithID("InventoryLabel");
	if (m_itemHeld != "") {
		Inventory->GetComponent<TextComponent>()->SetText(m_itemHeld.GetIDString());
	}
	else {
		Inventory->GetComponent<TextComponent>()->SetText("No Items");
	}

	if (InputManager::Instance()->GetActionButton("pick_up") == InputManager::eButtonState::PRESSED && m_itemHeld.GetIDString() != "No Items") {
	//	if (m_itemHeld.GetIDString() == "sword") {
	//	Item* itemdroped = m_scene->AddEntity<Item>();
	//	itemdroped->Create(Item::eType::SWORD, m_transform.position);
//}
	}
}

void Hero::OnEvent(const Event & event)
{
	if (event.eventID == "collision") {
		if (event.sender->GetTag() == "dragon" && event.sender->GetTag() != "item")
		{
			if (InputManager::Instance()->GetActionButton("pick_up") == InputManager::eButtonState::PRESSED && m_itemHeld == "")
			{					
				m_hugged = true;
			}
		}
		else if (event.sender->GetTag() == "item") {
			//drops item being held
			
		}
	}
}
