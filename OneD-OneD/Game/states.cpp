#include "states.h"
#include "entity.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "aabbComponent.h"
#include "scene.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"
#include "formation.h"
#include "timer.h"
#include "textComponent.h"
#include "hero.h"
#include "dragon.h"
#include "item.h"
#include "door.h"
#include <iostream>

void TitleState::Enter()
{
	//Adds action for enter key
	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("achieve", SDL_SCANCODE_Q, InputManager::eDevice::KEYBOARD);

	Entity* title = m_owner->GetScene()->AddEntity<Entity>("TitleScreen");
	title->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* spritecomponentTitle = title->AddComponent<SpriteComponent>();
	spritecomponentTitle->Create("Textures\\TitleScreen.png", Vector2D(0.5f, 0.5f));
	title->GetTransform().scale = Vector2D(1.0f, 1.0f);
	spritecomponentTitle->SetDepth(120);
	Entity* returnText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	returnText->GetTransform().position = Vector2D(200.0f, 700.0f);
	TextComponent* returntextComponent = returnText->AddComponent<TextComponent>();
	returntextComponent->Create("Press Enter to start", "Textures\\emulogic.ttf", 18, Color::white);
	returntextComponent->SetDepth(120);

	//Achievement Background
	Entity* achievementBackground = m_owner->GetScene()->AddEntity<Entity>("achieve");
	achievementBackground->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* achievementBackgroundSpriteComponent = achievementBackground->AddComponent<SpriteComponent>();
	achievementBackgroundSpriteComponent->Create("Sprites\\AchievementBackground.png", Vector2D(0.5f, 0.5f));
	achievementBackground->GetTransform().scale = Vector2D(1.0f, 1.0f);
	achievementBackgroundSpriteComponent->SetDepth(200);
	achievementBackgroundSpriteComponent->SetVisible(false);

}

void TitleState::Update()
{
	//if pressed moves to next state
	if (InputManager::Instance()->GetActionButton("start")==InputManager::eButtonState::PRESSED) {
		m_owner->SetState("game");
	}
}

void TitleState::Exit()
{
	//destroy entities made in title here
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("title");
	if (entity1) {
		entity1->SetState(Entity::DESTROY);
	}
	Entity* entity2 = m_owner->GetScene()->GetEntitiesWithID("ReturnText");
	if (entity2) {
		entity2->SetState(Entity::DESTROY);
	}
	Entity* entity3 = m_owner->GetScene()->GetEntitiesWithID("TitleScreen");
	if (entity3) {
		entity3->SetState(Entity::DESTROY);
	}
}

void GameState::Enter()
{
	//Background
	Entity* Background = m_owner->GetScene()->AddEntity<Entity>("background");
	Background->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* backgroundSpriteComponent = Background->AddComponent<SpriteComponent>();
	backgroundSpriteComponent->Create("Sprites\\MainRoomDesign.png", Vector2D(0.5f, 0.5f));
	Background->GetTransform().scale = Vector2D(5.0f, 5.0f);
	backgroundSpriteComponent->SetDepth(1);
	
	Hero* hero = m_owner->GetScene()->AddEntity<Hero>("hero");
	float x = 400.0f;
	float y = 700.0f;
	hero->Create(Vector2D(x, y));

	//Sleeping Dragon
	Dragon* dragon = m_owner->GetScene()->AddEntity<Dragon>("dragon");
	dragon->Create(Vector2D(400.0f, 400.0f));
	dragon->GetComponent<SpriteComponent>()->SetDepth(2);
	
	//Inventory placeholder
	Entity* Inventory = m_owner->GetScene()->AddEntity<Entity>("InventoryLabel");
	TextComponent* inventoryLabel = Inventory->AddComponent<TextComponent>();
	inventoryLabel->Create("No Items", "Textures\\emulogic.ttf", 18, Color::white);
	inventoryLabel->SetDepth(120);

	//set up game
	Item* sword = m_owner->GetScene()->AddEntity<Item>("sword");
	sword->Create(Item::eType::SWORD,Vector2D(200.0f, 200.0f));

	//door
	Door* topLeftDoor = m_owner->GetScene()->AddEntity<Door>("topLeftDoor");
	topLeftDoor->Create(Vector2D(5.0f,280.0f));
	topLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
}
void GameState::Update()
{
	
	//Checks for Q for achievemnt Screen
	if (InputManager::Instance()->GetActionButton("achieve") == InputManager::eButtonState::PRESSED) {
		Entity* achievementBackground = m_owner->GetScene()->GetEntitiesWithID("achieve");
		SpriteComponent* achievementBackgroundSpriteComponent = achievementBackground->GetComponent<SpriteComponent>();
		achievementBackgroundSpriteComponent->SetVisible(!achievementBackgroundSpriteComponent->GetVisible());
	}

	Entity* eHero = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (eHero != nullptr)
	{
		Hero* hero = (Hero*)eHero;
		if (hero->GetHugged())
		{
			std::cout << "hugged" << std::endl;
			m_owner->SetState("game_over");
		}
		else if (hero->GetIdle())
		{
			std::cout << "Idle" << std::endl;
			m_owner->SetState("game_over");
		}

	}//stays in here while game is playing
}

void GameState::Exit()
{
	
	//destroy entities in game state here
}

void GameOverState::Enter()
{
		Entity* eHero = m_owner->GetScene()->GetEntitiesWithID("hero");
		Hero* hero = (Hero*)eHero;
		std::cout << "entered Game Over" << std::endl;
		if (eHero != nullptr)
		{
			
			if (hero->GetHugged())
			{
				Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
				if (entity1) {
					entity1->SetState(Entity::DESTROY);
				}
				Entity* huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
				huggedText->GetTransform().position = Vector2D(0.0f, 300.0f);
				TextComponent* huggedtextComponent = huggedText->AddComponent<TextComponent>();
				huggedtextComponent->Create("You Have Hugged the Dragon. It has been", "Textures\\emulogic.ttf", 18, Color::white);
				huggedtextComponent->SetDepth(120);

				huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
				huggedText->GetTransform().position = Vector2D(0.0f, 350.0f);
				huggedtextComponent = huggedText->AddComponent<TextComponent>();
				huggedtextComponent->Create("warmed by Kindess and will do no more harm.", "Textures\\emulogic.ttf", 18, Color::white);
				huggedtextComponent->SetDepth(120);
			}
			if (hero->GetIdle())
			{
				std::cout << "entered idle" << std::endl;
				Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
				if (entity1) {
					entity1->SetState(Entity::DESTROY);
				}

				Entity* huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
				huggedText->GetTransform().position = Vector2D(0.0f, 300.0f);
				TextComponent* huggedtextComponent = huggedText->AddComponent<TextComponent>();
				huggedtextComponent->Create("You Have Bored The Dragon to Death. Maybe", "Textures\\emulogic.ttf", 18, Color::white);
				huggedtextComponent->SetDepth(120);

				huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
				huggedText->GetTransform().position = Vector2D(0.0f, 350.0f);
				huggedtextComponent = huggedText->AddComponent<TextComponent>();
				huggedtextComponent->Create("Put down the Chips and Play", "Textures\\emulogic.ttf", 18, Color::white);
				huggedtextComponent->SetDepth(120);
			}
		}
	}
	
	// Create entities for game over screen
	// add action or timer

void GameOverState::Update()
{
	//moves on if they press action or timer runs out
}

void GameOverState::Exit()
{
	//destroy gameover entities here
}
