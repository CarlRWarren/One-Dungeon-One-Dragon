#include "achievement.h"
#include "transform.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "hero.h"
#include "inputManager.h"
#include <string>
#include <iostream>
#include <fstream>

void Achievement::Create(const Vector2D & position)
{
	SpriteComponent* achievementBackgroundSpriteComponent = AddComponent<SpriteComponent>();
	achievementBackgroundSpriteComponent->Create("Sprites\\AchievementBackground.png", Vector2D(0.5f, 0.5f));
	GetTransform().scale = Vector2D(1.0f, 1.0f);
	achievementBackgroundSpriteComponent->SetDepth(200);
	achievementBackgroundSpriteComponent->SetVisible(false);

	m_transform.position = position;
	SetTag("achievement");
		
	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(1.0f,1.0f));
	CreateAchievements();
}

void Achievement::Update()
{
	Entity::Update();
}

void Achievement::Save()
{
	if (m_completedAchievementsTags.size() > 0) {
		std::ofstream myfile;
		myfile.open("../Saves/achievement.txt");
		for (std::string achievementtags : m_completedAchievementsTags) {
			myfile << achievementtags + "\n";
		}
		myfile.close();
	}
}

void Achievement::Load()
{
	std::vector<std::string> AUID;
	std::ifstream myfile("../Saves/achievement.txt");
	if (myfile.is_open()) {
		std::string UIDString;
		while (std::getline(myfile, UIDString)) {
			AUID.push_back(trim(UIDString));
		}
		myfile.close();
	}
	for (std::string UID : AUID) {
		for (Entity* entity : m_achievements) {
			ID entityid = entity->GetTag();
			std::string entitytag = entityid.GetIDString();
			if (entitytag == UID) {
				updateAchievement(entitytag);
			}
		}
	}
}


void Achievement::OnEvent(const Event & event)
{
 	
}

void Achievement::CreateAchievements()
{
	//achievments
	Entity* hugDragon = GetScene()->AddEntity<Entity>("HugDragonAchievement");
	hugDragon->SetTag("HugDragonAchievement");
	SpriteComponent* spritecomponentHugDragon = hugDragon->AddComponent<SpriteComponent>();
	spritecomponentHugDragon->Create("sprites\\ui_heart_full.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(hugDragon);
	spritecomponentHugDragon->SetDepth(202);
	hugDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* hugDragonText = GetScene()->AddEntity<Entity>("HugDragonTextAchievement");
	hugDragonText->SetTag("HugDragonTextAchievement");
	TextComponent* textcomponentHugDragon = hugDragonText->AddComponent<TextComponent>();
	textcomponentHugDragon->Create("Awwee!", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(hugDragonText);
	textcomponentHugDragon->SetDepth(202);
	hugDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* boreDragon = GetScene()->AddEntity<Entity>("BoreDragonAchievement");
	boreDragon->SetTag("BoreDragonAchievement");
	SpriteComponent* spritecomponentBoreDragon = boreDragon->AddComponent<SpriteComponent>();
	spritecomponentBoreDragon->Create("sprites\\skull.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(boreDragon);
	spritecomponentBoreDragon->SetDepth(202);
	boreDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* boreDragonText = GetScene()->AddEntity<Entity>("BoreDragonTextAchievement");
	boreDragonText->SetTag("BoreDragonTextAchievement");
	TextComponent* textcomponentBoreDragon = boreDragonText->AddComponent<TextComponent>();
	textcomponentBoreDragon->Create("Wow, you waited?", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(boreDragonText);
	textcomponentBoreDragon->SetDepth(202);
	boreDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* killDragon = GetScene()->AddEntity<Entity>("KillDragonAchievement");
	killDragon->SetTag("KillDragonAchievement");
	SpriteComponent* spritecomponentKillDragon = killDragon->AddComponent<SpriteComponent>();
	spritecomponentKillDragon->Create("sprites\\weapon_regular_sword.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(killDragon);
	spritecomponentKillDragon->SetDepth(202);
	killDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* killDragonText = GetScene()->AddEntity<Entity>("KillDragonTextAchievement");
	killDragonText->SetTag("KillDragonTextAchievement");
	TextComponent* textcomponentKillDragon = killDragonText->AddComponent<TextComponent>();
	textcomponentKillDragon->Create("Murderer...", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(killDragonText);
	textcomponentKillDragon->SetDepth(202);
	killDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* respectDragon = GetScene()->AddEntity<Entity>("RespectDragonAchievement");
	respectDragon->SetTag("RespectDragonAchievement");
	SpriteComponent* spritecomponentRespectDragon = respectDragon->AddComponent<SpriteComponent>();
	spritecomponentRespectDragon->Create("sprites\\F.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(respectDragon);
	spritecomponentRespectDragon->SetDepth(202);
	respectDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* respectDragonText = GetScene()->AddEntity<Entity>("RespectDragonTextAchievement");
	respectDragonText->SetTag("RespectDragonTextAchievement");
	TextComponent* textcomponentRespectDragon = respectDragonText->AddComponent<TextComponent>();
	textcomponentRespectDragon->Create("Press F to Pay Respects.", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(respectDragonText);
	textcomponentRespectDragon->SetDepth(202);
	respectDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* wizardSecret = GetScene()->AddEntity<Entity>("WizardSecretAchievement");
	wizardSecret->SetTag("WizardSecretAchievement");
	SpriteComponent* spritecomponentWizardSecret = wizardSecret->AddComponent<SpriteComponent>();
	spritecomponentWizardSecret->Create("sprites\\weapon_red_magic_staff.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(wizardSecret);
	spritecomponentWizardSecret->SetDepth(202);
	wizardSecret->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* wizardSecretText = GetScene()->AddEntity<Entity>("WizardSecretTextAchievement");
	wizardSecretText->SetTag("WizardSecretTextAchievement");
	TextComponent* textcomponentWizardSecret = wizardSecretText->AddComponent<TextComponent>();
	textcomponentWizardSecret->Create("Secrets? I didn't know?", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(wizardSecretText);
	textcomponentWizardSecret->SetDepth(202);
	wizardSecretText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* poisonDragon = GetScene()->AddEntity<Entity>("PoisonDragonAchievement");
	poisonDragon->SetTag("PoisonDragonAchievement");
	SpriteComponent* spritecomponentPoisonDragon = poisonDragon->AddComponent<SpriteComponent>();
	spritecomponentPoisonDragon->Create("sprites\\flask_big_green.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(poisonDragon);
	spritecomponentPoisonDragon->SetDepth(202);
	poisonDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* poisonDragonText = GetScene()->AddEntity<Entity>("PoisonDragonTextAchievement");
	poisonDragonText->SetTag("PoisonDragonTextAchievement");
	TextComponent* textcomponentPoisonDragon = poisonDragonText->AddComponent<TextComponent>();
	textcomponentPoisonDragon->Create("Falmer Ear and Imp Stool", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(poisonDragonText);
	textcomponentPoisonDragon->SetDepth(202);
	poisonDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* TrapDragon = GetScene()->AddEntity<Entity>("TrapDragonAchievement");
	TrapDragon->SetTag("TrapDragonAchievement");
	SpriteComponent* spritecomponentTrapDragon = TrapDragon->AddComponent<SpriteComponent>();
	spritecomponentTrapDragon->Create("sprites\\floor_ladder.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(TrapDragon);
	spritecomponentTrapDragon->SetDepth(202);
	TrapDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* TrapDragonText = GetScene()->AddEntity<Entity>("TrapDragonTextAchievement");
	TrapDragonText->SetTag("TrapDragonTextAchievement");
	TextComponent* textcomponentTrapDragon = TrapDragonText->AddComponent<TextComponent>();
	textcomponentTrapDragon->Create("He's not going anywhere", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(TrapDragonText);
	textcomponentTrapDragon->SetDepth(202);
	TrapDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* TrapYourself = GetScene()->AddEntity<Entity>("TrapYourselfAchievement");
	TrapYourself->SetTag("TrapYourselfAchievement");
	SpriteComponent* spritecomponentTrapYourself = TrapYourself->AddComponent<SpriteComponent>();
	spritecomponentTrapYourself->Create("sprites\\skelet_idle_anim_f0.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(TrapYourself);
	spritecomponentTrapYourself->SetDepth(202);
	TrapYourself->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* TrapYourselfText = GetScene()->AddEntity<Entity>("TrapYourselfTextAchievement");
	TrapYourselfText->SetTag("TrapYourselfTextAchievement");
	TextComponent* textcomponentTrapYourselfText = TrapYourselfText->AddComponent<TextComponent>();
	textcomponentTrapYourselfText->Create("You're not going anywhere...", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(TrapYourselfText);
	textcomponentTrapYourselfText->SetDepth(202);
	TrapYourselfText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* starveDragon = GetScene()->AddEntity<Entity>("StarvationAchievement");
	starveDragon->SetTag("StarvationAchievement");
	SpriteComponent* spritecomponentStarveDragon = starveDragon->AddComponent<SpriteComponent>();
	spritecomponentStarveDragon->Create("sprites\\steak.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(starveDragon);
	spritecomponentStarveDragon->SetDepth(202);
	starveDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* starveDragonText = GetScene()->AddEntity<Entity>("StarvationTextAchievement");
	starveDragonText->SetTag("StarvationTextAchievement");
	TextComponent* textcomponentStarveDragon = starveDragonText->AddComponent<TextComponent>();
	textcomponentStarveDragon->Create("My belly, It's sooooo empty.:(", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(starveDragonText);
	textcomponentStarveDragon->SetDepth(202);
	starveDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* DragonOfferingAchievement = GetScene()->AddEntity<Entity>("DragonOfferingAchievement");
	DragonOfferingAchievement->SetTag("DragonOfferingAchievement");
	SpriteComponent* spritecomponentDragonOfferingAchievement = DragonOfferingAchievement->AddComponent<SpriteComponent>();
	spritecomponentDragonOfferingAchievement->Create("sprites\\coin_anim_f0.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(DragonOfferingAchievement);
	spritecomponentDragonOfferingAchievement->SetDepth(202);
	DragonOfferingAchievement->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* DragonOfferingAchievementText = GetScene()->AddEntity<Entity>("DragonOfferingTextAchievement");
	DragonOfferingAchievementText->SetTag("DragonOfferingTextAchievement");
	TextComponent* textcomponentDragonOffering = DragonOfferingAchievementText->AddComponent<TextComponent>();
	textcomponentDragonOffering->Create("Pay your Taxes", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(DragonOfferingAchievementText);
	textcomponentDragonOffering->SetDepth(202);
	DragonOfferingAchievementText->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* feedDragon = GetScene()->AddEntity<Entity>("FeedDragonAchievement");
	feedDragon->SetTag("FeedDragonAchievement");
	SpriteComponent* spritecomponentFeedDragon = feedDragon->AddComponent<SpriteComponent>();
	spritecomponentFeedDragon->Create("sprites\\apple.png", Vector2D(0.5f, 0.5f));
	m_achievements.push_back(feedDragon);
	spritecomponentFeedDragon->SetDepth(202);
	feedDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

	Entity* feedDragonText = GetScene()->AddEntity<Entity>("FeedDragonTextAchievement");
	feedDragonText->SetTag("FeedDragonTextAchievement");
	TextComponent* textcomponentFeedDragon = feedDragonText->AddComponent<TextComponent>();
	textcomponentFeedDragon->Create("Thanks for the food", "Textures\\emulogic.ttf", 8, Color::white);
	m_achievements.push_back(feedDragonText);
	textcomponentFeedDragon->SetDepth(202);
	feedDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);
}

void Achievement::updateAchievement(std::string completedAchivement)
{
	bool exists = false;
	for (std::string entity : m_completedAchievementsTags) {
		if (entity == completedAchivement) {
			exists = true;
		}
	}
	if (exists == false) {
		m_completedAchievementsTags.push_back(completedAchivement);
	}

}

void Achievement::setVisibility(bool isVisible)
{
	float x = 100.0f;
	float y = 100.0f;

	float tx = 150.0f;
	float ty = 95.0f;
	GetComponent<SpriteComponent>()->SetVisible(isVisible);

	for (std::string entity : m_completedAchievementsTags) {
		Entity* entityget = m_scene->GetEntitiesWithID(entity);

		if (entityget) {
			entityget->GetTransform().scale = Vector2D(2.0f, 2.0f);
			SpriteComponent* achieveSprite = entityget->GetComponent<SpriteComponent>();
			if (achieveSprite) {
				entityget->GetComponent<SpriteComponent>()->SetVisible(isVisible);
				entityget->GetTransform().position = Vector2D(x, y);
				if (y >= 600.0f) {
					y = 100.0f;
				}
				else {
					y += 50.0f;
				}
			}
			TextComponent* achieveText = entityget->GetComponent<TextComponent>();
			if (achieveText) {
				entityget->GetComponent<TextComponent>()->SetVisible(isVisible);
				entityget->GetTransform().position = Vector2D(tx, ty);
				if (tx >= 700.0f) {
					ty = 100.0f;
				}
				else {
					ty += 50.0f;
				}
			}
		}
	}
}