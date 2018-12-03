#include "states.h"
#include "entity.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "aabbComponent.h"
#include "scene.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "timer.h"
#include "textComponent.h"
#include "hero.h"
#include "dragon.h"
#include "item.h"
#include "door.h"
#include "achievement.h"
#include "audioSystem.h"
#include "room.h"
#include "pauseScreen.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void TitleState::Enter()
{
	AudioSystem::Instance()->AddSound("intro", "Sound\\introbeat.mp3");

	//Adds action for enter key
	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("pause", SDL_SCANCODE_P, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("achieve", SDL_SCANCODE_Q, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("hint", SDL_SCANCODE_H, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("select_left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("select_right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	
	InputManager::Instance()->AddAction("delete", SDL_SCANCODE_DELETE, InputManager::eDevice::KEYBOARD);

	Entity* TitleText = m_owner->GetScene()->AddEntity<Entity>("title");
	TitleText->GetTransform().position = Vector2D(25.0f, 100.0f);
	TextComponent* TitleTextComponent = TitleText->AddComponent<TextComponent>();
	TitleTextComponent->Create("One Dungeon, One Dragon", "Textures\\emulogic.ttf", 32, Color::white);
	TitleTextComponent->SetDepth(120);

	//banner
	Entity* titlebanner = m_owner->GetScene()->AddEntity<Entity>("TitleBanner");
	titlebanner->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* spritecomponentTitlebanner = titlebanner->AddComponent<SpriteComponent>();
	spritecomponentTitlebanner->Create("Sprites\\TitleBanner.png", Vector2D(0.5f, 0.5f));
	spritecomponentTitlebanner->SetDepth(100);
	titlebanner->GetTransform().scale = Vector2D(1.1f, 1.1f);
	spritecomponentTitlebanner->SetVisible(false);

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

	//Achievement Background
	Achievement* createAchievement = m_owner->GetScene()->AddEntity<Achievement>("achievement");
	createAchievement->Create(Vector2D(400.0f, 400.0f));

	//pause screen
	PauseScreen* pauseScreen = m_owner->GetScene()->AddEntity<PauseScreen>("pauseScreen");
	pauseScreen->Create(Vector2D(400.0f, 400.0f));

	//pausePropmt
	Entity* PauseScreen = m_owner->GetScene()->AddEntity<Entity>("PauseScreenPrompt");
	PauseScreen->GetTransform().position = Vector2D(625.0f, 25.0f);
	TextComponent* PauseScreenlabel = PauseScreen->AddComponent<TextComponent>();
	PauseScreenlabel->Create("Press 'P' To Pause", "Textures\\emulogic.ttf", 8, Color::white);
	PauseScreenlabel->SetDepth(120);
	PauseScreenlabel->SetVisible(false);

	//Inventory placeholder
	Entity* Inventory = m_owner->GetScene()->AddEntity<Entity>("InventoryLabel");
	Inventory->GetTransform().position = Vector2D(25.0f, 50.0f);
	TextComponent* inventoryLabel = Inventory->AddComponent<TextComponent>();
	inventoryLabel->Create("No Items", "Textures\\emulogic.ttf", 18, Color::white);
	inventoryLabel->SetDepth(120);
	inventoryLabel->SetVisible(false);
	Entity* InventoryIcon = m_owner->GetScene()->AddEntity<Entity>("InventoryIcon");
	InventoryIcon->GetTransform().position = Vector2D(50.0f, 40.0f);
	InventoryIcon->GetTransform().scale = Vector2D(4.0f, 4.0f);
	SpriteComponent* inventoryicon = InventoryIcon->AddComponent<SpriteComponent>();
	inventoryicon->Create("Sprites\\chest_empty_open_anim_f2.png", Vector2D(0.5f, 0.5f));
	inventoryicon->SetDepth(50);
	inventoryicon->SetVisible(false);

	//SwordItem
	Item* sword = m_owner->GetScene()->AddEntity<Item>();
	sword->Create(Item::eType::SWORD, Vector2D(200.0f, 200.0f));
	sword->GetComponent<SpriteComponent>()->SetVisible(false);

	//PosionItem
	Item* poison = m_owner->GetScene()->AddEntity<Item>();
	poison->Create(Item::eType::POISON, Vector2D(200.0f, 200.0f));
	poison->GetComponent<SpriteComponent>()->SetVisible(false);

	//food Item
	Item* food = m_owner->GetScene()->AddEntity<Item>();
	food->Create(Item::eType::FOOD, Vector2D(200.0f, 200.0f));
	food->GetComponent<SpriteComponent>()->SetVisible(false);

	Item* coin = m_owner->GetScene()->AddEntity<Item>();
	coin->Create(Item::eType::COIN, Vector2D(700.0f, 700.0f));
	coin->GetComponent<SpriteComponent>()->SetVisible(false);

	//Nothing Item
	Item* nothing = m_owner->GetScene()->AddEntity<Item>();
	nothing->Create(Item::eType::NONE, Vector2D(0.0f, 0.0f));

	//Hero
	Hero* hero = m_owner->GetScene()->AddEntity<Hero>("hero");
	hero->Create(Vector2D(400.0f, 600.0f));
	std::vector<Entity*> items = m_owner->GetScene()->GetEntitiesWithTag("item");
	for (Entity* entity : items) {
		Item* emptyInventory = (Item*)entity;
		if (emptyInventory->GetItemType() == "No Items") {
			hero->SetItemHeld(emptyInventory);
		}
	}

	//achievement count
	Entity* NUMAcheivementsCompleted = m_owner->GetScene()->AddEntity<Entity>("NUMAcheivementsCompleted");
	NUMAcheivementsCompleted->GetTransform().position = (Vector2D(600.0f, 75.0f));
	TextComponent* textcomponentNUMAcheivementsCompleted = NUMAcheivementsCompleted->AddComponent<TextComponent>();
	int numacheivements2 = createAchievement->GetNumAchievments()/2;
	int numacheivements1 = createAchievement->GetNumAchievmentsCompleted()/2;
	std::string numacheivements = std::to_string(numacheivements1) + "/" + std::to_string(numacheivements2) + " Achievements";
	textcomponentNUMAcheivementsCompleted->Create(numacheivements, "Textures\\emulogic.ttf", 8, Color::white);
	textcomponentNUMAcheivementsCompleted->SetDepth(300);

	AudioSystem::Instance()->PlaySound("intro", true);

}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("select_left")==InputManager::eButtonState::PRESSED) {
			Hero* hero = (Hero*)m_owner->GetScene()->GetEntitiesWithID("hero");
			hero->GetRunAnimation(1);
			hero->GetIdleAnimation(1);
	}
	else if (InputManager::Instance()->GetActionButton("select_right") == InputManager::eButtonState::PRESSED) {
			Hero* hero = (Hero*)m_owner->GetScene()->GetEntitiesWithID("hero");
			hero->GetRunAnimation(2);
			hero->GetIdleAnimation(2);

			Achievement* dragonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
			Entity* dragonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("WizardSecretAchievement");
			dragonAchivement->updateAchievement(dragonAchivementAchievement);
			Achievement* dragonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
			Entity* dragonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("WizardSecretTextAchievement");
			dragonAchivementText->updateAchievement(dragonAchivementTextAchievement);
			
			Entity* NUMAcheivementsCompleted = m_owner->GetScene()->GetEntitiesWithID("NUMAcheivementsCompleted");
			TextComponent* textcomponentNUMAcheivementsCompleted = NUMAcheivementsCompleted->GetComponent<TextComponent>();
			int numacheivements2 = dragonAchivement->GetNumAchievments()/2;
			int numacheivements1 = dragonAchivement->GetNumAchievmentsCompleted()/2;
			std::string numacheivements = std::to_string(numacheivements1) + "/" + std::to_string(numacheivements2) + " Achievements";
			textcomponentNUMAcheivementsCompleted->SetText(numacheivements);
	}


 	//if pressed moves to next state
	if (InputManager::Instance()->GetActionButton("start")==InputManager::eButtonState::PRESSED) {
		m_owner->SetState("intitialize");
	}
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
			entity1->GetTransform().position = Vector2D(400.0f, 600.0f);
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
	AudioSystem::Instance()->RemoveSound("intro");
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
	Entity* Inventory = m_owner->GetScene()->GetEntitiesWithID("InventoryLabel");
	TextComponent* inventoryLabel = Inventory->GetComponent<TextComponent>();
	inventoryLabel->SetVisible(true);
	Entity* InventoryIcon = m_owner->GetScene()->GetEntitiesWithID("InventoryIcon");
	SpriteComponent* inventoryicon = InventoryIcon->GetComponent<SpriteComponent>();
	inventoryicon->SetVisible(true);

	//show pause prompt
	Entity* pauseprompt = m_owner->GetScene()->GetEntitiesWithID("PauseScreenPrompt");
	TextComponent* pausepromptlabel = pauseprompt->GetComponent<TextComponent>();
	pausepromptlabel->SetVisible(true);

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
	Entity* room2LavaFountainL = m_owner->GetScene()->GetEntitiesWithID("leftLavaFountain");
	Entity* room2LavaFountainR = m_owner->GetScene()->GetEntitiesWithID("rightLavaFountain");
	room2LavaFountainL->GetComponent<SpriteComponent>()->SetVisible(false);
	room2LavaFountainR->GetComponent<SpriteComponent>()->SetVisible(false);
	AudioSystem::Instance()->AddSound("background", "Sound\\prayerofsoul.mp3");
	AudioSystem::Instance()->PlaySound("background", true);

	Entity* mainroom = m_owner->GetScene()->GetEntitiesWithID("mainroom");
	((Room*)mainroom)->ChangeRoom(0);
	Entity* eDragon = m_owner->GetScene()->GetEntitiesWithID("dragon");
	eDragon->GetComponent<SpriteComponent>()->SetVisible();
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(300.0f, 700.0f);
	}

	for (Room::Roomx* room : ((Room*)mainroom)->m_rooms)
	{
		for (Item* item : room->itemsInRoom)
		{
			if (item->GetItemType() == "food")
			{
				foodCount++;
			}
		}
	}
	Entity* titlebanner = m_owner->GetScene()->GetEntitiesWithID("TitleBanner");
	SpriteComponent* spritecomponentTitlebanner = titlebanner->GetComponent<SpriteComponent>();
	spritecomponentTitlebanner->SetVisible(false);
}

void GameState::Update()
{
	PauseScreen* showPause = (PauseScreen*)m_owner->GetScene()->GetEntitiesWithID("pauseScreen");
	float dt = Timer::Instance()->DeltaTime();

	if (InputManager::Instance()->GetActionButton("pause") == InputManager::eButtonState::PRESSED)
	{
		(Timer::Instance()->IsPaused()) ? Timer::Instance()->UnPause() : Timer::Instance()->Pause();
		showPause->setVisibility(!showPause->GetComponent<SpriteComponent>()->GetVisible());

	}
if (m_hintTimerRate > 0.0f) 
	{
		m_hintTimerRate = m_hintTimerRate - dt;
	}

	if (m_hintTimerRate > 0.0f) 
	{
		m_hintTimerRate = m_hintTimerRate - dt;
	}
	srand(time(NULL));
	if (InputManager::Instance()->GetActionButton("hint") == InputManager::eButtonState::PRESSED && m_hintTimerRate <= 0.0f)
	{
		int random = rand() % m_hints.size();
		m_hintActive = true;

		Entity* hintText = m_owner->GetScene()->AddEntity<Entity>("hintText");
		hintText->GetTransform().position = Vector2D(130.0f, 350.0f);
		TextComponent* hintTextComponent = hintText->AddComponent<TextComponent>();
		hintTextComponent->Create(m_hints[random], "Textures\\emulogic.ttf", 16, Color::white);
		hintTextComponent->SetDepth(120);

	}
	if (m_hintActive)
	{
		m_hintVisibilityTimerRate = m_hintVisibilityTimerRate - dt;
		if (m_hintVisibilityTimerRate <= 0.0f)
		{
			m_hintVisibilityTimerRate = m_hintVisibilityTimerReset;
			m_hintTimerRate = m_hintTimerReset;
			m_hintActive = false;
			Entity* eHint = m_owner->GetScene()->GetEntitiesWithID("hintText");
			if (eHint) {
				eHint->SetState(Entity::eState::DESTROY);
			}
		}
	}	//Checks for Q for achievemnt Screen

	Achievement* showAchievements = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* NUMAcheivementsCompleted = m_owner->GetScene()->GetEntitiesWithID("NUMAcheivementsCompleted");
	TextComponent* textcomponentNUMAcheivementsCompleted = NUMAcheivementsCompleted->GetComponent<TextComponent>();
	if (InputManager::Instance()->GetActionButton("achieve") == InputManager::eButtonState::PRESSED) {
		showAchievements->setVisibility(!showAchievements->GetComponent<SpriteComponent>()->GetVisible());
	}
	int numacheivements2 = showAchievements->GetNumAchievments()/2;
	int numacheivements1 = showAchievements->GetNumAchievmentsCompleted() / 2;
	std::string numacheivements = std::to_string(numacheivements1) + "/" + std::to_string(numacheivements2) + " Achievements";
	textcomponentNUMAcheivementsCompleted->SetText(numacheivements);
	textcomponentNUMAcheivementsCompleted->SetVisible(showAchievements->GetComponent<SpriteComponent>()->GetVisible());

	//hugged dragon
	Entity* eHero = m_owner->GetScene()->GetEntitiesWithID("hero");
	Entity* eDragon = m_owner->GetScene()->GetEntitiesWithID("dragon");
	Entity* mainroom = m_owner->GetScene()->GetEntitiesWithID("mainroom");
	Entity* room2door = m_owner->GetScene()->GetEntitiesWithID("room2door");
	Entity* mainroomtopleftdoor = m_owner->GetScene()->GetEntitiesWithID("topLeftDoor");
	Entity* mainbottomleftdoor = m_owner->GetScene()->GetEntitiesWithID("bottomLeftDoor");
	Entity* maintoprightdoor = m_owner->GetScene()->GetEntitiesWithID("topRightDoor");
	Entity* mainbottomrightdoor = m_owner->GetScene()->GetEntitiesWithID("bottomRightDoor");
	Entity* room3door = m_owner->GetScene()->GetEntitiesWithID("room3door");
	Entity* room4door = m_owner->GetScene()->GetEntitiesWithID("room4_1door");
	Entity* room5door = m_owner->GetScene()->GetEntitiesWithID("room5_1door");
	Entity* room2LavaFountainL = m_owner->GetScene()->GetEntitiesWithID("leftLavaFountain");
	Entity* room2LavaFountainR = m_owner->GetScene()->GetEntitiesWithID("rightLavaFountain");
	Room* room = ((Room*)mainroom);
	m_roomswitch = m_roomswitch + Timer::Instance()->DeltaTime();
	
	//delete related acheivements
	if (InputManager::Instance()->GetActionButton("delete") == InputManager::eButtonState::HELD) {
			if (eHero->GetComponent<AABBComponent>()->Intersects(mainroomtopleftdoor->GetComponent<AABBComponent>()) && (mainroomtopleftdoor->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				mainroomtopleftdoor->GetComponent<SpriteComponent>()->SetVisible(false);
				if (mainroomtopleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false && (mainbottomleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (maintoprightdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (mainbottomrightdoor->GetComponent<SpriteComponent>()->GetVisible() == false)) {
					m_owner->SetState("TrapDragonEnding");
				}
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(mainbottomleftdoor->GetComponent<AABBComponent>()) && (mainbottomleftdoor->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				mainbottomleftdoor->GetComponent<SpriteComponent>()->SetVisible(false);
				if (mainroomtopleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false && (mainbottomleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (maintoprightdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (mainbottomrightdoor->GetComponent<SpriteComponent>()->GetVisible() == false)) {
					m_owner->SetState("TrapDragonEnding");
				}
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(maintoprightdoor->GetComponent<AABBComponent>()) && (maintoprightdoor->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				maintoprightdoor->GetComponent<SpriteComponent>()->SetVisible(false);
				if (mainroomtopleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false && (mainbottomleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (maintoprightdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (mainbottomrightdoor->GetComponent<SpriteComponent>()->GetVisible() == false)) {
					m_owner->SetState("TrapDragonEnding");
				}
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(mainbottomrightdoor->GetComponent<AABBComponent>()) && (mainbottomrightdoor->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				mainbottomrightdoor->GetComponent<SpriteComponent>()->SetVisible(false);
				if (mainroomtopleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false && (mainbottomleftdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (maintoprightdoor->GetComponent<SpriteComponent>()->GetVisible() == false) && (mainbottomrightdoor->GetComponent<SpriteComponent>()->GetVisible() == false)) {
					m_owner->SetState("TrapDragonEnding");
				}
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(room3door->GetComponent<AABBComponent>()) && (room3door->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				room3door->GetComponent<SpriteComponent>()->SetVisible(false);
				m_owner->SetState("TrapYourselfEnding");
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(room2door->GetComponent<AABBComponent>()) && (room2door->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				room2door->GetComponent<SpriteComponent>()->SetVisible(false);
				m_owner->SetState("TrapYourselfEnding");
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(room4door->GetComponent<AABBComponent>()) && (room4door->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				room4door->GetComponent<SpriteComponent>()->SetVisible(false);
				m_owner->SetState("TrapYourselfEnding");
			}
			else if (eHero->GetComponent<AABBComponent>()->Intersects(room5door->GetComponent<AABBComponent>()) && (room5door->GetComponent<SpriteComponent>()->GetVisible() == true)) {
				room5door->GetComponent<SpriteComponent>()->SetVisible(false);
				m_owner->SetState("TrapYourselfEnding");
			}
	}
	

	//check door interesections
	if (((eHero->GetComponent<AABBComponent>()->Intersects(room2door->GetComponent<AABBComponent>()) && (room2door->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 1)
	{
		((Room*)mainroom)->ChangeRoom(0);
		eHero->GetTransform().position = Vector2D(65.0f, 260.0f);
		m_roomswitch = 0.0f;
		room2LavaFountainL->GetComponent<SpriteComponent>()->SetVisible(false);
		room2LavaFountainR->GetComponent<SpriteComponent>()->SetVisible(false);
		eDragon->GetComponent<SpriteComponent>()->SetVisible();

	}
	
	if (((eHero->GetComponent<AABBComponent>()->Intersects(mainroomtopleftdoor->GetComponent<AABBComponent>()) && (mainroomtopleftdoor->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 0)
	{
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible(false);
		((Room*)mainroom)->ChangeRoom(1);
		room2LavaFountainL->GetComponent<SpriteComponent>()->SetVisible();
		room2LavaFountainR->GetComponent<SpriteComponent>()->SetVisible();
		eHero->GetTransform().position = Vector2D(735.0f, 660.0f);
	}
	if (((eHero->GetComponent<AABBComponent>()->Intersects(maintoprightdoor->GetComponent<AABBComponent>()) 
		&& (maintoprightdoor->GetComponent<SpriteComponent>()->GetVisible() == true) 
		&& m_roomswitch > 3.0f))
		&& room->m_roomIndex == 0)
	{
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible(false);
		((Room*)mainroom)->ChangeRoom(3);
		eHero->GetTransform().position = Vector2D(105.0f, 660.0f);
	}
	if (((eHero->GetComponent<AABBComponent>()->Intersects(mainbottomrightdoor->GetComponent<AABBComponent>()) && (mainbottomrightdoor->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 0)
	{
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible(false);
		((Room*)mainroom)->ChangeRoom(4);
		eHero->GetTransform().position = Vector2D(105.0f, 160.0f);
	}

	if (((eHero->GetComponent<AABBComponent>()->Intersects(room3door->GetComponent<AABBComponent>()) && (room3door->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 2)
	{
		((Room*)mainroom)->ChangeRoom(0);
		eHero->GetTransform().position = Vector2D(65.0f, 518.0f);
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible();

	}

	if (((eHero->GetComponent<AABBComponent>()->Intersects(room4door->GetComponent<AABBComponent>()) && (room4door->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 3)
	{
		((Room*)mainroom)->ChangeRoom(0);
		eHero->GetTransform().position = Vector2D(705.0f, 250.0f);
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible();
	}
	if (((eHero->GetComponent<AABBComponent>()->Intersects(room5door->GetComponent<AABBComponent>()) && (room5door->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 4)
	{
		((Room*)mainroom)->ChangeRoom(0);
		eHero->GetTransform().position = Vector2D(705.0f, 500.0f);
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible();

	}

	if (((eHero->GetComponent<AABBComponent>()->Intersects(mainbottomleftdoor->GetComponent<AABBComponent>()) && (mainbottomleftdoor->GetComponent<SpriteComponent>()->GetVisible() == true) && m_roomswitch > 3.0f)) && room->m_roomIndex == 0)
	{
		m_roomswitch = 0.0f;
		eDragon->GetComponent<SpriteComponent>()->SetVisible(false);
		((Room*)mainroom)->ChangeRoom(2);
		eHero->GetTransform().position = Vector2D(735.0f, 200.0f);
	}

	//if statement for checks that involve any "pick up" action
	if (InputManager::Instance()->GetActionButton("use") == InputManager::eButtonState::PRESSED)
	{
		//checks intersect
		if ((eHero->GetComponent<AABBComponent>()->Intersects(eDragon->GetComponent<AABBComponent>()) && (eDragon->GetComponent<SpriteComponent>()->GetVisible() == true)))
		{
			std::string id = ((Hero*)eHero)->GetItemHeld()->GetItemType();
			if (id == "No Items") { m_owner->SetState("HugDragonEnding"); }
			if (id == "sword") { m_owner->SetState("KillDragonEnding"); }
			if (id == "poison") { m_owner->SetState("PoisionEnding"); }
		}
	}
	
	//check individual items placement
	std::vector<Entity*> items = m_owner->GetScene()->GetEntitiesWithTag("item");
	for (Entity* entity : items) {
		Item* itemchosen = (Item*)entity;
		//throw away food
		if (itemchosen->GetItemType() == "food" ) {
			if ((itemchosen->GetComponent<AABBComponent>()->Intersects(room2LavaFountainL->GetComponent<AABBComponent>()) 
				|| itemchosen->GetComponent<AABBComponent>()->Intersects(room2LavaFountainR->GetComponent<AABBComponent>()) 
					) && room2LavaFountainR->GetComponent<SpriteComponent>()->GetVisible() == true) 
			{
				itemchosen->GetComponent<SpriteComponent>()->SetVisible(false);
				itemchosen->GetTransform().position = Vector2D(400.0f, 400.0f);
				m_owner->SetState("Starvation");
			}
		}
		if (itemchosen->GetItemType() == "coin"){
			if (itemchosen->GetComponent<AABBComponent>()->Intersects(eDragon->GetComponent<AABBComponent>())
				 && eDragon->GetComponent<SpriteComponent>()->GetVisible() == true && itemchosen->GetComponent<SpriteComponent>()->GetVisible() == true)
			{
				itemchosen->GetComponent<SpriteComponent>()->SetVisible(false);
				itemchosen->GetTransform().position = Vector2D(600.0f, 600.0f);
				m_owner->SetState("DragonOffering");
			}
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


	Achievement* achievements = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	if (achievements->GetNumAchievments() == achievements->GetNumAchievmentsCompleted())
	{
		m_owner->SetState("game_over");
	}
}


void GameState::Exit()
{

	AudioSystem::Instance()->RemoveSound("background");
	Entity* titlebanner = m_owner->GetScene()->GetEntitiesWithID("TitleBanner");
	SpriteComponent* spritecomponentTitlebanner = titlebanner->GetComponent<SpriteComponent>();
	spritecomponentTitlebanner->SetVisible(true);

}

void GameOverState::Enter()
{
	//print out score?
	Entity* titlebanner = m_owner->GetScene()->GetEntitiesWithID("TitleBanner");
	SpriteComponent* spritecomponentTitlebanner = titlebanner->GetComponent<SpriteComponent>();
	spritecomponentTitlebanner->SetVisible(false);

	Entity* gameoverprompt = m_owner->GetScene()->AddEntity<Entity>("GameOverText");
	gameoverprompt->GetTransform().position = Vector2D(30.0f, 100.0f);
	TextComponent* gameoverprompttextComponent = gameoverprompt->AddComponent<TextComponent>();
	gameoverprompttextComponent->Create("Congratulations on Completing all Achievements!", "Textures\\emulogic.ttf", 16, Color::white);
	gameoverprompttextComponent->SetDepth(120);


	//create credits
	std::vector<std::string> credits = { 
		"Programmer: Emily Remy",
		"Programmer: Carl Warren", 
		"Programmer: Joe Hommel", 
		"Programmer: Tyler White", 
		"Tilesets by 0x72 on itch.io",
		"Sound by Rin on itch.io",
		"Food by Henry on itch.io"
	};

	for (int i = 0; i < credits.size(); i++) {
		Entity* Credits = m_owner->GetScene()->AddEntity<Entity>("credits");
		TextComponent* Creditstext = Credits->AddComponent<TextComponent>();
		Creditstext->SetDepth(120);
		Credits->GetTransform().position = Vector2D(130.0f, (float)(400.0f + i * 50));
		Creditstext->Create(credits[i], "Textures\\emulogic.ttf", 10, Color::white);

	}

	Entity* escprompt = m_owner->GetScene()->AddEntity<Entity>("ESCPromptText");
	escprompt->GetTransform().position = Vector2D(130.0f, 200.0f);
	TextComponent* escprompttextComponent = escprompt->AddComponent<TextComponent>();
	escprompttextComponent->Create("Press ESC to quit", "Textures\\emulogic.ttf", 24, Color::white);
	escprompttextComponent->SetDepth(120);
	escprompttextComponent->SetVisible(false);

}

void GameOverState::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();

	//scroll through credits by position
//	std::vector<Entity*> credits = m_owner->GetScene()->GetEntitiesWithTag("credits");
//	for (Entity* entity : credits) {
//		entity->GetTransform().position += Vector2D::down* 30.0f;
	//
	//}


	if (m_timerRate <= 0.0f)
	{
		Entity* escprompt = m_owner->GetScene()->GetEntitiesWithID("ESCPromptText");
		escprompt->GetComponent<TextComponent>()->SetVisible(true);
		//after 30 seconds show final prompt
	}
}

void GameOverState::Exit()
{

}



void BoreDragonEnding::Enter()
{
	m_timerRate = 3.0f;
	Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("ReturnText1");
	huggedText1->GetTransform().position = Vector2D(130.0f, 350.0f);
	TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
	huggedtextComponent1->Create("You Have Bored The Dragon to Death.", "Textures\\emulogic.ttf", 16, Color::white);
	huggedtextComponent1->SetDepth(120);
	Entity* huggedText2 = m_owner->GetScene()->AddEntity<Entity>("ReturnText2");
	huggedText2->GetTransform().position = Vector2D(175.0f, 400.0f);
	TextComponent* huggedtextComponent2 = huggedText2->AddComponent<TextComponent>();
	huggedtextComponent2->Create("Maybe put down the Chips and Play", "Textures\\emulogic.ttf", 10, Color::white);
	huggedtextComponent2->SetDepth(120);


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
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
} 

void BoreDragonEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("ReturnText1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText1 = m_owner->GetScene()->GetEntitiesWithID("ReturnText2");
	if (huggedText1) {
		huggedText1->SetState(Entity::eState::DESTROY);
	}
}

void HugDragonEnding::Enter()
{
	AudioSystem::Instance()->AddSound("peaceful", "Sound\\angelsballad.mid");
	AudioSystem::Instance()->PlaySound("peaceful", false);



		Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("HugTextSent1");
		huggedText1->GetTransform().position = Vector2D(175.0f, 350.0f);
		TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
		huggedtextComponent1->Create("You Have Hugged the Dragon. ", "Textures\\emulogic.ttf", 16, Color::white);
		huggedtextComponent1->SetDepth(120);

		Entity* huggedText2 = m_owner->GetScene()->AddEntity<Entity>("HugTextSent2");
		huggedText2->GetTransform().position = Vector2D(130.0f, 400.0f);
		TextComponent* huggedtextComponent2 = huggedText2->AddComponent<TextComponent>();
		huggedtextComponent2->Create("It has been warmed by Kindess and will do no more harm.", "Textures\\emulogic.ttf", 10, Color::white);
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
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void HugDragonEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("HugTextSent1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("HugTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
	AudioSystem::Instance()->RemoveSound("peaceful");
}

void KillDragonEnding::Enter()
{
	AudioSystem::Instance()->AddSound("death", "Sound\\churchofsaints.mid");
	AudioSystem::Instance()->PlaySound("death", false);

	Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("KillTextSent1");
	huggedText1->GetTransform().position = Vector2D(130.0f, 350.0f);
	TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
	huggedtextComponent1->Create("You Have Slain the Mighty Dragon.",  "Textures\\emulogic.ttf", 16, Color::white);
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
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void KillDragonEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("KillTextSent1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("KillTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
	AudioSystem::Instance()->RemoveSound("death");
}

void RespectEnding::Enter()
{
	AudioSystem::Instance()->AddSound("bonus", "Sound\\Bonus.wav");
	AudioSystem::Instance()->PlaySound("bonus", false);
	Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("RespectTextSent1");
	huggedText1->GetTransform().position = Vector2D(130.0f, 350.0f);
	TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
	huggedtextComponent1->Create("You Pay Respect to your kill.", "Textures\\emulogic.ttf", 16, Color::white);
	huggedtextComponent1->SetDepth(120);

	Entity* huggedText2 = m_owner->GetScene()->AddEntity<Entity>("RespectTextSent2");
	huggedText2->GetTransform().position = Vector2D(130.0f, 400.0f);
	TextComponent* huggedtextComponent2 = huggedText2->AddComponent<TextComponent>();
	huggedtextComponent2->Create("You've Earned a Bonus Achievement.", "Textures\\emulogic.ttf", 10, Color::white);
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
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void RespectEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText = m_owner->GetScene()->GetEntitiesWithID("RespectTextSent1");
	if (huggedText) {
		huggedText->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("RespectTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
	AudioSystem::Instance()->RemoveSound("bonus");
}

void PoisonDragonEnding::Enter()
{
	Entity* huggedText1 = m_owner->GetScene()->AddEntity<Entity>("PoisonTextSent1");
	huggedText1->GetTransform().position = Vector2D(175.0f, 350.0f);
	TextComponent* huggedtextComponent1 = huggedText1->AddComponent<TextComponent>();
	huggedtextComponent1->Create("You feed the dragon the Poison. ", "Textures\\emulogic.ttf", 16, Color::white);
	huggedtextComponent1->SetDepth(120);

	Entity* huggedText2 = m_owner->GetScene()->AddEntity<Entity>("PoisonTextSent2");
	huggedText2->GetTransform().position = Vector2D(130.0f, 400.0f);
	TextComponent* huggedtextComponent2 = huggedText2->AddComponent<TextComponent>();
	huggedtextComponent2->Create("Its face becomes pale as it takes it's last breath", "Textures\\emulogic.ttf", 10, Color::white);
	huggedtextComponent2->SetDepth(120);

	//achievement
	Achievement* poisonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* poisonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("PoisonDragonAchievement");
	poisonAchivement->updateAchievement(poisonAchivementAchievement);
	Achievement* poisonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* poisonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("PoisonDragonTextAchievement");
	poisonAchivementText->updateAchievement(poisonAchivementTextAchievement);
}

void PoisonDragonEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);

	}
}

void PoisonDragonEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText1 = m_owner->GetScene()->GetEntitiesWithID("PoisonTextSent1");
	if (huggedText1) {
		huggedText1->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("PoisonTextSent2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
	
}

void TrapDragonEnding::Enter()
{
	Entity* TrappedText1 = m_owner->GetScene()->AddEntity<Entity>("TrapDragonText1");
	TrappedText1->GetTransform().position = Vector2D(130.0f, 350.0f);
	TextComponent* trappedtextComponent1 = TrappedText1->AddComponent<TextComponent>();
	trappedtextComponent1->Create("You have trapped the dragon in.", "Textures\\emulogic.ttf", 16, Color::white);
	trappedtextComponent1->SetDepth(120);

	Entity* TrappedText2 = m_owner->GetScene()->AddEntity<Entity>("TrapDragonText2");
	TrappedText2->GetTransform().position = Vector2D(130.0f, 400.0f);
	TextComponent* trappedtextComponent2 = TrappedText2->AddComponent<TextComponent>();
	trappedtextComponent2->Create("It can no longer terrorize the countryside", "Textures\\emulogic.ttf", 10, Color::white);
	trappedtextComponent2->SetDepth(120);

	//achievement
	Achievement* poisonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* poisonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("TrapDragonAchievement");
	poisonAchivement->updateAchievement(poisonAchivementAchievement);
	Achievement* poisonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* poisonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("TrapDragonTextAchievement");
	poisonAchivementText->updateAchievement(poisonAchivementTextAchievement);
}

void TrapDragonEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void TrapDragonEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText1 = m_owner->GetScene()->GetEntitiesWithID("TrapDragonText1");
	if (huggedText1) {
		huggedText1->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("TrapDragonText2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}

void TrapYourselfEnding::Enter()
{
	Entity* TrappedText1 = m_owner->GetScene()->AddEntity<Entity>("TrapYourselfText1");
	TrappedText1->GetTransform().position = Vector2D(130.0f, 350.0f);
	TextComponent* trappedtextComponent1 = TrappedText1->AddComponent<TextComponent>();
	trappedtextComponent1->Create("You have trapped yourself in here", "Textures\\emulogic.ttf", 16, Color::white);
	trappedtextComponent1->SetDepth(120);

	Entity* TrappedText2 = m_owner->GetScene()->AddEntity<Entity>("TrapYourselfText2");
	TrappedText2->GetTransform().position = Vector2D(130.0f, 400.0f);
	TextComponent* trappedtextComponent2 = TrappedText2->AddComponent<TextComponent>();
	trappedtextComponent2->Create("uh... Congratulations?", "Textures\\emulogic.ttf", 10, Color::white);
	trappedtextComponent2->SetDepth(120);

	//achievement
	Achievement* poisonAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* poisonAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("TrapYourselfAchievement");
	poisonAchivement->updateAchievement(poisonAchivementAchievement);
	Achievement* poisonAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* poisonAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("TrapYourselfTextAchievement");
	poisonAchivementText->updateAchievement(poisonAchivementTextAchievement);
}

void TrapYourselfEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void TrapYourselfEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText1 = m_owner->GetScene()->GetEntitiesWithID("TrapYourselfText1");
	if (huggedText1) {
		huggedText1->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("TrapYourselfText2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}

void StarveDragonEnding::Enter()
{
	Entity* StarveText1 = m_owner->GetScene()->AddEntity<Entity>("Starvation1");
	StarveText1->GetTransform().position = Vector2D(175.0f, 350.0f);
	TextComponent* starvetextComponent1 = StarveText1->AddComponent<TextComponent>();
	starvetextComponent1->Create("The dragon has no more food.", "Textures\\emulogic.ttf", 16, Color::white);
	starvetextComponent1->SetDepth(120);

	Entity* StarveText2 = m_owner->GetScene()->AddEntity<Entity>("Starvation2");
	StarveText2->GetTransform().position = Vector2D(175.0f, 400.0f);
	TextComponent* starvetextComponent2 = StarveText2->AddComponent<TextComponent>();
	starvetextComponent2->Create("*you hear a stomach growl*", "Textures\\emulogic.ttf", 10, Color::white);
	starvetextComponent2->SetDepth(120);

	//achievement
	Achievement* starveAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* starveAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("StarvationAchievement");
	starveAchivement->updateAchievement(starveAchivementAchievement);
	Achievement* starveAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* starveAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("StarvationTextAchievement");
	starveAchivementText->updateAchievement(starveAchivementTextAchievement);
}

void StarveDragonEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void StarveDragonEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText1 = m_owner->GetScene()->GetEntitiesWithID("Starvation1");
	if (huggedText1) {
		huggedText1->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("Starvation2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}

void DragonOfferingEnding::Enter()
{
	Entity* StarveText1 = m_owner->GetScene()->AddEntity<Entity>("Starvation1");
	StarveText1->GetTransform().position = Vector2D(175.0f, 350.0f);
	TextComponent* starvetextComponent1 = StarveText1->AddComponent<TextComponent>();
	starvetextComponent1->Create("You offer up payment.", "Textures\\emulogic.ttf", 16, Color::white);
	starvetextComponent1->SetDepth(120);

	Entity* StarveText2 = m_owner->GetScene()->AddEntity<Entity>("Starvation2");
	StarveText2->GetTransform().position = Vector2D(130.0f, 400.0f);
	TextComponent* starvetextComponent2 = StarveText2->AddComponent<TextComponent>();
	starvetextComponent2->Create("The Dragon is pleased with your contribution", "Textures\\emulogic.ttf", 10, Color::white);
	starvetextComponent2->SetDepth(120);

	//achievement
	Achievement* starveAchivement = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* starveAchivementAchievement = m_owner->GetScene()->GetEntitiesWithID("DragonOfferingAchievement");
	starveAchivement->updateAchievement(starveAchivementAchievement);
	Achievement* starveAchivementText = (Achievement*)m_owner->GetScene()->GetEntitiesWithID("achievement");
	Entity* starveAchivementTextAchievement = m_owner->GetScene()->GetEntitiesWithID("DragonOfferingTextAchievement");
	starveAchivementText->updateAchievement(starveAchivementTextAchievement);
}

void DragonOfferingEnding::Update()
{
	m_timerRate = m_timerRate - Timer::Instance()->DeltaTime();
	if (m_timerRate <= 0.0f)
	{
		m_owner->SetState("game");
	}
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("hero");
	if (entity1) {
		entity1->GetTransform().position = Vector2D(400.0f, 700.0f);
	}
}

void DragonOfferingEnding::Exit()
{
	m_timerRate = m_timerReset;
	Entity* huggedText1 = m_owner->GetScene()->GetEntitiesWithID("Starvation1");
	if (huggedText1) {
		huggedText1->SetState(Entity::eState::DESTROY);
	}
	Entity* huggedText2 = m_owner->GetScene()->GetEntitiesWithID("Starvation2");
	if (huggedText2) {
		huggedText2->SetState(Entity::eState::DESTROY);
	}
}
