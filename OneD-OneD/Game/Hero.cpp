#include "hero.h"
#include "transform.h"
#include "HeroControllerComponent.h"
#include "spriteComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
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
	heroControllerComponent->Create(1.5f);

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
	bool pause = Timer::Instance()->IsPaused();
	Entity::Update();

	if (((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)) && pause == false) {
		m_isFlipped = true;
	}
	if (((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)) && pause == false) {
		m_isFlipped = false;
	}

	if (((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)|| 
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)) && pause == false)
	{
		this->GetComponent<AnimationComponent>()->Create(m_whichRun, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP, m_isFlipped);
	} else {
		this->GetComponent<AnimationComponent>()->Create(m_whichIdle, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP, m_isFlipped);
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

void Hero::GetRunAnimation(int herowizzard)
{
		if (herowizzard == 1) {
				m_whichRun = m_runanimation;
		}
		else if (herowizzard == 2) {
				m_whichRun = m_runanimationwizard;
		}
}

void Hero::GetIdleAnimation(int herowizzard)
{
		if (herowizzard == 1) {
				m_whichIdle = m_idleanimation;
		}
		else if (herowizzard == 2) {
				m_whichIdle = m_idleanimationwizard;
		}
}
