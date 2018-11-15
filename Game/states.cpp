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
#include "achievement.h"
#include "room.h"
#include <iostream>

void TitleState::Enter()
{
	//Adds action for enter key
	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("pause", SDL_SCANCODE_P, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("achieve", SDL_SCANCODE_Q, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("select_left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("select_right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);

	Entity* TitleText = m_owner->GetScene()->AddEntity<Entity>("title");
	TitleText->GetTransform().position = Vector2D(25.0f, 100.0f);
	TextComponent* TitleTextComponent = TitleText->AddComponent<TextComponent>();
	TitleTextComponent->Create("One Dungeon, One Dragon", "Textures\\emulogic.ttf", 32, Color::white);
	TitleTextComponent->SetDepth(120);

	Entity* title = m_owner->GetScene()->AddEntity<Entity>("TitleScreen");
	title->GetTransform().position = Vector2D(400.0f, 370.0f);
	SpriteComponent* spritecomponentTitle = title->AddComponent<SpriteComponent>();
	spritecomponentTitle->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* dragonAnimation = title->AddComponent<AnimationComponent>();
	std::vector<std::string> animations = { "Sprites\\sleepingdragonframe1.png","Sprites\\sleepingdragonframe2.png" ,"Sprites\\sleepingdragonframe3.png" ,"Sprites\\sleepingdragonframe4.png" ,"Sprites\\sleepingdragonframe5.png" };
	dragonAnimation->Create(animations, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);
	title->GetTransform().scale = Vector2D(5.0f, 5.0f);
	spritecomponentTitle->SetDepth(120);

	Entity* ItemPrompt = m_owner->GetScene()->AddEntity<Entity>("ItemPrompt");
	ItemPrompt->GetTransform().position = Vector2D(250.0f, 690.0f);
	TextComponent* ItemPromptComponent = ItemPrompt->AddComponent<TextComponent>();
	ItemPromptComponent->Create("Press Space To Pick Up Items", "Textures\\emulogic.ttf", 10, Color::white);
	ItemPromptComponent->SetDepth(120);

	Entity* UsePrompt = m_owner->GetScene()->AddEntity<Entity>("UsePrompt");
	UsePrompt->GetTransform().position = Vector2D(250.0f, 710.0f);
	TextComponent* UsePromptComponent = UsePrompt->AddComponent<TextComponent>();
	UsePromptComponent->Create("Press E to perform an action", "Textures\\emulogic.ttf", 10, Color::white);
	UsePromptComponent->SetDepth(120);

	Entity* AcheivePrompt = m_owner->GetScene()->AddEntity<Entity>("AcheivePrompt");
	AcheivePrompt->GetTransform().position = Vector2D(250.0f, 730.0f);
	TextComponent* AcheivePromptcomponent = AcheivePrompt->AddComponent<TextComponent>();
	AcheivePromptcomponent->Create("Press Q to see Acheivements", "Textures\\emulogic.ttf", 10, Color::white);
	AcheivePromptcomponent->SetDepth(120);

	Entity* returnText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	returnText->GetTransform().position = Vector2D(250.0f, 750.0f);
	TextComponent* returntextComponent = returnText->AddComponent<TextComponent>();
	returntextComponent->Create("Press Enter to start", "Textures\\emulogic.ttf", 10, Color::white);
	returntextComponent->SetDepth(120);

	//character select:
	Entity* CharacterHero = m_owner->GetScene()->AddEntity<Entity>("Charaheroselect");
	CharacterHero->GetTransform().position = Vector2D(400.0f, 620.0f);
	SpriteComponent* CharacterHerosprite = CharacterHero->AddComponent<SpriteComponent>();
	CharacterHerosprite->Create("", Vector2D(0.5f, 0.5f));
	CharacterHero->GetTransform().scale = Vector2D(5.0f, 5.0f);
	AnimationComponent* CharacterHerospriteanimationComponent = CharacterHero->AddComponent<AnimationComponent>();
	CharacterHerospriteanimationComponent->Create({ "sprites//knight_m_run_anim_f0.png","sprites//knight_m_run_anim_f1.png" ,"sprites//knight_m_run_anim_f2.png" ,"sprites//knight_m_run_anim_f3.png" }, 1.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

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

	Entity* entity5 = m_owner->GetScene()->GetEntitiesWithID("AcheivePrompt");
	if (entity5) {
		entity5->SetState(Entity::DESTROY);
	}
	Entity* entity6 = m_owner->GetScene()->GetEntitiesWithID("UsePrompt");
	if (entity6) {
		entity6->SetState(Entity::DESTROY);
	}
	Entity* entity7 = m_owner->GetScene()->GetEntitiesWithID("ReturnText");
	if (entity7) {
		entity7->SetState(Entity::DESTROY);
	}
	Entity* entity8 = m_owner->GetScene()->GetEntitiesWithID("ItemPrompt");
	if (entity8) {
		entity8->SetState(Entity::DESTROY);
	}
	Entity* entity9 = m_owner->GetScene()->GetEntitiesWithID("Charaheroselect");
	if (entity9) {
		entity9->SetState(Entity::DESTROY);
	}
}

void InitializeState::Enter()
{
	Room* mainroom = m_owner->GetScene()->AddEntity<Room>("mainroom");
	mainroom->SetRooms();

	//Sleeping Dragon
	Dragon* dragon = m_owner->GetScene()->AddEntity<Dragon>("dragon");
	dragon->Create(Vector2D(400.0f, 400.0f));
	dragon->GetComponent<SpriteComponent>()->SetDepth(2);

	//Inventory placeholder
	Entity* Inventory = m_owner->GetScene()->AddEntity<Entity>("InventoryLabel");
	Inventory->GetTransform().position = Vector2D(25.0f, 50.0f);
	TextComponent* inventoryLabel = Inventory->AddComponent<TextComponent>();
	inventoryLabel->Create("No Items", "Textures\\emulogic.ttf", 18, Color::white);
	inventoryLabel->SetDepth(120);
	Entity* InventoryIcon = m_owner->GetScene()->AddEntity<Entity>("InventoryIcon");
	InventoryIcon->GetTransform().position = Vector2D(50.0f, 40.0f);
	InventoryIcon->GetTransform().scale = Vector2D(4.0f,4.0f);
	SpriteComponent* inventoryicon = InventoryIcon->AddComponent<SpriteComponent>();
	inventoryicon->Create("Sprites\\chest_empty_open_anim_f2.png", Vector2D(0.5f,0.5f));
	inventoryicon->SetDepth(50);

	//set up game
	/*Item* sword = m_owner->GetScene()->AddEntity<Item>("sword");
	sword->Create(Item::eType::SWORD, Vector2D(200.0f, 200.0f));*/

	Item* nothing = m_owner->GetScene()->AddEntity<Item>("No Items");
	nothing->Create(Item::eType::NONE, Vector2D(0.0f, 0.0f));



	//doors
	/*
	Door* topRightDoor = m_owner->GetScene()->AddEntity<Door>("topRightDoor");
	topRightDoor->Create(Vector2D(800.0f, 280.0f), true);
	topRightDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	Door* bottomLeftDoor = m_owner->GetScene()->AddEntity<Door>("bottomLeftDoor");
	bottomLeftDoor->Create(Vector2D(5.0f, 520.0f), false);
	bottomLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	Door* bottomRightDoor = m_owner->GetScene()->AddEntity<Door>("bottomRightDoor");
	bottomRightDoor->Create(Vector2D(800.0f, 520.0f), true);
	bottomRightDoor->GetComponent<SpriteComponent>()->SetDepth(2);*/

	Hero* hero = m_owner->GetScene()->AddEntity<Hero>("hero");
	Item* emptyInventory = (Item*)m_owner->GetScene()->GetEntitiesWithID("No Items");
	hero->Create(Vector2D(400.0f, 600.0f));
	hero->SetItemHeld(emptyInventory);
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
	Entity* mainroom = m_owner->GetScene()->GetEntitiesWithID("mainroom");
	if ((eHero->GetTransform().position.x > 0 && eHero->GetTransform().position.x < 50) && (eHero->GetTransform().position.y > 220 && eHero->GetTransform().position.y < 300))
	{
		if (((Room*)mainroom)->m_currentRoom == ((Room*)mainroom)->m_rooms[0]) 
		{
			((Room*)mainroom)->ChangeRoom(1);
			eHero->GetTransform().position = Vector2D(750.0f, 680.0f);
		}
	}
	else if ((eHero->GetTransform().position.x > 750) && (eHero->GetTransform().position.y > 640 && eHero->GetTransform().position.y < 720))
	{
		if (((Room*)mainroom)->m_currentRoom != ((Room*)mainroom)->m_rooms[0])
		{
			((Room*)mainroom)->ChangeRoom();
			eHero->GetTransform().position = Vector2D(50.0f, 260.0f);
		}
	}

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
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD) ||
		(InputManager::Instance()->GetActionButton("pick up") == InputManager::eButtonState::HELD))
	{
		m_timerRate = m_timerReset;
	}
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("BoreDragonEnding");
	}
}


void GameState::Exit()
{
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(300.0f, 700.0f);
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
	m_timerRate = 3.0f;
	Entity* huggedText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	huggedText->GetTransform().position = Vector2D(0.0f, 100.0f);
	TextComponent* huggedtextComponent = huggedText->AddComponent<TextComponent>();
	huggedtextComponent->Create("You Have Bored The Dragon to Death. Maybe put down the Chips and Play", "Textures\\emulogic.ttf", 10, Color::white);
	huggedtextComponent->SetDepth(120);

	//achievement
	Achievement* dragonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* dragonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("BoreDragonAchievement");
	dragonAchivement->updateAchievement(dragonAchivementAchievement);
	Achievement* dragonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* dragonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("BoreDragonTextAchievement");
	dragonAchivementText->updateAchievement(dragonAchivementTextAchievement);
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
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
}

void HugDragonEnding::Enter()
{
		m_timerRate = 3.0f;
		Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("HugTextSent1");
		huggedText1->GetTransform().position = Vector2D(0.0f, 100.0f);
		TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
		huggedtextComponent1->Create("You Have Hugged the Dragon. It has been warmed", "Textures\\emulogic.ttf", 16, Color::white);
		huggedtextComponent1->SetDepth(120);

		Entity* huggedText2 = m_owner->GetScene()->AddEntity<Entity>("HugTextSent2");
		huggedText2->GetTransform().position = Vector2D(0.0f, 150.0f);
		TextComponent* huggedtextComponent2 = huggedText2->AddComponent<TextComponent>();
		huggedtextComponent2->Create("by Kindess and will do no more harm.", "Textures\\emulogic.ttf", 16, Color::white);
		huggedtextComponent2->SetDepth(120);
		//achievement
		Achievement* dragonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		Entity* dragonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("HugDragonAchievement");
		dragonAchivement->updateAchievement(dragonAchivementAchievement);
		Achievement* dragonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		Entity* dragonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("HugDragonTextAchievement");
		dragonAchivementText->updateAchievement(dragonAchivementTextAchievement);
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
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("HugTextSent1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("HugTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}

void KillDragonEnding::Enter()
{
	m_timerRate = 3.0f;
	Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("KillTextSent1");
	huggedText1->GetTransform().position = Vector2D(0.0f, 100.0f);
	TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
	huggedtextComponent1->Create("You Have Slain the Mighty Tempest Dragon.",  "Textures\\emulogic.ttf", 16, Color::white);
	huggedtextComponent1->SetDepth(120);

		//achievement
		Achievement* dragonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		Entity* dragonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("KillDragonAchievement");
		dragonAchivement->updateAchievement(dragonAchivementAchievement);
		Achievement* dragonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
		Entity* dragonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("KillDragonTextAchievement");
		dragonAchivementText->updateAchievement(dragonAchivementTextAchievement);
}

void KillDragonEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (InputManager::Instance()->GetActionButton("respect") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("RespectEnding");
	}
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
}

void KillDragonEnding::Exit()
{
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("KillTextSent1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("KillTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}

void RespectEnding::Enter()
{
	m_timerRate = 3.0f;
	Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("RespectTextSent1");
	huggedText1->GetTransform().position = Vector2D(0.0f, 100.0f);
	TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
	huggedtextComponent1->Create("You Pay Respect to the Mighty Tempest Dragon.", "Textures\\emulogic.ttf", 16, Color::white);
	huggedtextComponent1->SetDepth(120);

	Entity* huggedText2 = m_owner->GetScene()->AddEntity<Entity>("RespectTextSent2");
	huggedText2->GetTransform().position = Vector2D(0.0f, 150.0f);
	TextComponent* huggedtextComponent2 = huggedText2->AddComponent<TextComponent>();
	huggedtextComponent2->Create("You've Earned a Bonus Achievement.", "Textures\\emulogic.ttf", 16, Color::white);
	huggedtextComponent2->SetDepth(120);

	Achievement* dragonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* dragonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("RespectDragonAchievement");
	dragonAchivement->updateAchievement(dragonAchivementAchievement);
	Achievement* dragonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* dragonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("RespectDragonTextAchievement");
	dragonAchivementText->updateAchievement(dragonAchivementTextAchievement);
}

void RespectEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
}

void RespectEnding::Exit()
{
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("RespectTextSent1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("RespectTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}
