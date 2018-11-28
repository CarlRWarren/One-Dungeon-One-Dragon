#include "Item.h"
#include "transform.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "hero.h"
#include "inputManager.h"

void Item::Create(Item::eType type, const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.5f, 2.5f);
	SetTag("item");

	if (type == SWORD) {
		m_itemType = "sword";
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("sprites\\weapon_regular_sword.png", Vector2D(0.5f, 0.5f));
		spriteComponent->SetDepth(55);
	}
	else if (type == POISON) {
		m_itemType = ("poison");
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("sprites\\flask_big_green.png", Vector2D(0.5f, 0.5f));
		spriteComponent->SetDepth(55);
	}
	else if (type == FOOD) {
		m_itemType = ("food");
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("sprites\\steak.png", Vector2D(0.5f, 0.5f));
		spriteComponent->SetDepth(55);
	}
	else {
		m_itemType = ("No Items");
	}
	
	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(1.0f,1.0f));
}

void Item::Update()
{
	Entity::Update();
}


void Item::OnEvent(const Event & event)
{
	if (GetComponent<SpriteComponent>()->GetVisible() == true) {
		if (event.eventID == "collision") {
			if (event.sender->GetTag() == "hero") {
				if (InputManager::Instance()->GetActionButton("pick_up") == InputManager::eButtonState::PRESSED) {
					Entity* hero = m_scene->GetEntitiesWithID("hero");
					Hero* ehero = (Hero*)hero;
					ID* id = new ID(m_id.GetIDString());
					ehero->SetItemHeld(this);
					m_transform.position = Vector2D(50.0f, 25.0f);
				}
			}
		}
	}
}

