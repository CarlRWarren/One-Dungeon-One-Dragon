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
#include "achievement.h"
#include <iostream>

void TitleState::Enter()
{
	//Adds action for enter key
	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("pause", SDL_SCANCODE_P, InputManager::eDevice::KEYBOARD);
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
	Achievement* createAchievement = m_owner->GetScene()->AddEntity<Achievement>("achievement");
	createAchievement->Create(Vector2D(400.0f, 400.0f));

}

void TitleState::Update()
{
	//if pressed moves to next state
	if (InputManager::Instance()->GetActionButton("start")==InputManager::eButtonState::PRESSED) {
		m_owner->SetState("intitialize");
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

void InitializeState::Enter()
{
	//Background
	Entity* Background = m_owner->GetScene()->AddEntity<Entity>("background");
	Background->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* backgroundSpriteComponent = Background->AddComponent<SpriteComponent>();
//	backgroundSpriteComponent->Create("Sprites\\MainRoomDesign.png", Vector2D(0.5f, 0.5f));
	Background->GetTransform().scale = Vector2D(5.0f, 5.0f);
	backgroundSpriteComponent->SetDepth(1);

	//Sleeping Dragon
	Dragon* dragon = m_owner->GetScene()->AddEntity<Dragon>("dragon");
	dragon->Create(Vector2D(400.0f, 400.0f));
	dragon->GetComponent<SpriteComponent>()->SetDepth(2);

	//Inventory placeholder
	Entity* Inventory = m_owner->GetScene()->AddEntity<Entity>("InventoryLabel");
	Inventory->GetTransform().position = Vector2D(650.0f, 25.0f);
	TextComponent* inventoryLabel = Inventory->AddComponent<TextComponent>();
	inventoryLabel->Create("No Items", "Textures\\emulogic.ttf", 18, Color::white);
	inventoryLabel->SetDepth(120);

	//set up game
	Item* sword = m_owner->GetScene()->AddEntity<Item>("sword");
	sword->Create(Item::eType::SWORD, Vector2D(200.0f, 200.0f));

	Item* nothing = m_owner->GetScene()->AddEntity<Item>("No Items");
	nothing->Create(Item::eType::NONE, Vector2D(0.0f, 0.0f));



	//doors
	Door* topLeftDoor = m_owner->GetScene()->AddEntity<Door>("topLeftDoor");
	topLeftDoor->Create(Vector2D(5.0f,280.0f), false);
	topLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	Door* topRightDoor = m_owner->GetScene()->AddEntity<Door>("topRightDoor");
	topRightDoor->Create(Vector2D(800.0f, 280.0f), true);
	topRightDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	Door* bottomLeftDoor = m_owner->GetScene()->AddEntity<Door>("bottomLeftDoor");
	bottomLeftDoor->Create(Vector2D(5.0f, 520.0f), false);
	bottomLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	Door* bottomRightDoor = m_owner->GetScene()->AddEntity<Door>("bottomRightDoor");
	bottomRightDoor->Create(Vector2D(800.0f, 520.0f), true);
	bottomRightDoor->GetComponent<SpriteComponent>()->SetDepth(2);
}

void InitializeState::Update()
{
	m_owner->SetState("game");
}

void InitializeState::Exit()
{
}

void GameState::Enter()
{
	//anything that needs to be reset every time they win, place here
	Hero* hero = m_owner->GetScene()->AddEntity<Hero>("hero");
	float x = 400.0f;
	float y = 700.0f;
	hero->Create(Vector2D(x, y));

	Item* emptyInventory = (Item*)m_owner->GetScene()->GetEntitiesWithID("No Items");
	hero->SetItemHeld(emptyInventory);
}

void GameState::Update()
{
	if (InputManager::Instance()->GetActionButton("pause") == InputManager::eButtonState::PRESSED)
	{
		(Timer::Instance()->IsPaused()) ? Timer::Instance()->UnPause() : Timer::Instance()->Pause();
	}
	//Checks for Q for achievemnt Screen
	if (InputManager::Instance()->GetActionButton("achieve") == InputManager::eButtonState::PRESSED) {
		Achievement* showAchievements = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		showAchievements->setVisibility(!showAchievements->GetComponent<SpriteComponent>()->GetVisible());
	}

	//hugged dragon
	Entity* eHero = m_owner->GetScene()->GetEntitiesWithID("hero");
	Entity* eDragon = m_owner->GetScene()->GetEntitiesWithID("dragon");

	//if statement for checks that involve any "pick up" action
	if (InputManager::Instance()->GetActionButton("use") == InputManager::eButtonState::PRESSED) 
	{
		//checks intersect
		if (eHero->GetComponent<AABBComponent>()->Intersects(eDragon->GetComponent<AABBComponent>())) 
		{
			ID id = ((Hero*)eHero)->GetItemHeld()->GetTag();
			if (id.GetIDString() == "No Items") { m_owner->SetState("HugDragonEnding"); }
			if (id.GetIDString() == "sword") { m_owner->SetState("KillDragonEnding"); }
		}
	}

	//bore dragon
	if (!(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD) &&
		!(InputManager::Instance()->GetActionButton("pick up") == InputManager::eButtonState::HELD))
	{
		m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
		if (m_timerRate <= 0.0f)
		{
			m_owner->SetState("BoreDragonEnding");
		}
	}
	else
	{
		m_timerRate = m_timerReset;
	}
}

void GameState::Exit()
{
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->SetState(Entity::DESTROY);
	}
}

void GameOverState::Enter()
{
	//print out score?
}

void GameOverState::Update()
{

}

void GameOverState::Exit()
{

}



void BoreDragonEnding::Enter()
{
	Entity* huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	huggedText->GetTransform().position = Vector2D(0.0f, 100.0f);
	TextComponent* huggedtextComponent = huggedText->AddComponent<TextComponent>();
	huggedtextComponent->Create("You Have Bored The Dragon to Death. Maybe put down the Chips and Play", "Textures\\emulogic.ttf", 10, Color::white);
	huggedtextComponent->SetDepth(120);

	//achievement
	Achievement* boreDragon = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* boreDragonAchievement = m_owner->GetScene()->GetEntitiesWithID("BoreDragonAchievement");
	boreDragon->updateAchievement(boreDragonAchievement);
}

void BoreDragonEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
}

void BoreDragonEnding::Exit()
{
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("ReturnText");
	huggedText->SetState(Entity::eState::DESTROY);

}

void HugDragonEnding::Enter()
{
	{
		Entity* huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
		huggedText->GetTransform().position = Vector2D(0.0f, 100.0f);
		TextComponent* huggedtextComponent = huggedText->AddComponent<TextComponent>();
		huggedtextComponent->Create("You Have Hugged the Dragon. It has been warmed by Kindess and will do no more harm.", "Textures\\emulogic.ttf", 8, Color::white);
		huggedtextComponent->SetDepth(120);

		//achievement
		Achievement* hugDragon = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		Entity* hugDragonAchievement = m_owner->GetScene()->GetEntitiesWithID("HugDragonAchievement");
		hugDragon->updateAchievement(hugDragonAchievement);
	}
}

void HugDragonEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
}

void HugDragonEnding::Exit()
{
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("ReturnText");
	huggedText->SetState(Entity::eState::DESTROY);
}

void KillDragonEnding::Enter()
{


		//achievement
		Achievement* killDragon = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		Entity* killDragonAchievement = m_owner->GetScene()->GetEntitiesWithID("KillDragonAchievement");
		killDragon->updateAchievement(killDragonAchievement);
}

void KillDragonEnding::Update()
{

}

void KillDragonEnding::Exit()
{

}
