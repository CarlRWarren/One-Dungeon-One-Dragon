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
		std::ofstream myfile;
		myfile.open("achievement.txt");
		for (Entity* entity : m_completedAchievements) {
				myfile << ((ID)entity->GetTag()).GetIDString() + "\n";
		}
		myfile.close();
}

void Achievement::Load()
{
		std::vector<std::string> AUID;
		std::ifstream myfile("achievement.txt");
		if (myfile.is_open()) {
				std::string UIDString;
				while (std::getline(myfile, UIDString)) {
						AUID.push_back(UIDString);
				}
				myfile.close();
		}
		for (std::string UID : AUID) {
				for (Entity* entity : m_achievements) {
						if (((ID)entity->GetTag()).GetIDString() == UID) {
								updateAchievement(entity);
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
		SpriteComponent* spritecomponentHugDragon = hugDragon->AddComponent<SpriteComponent>();
		spritecomponentHugDragon->Create("sprites\\ui_heart_full.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(hugDragon);
		spritecomponentHugDragon->SetDepth(202);
		hugDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* hugDragonText = GetScene()->AddEntity<Entity>("HugDragonTextAchievement");
		TextComponent* textcomponentHugDragon = hugDragonText->AddComponent<TextComponent>();
		textcomponentHugDragon->Create("Awwee!", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(hugDragonText);
		textcomponentHugDragon->SetDepth(202);
		hugDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* boreDragon = GetScene()->AddEntity<Entity>("BoreDragonAchievement");
		SpriteComponent* spritecomponentBoreDragon = boreDragon->AddComponent<SpriteComponent>();
		spritecomponentBoreDragon->Create("sprites\\skull.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(boreDragon);
		spritecomponentBoreDragon->SetDepth(202);
		boreDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* boreDragonText = GetScene()->AddEntity<Entity>("BoreDragonTextAchievement");
		TextComponent* textcomponentBoreDragon = boreDragonText->AddComponent<TextComponent>();
		textcomponentBoreDragon->Create("Wow, you waited?", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(boreDragonText);
		textcomponentBoreDragon->SetDepth(202);
		boreDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* killDragon = GetScene()->AddEntity<Entity>("KillDragonAchievement");
		SpriteComponent* spritecomponentKillDragon = killDragon->AddComponent<SpriteComponent>();
		spritecomponentKillDragon->Create("sprites\\weapon_regular_sword.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(killDragon);
		spritecomponentKillDragon->SetDepth(202);
		killDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* killDragonText = GetScene()->AddEntity<Entity>("KillDragonTextAchievement");
		TextComponent* textcomponentKillDragon = killDragonText->AddComponent<TextComponent>();
		textcomponentKillDragon->Create("Murderer...", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(killDragonText);
		textcomponentKillDragon->SetDepth(202);
		killDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* respectDragon = GetScene()->AddEntity<Entity>("RespectDragonAchievement");
		SpriteComponent* spritecomponentRespectDragon = respectDragon->AddComponent<SpriteComponent>();
		spritecomponentRespectDragon->Create("sprites\\F.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(respectDragon);
		spritecomponentRespectDragon->SetDepth(202);
		respectDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* respectDragonText = GetScene()->AddEntity<Entity>("RespectDragonTextAchievement");
		TextComponent* textcomponentRespectDragon = respectDragonText->AddComponent<TextComponent>();
		textcomponentRespectDragon->Create("Press F to Pay Respects.", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(respectDragonText);
		textcomponentRespectDragon->SetDepth(202);
		respectDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* wizardSecret = GetScene()->AddEntity<Entity>("WizardSecretAchievement");
		SpriteComponent* spritecomponentWizardSecret = wizardSecret->AddComponent<SpriteComponent>();
		spritecomponentWizardSecret->Create("sprites\\weapon_red_magic_staff.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(wizardSecret);
		spritecomponentWizardSecret->SetDepth(202);
		wizardSecret->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* wizardSecretText = GetScene()->AddEntity<Entity>("WizardSecretTextAchievement");
		TextComponent* textcomponentWizardSecret = wizardSecretText->AddComponent<TextComponent>();
		textcomponentWizardSecret->Create("Secrets? I didn't know?", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(wizardSecretText);
		textcomponentWizardSecret->SetDepth(202);
		wizardSecretText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* poisonDragon = GetScene()->AddEntity<Entity>("PoisonDragonAchievement");
		SpriteComponent* spritecomponentPoisonDragon = poisonDragon->AddComponent<SpriteComponent>();
		spritecomponentPoisonDragon->Create("sprites\\flask_big_green.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(poisonDragon);
		spritecomponentPoisonDragon->SetDepth(202);
		poisonDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* poisonDragonText = GetScene()->AddEntity<Entity>("PoisonDragonTextAchievement");
		TextComponent* textcomponentPoisonDragon = poisonDragonText->AddComponent<TextComponent>();
		textcomponentPoisonDragon->Create("Falmer Ear and Imp Stool", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(poisonDragonText);
		textcomponentPoisonDragon->SetDepth(202);
		poisonDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* TrapDragon = GetScene()->AddEntity<Entity>("TrapDragonAchievement");
		SpriteComponent* spritecomponentTrapDragon = TrapDragon->AddComponent<SpriteComponent>();
		spritecomponentTrapDragon->Create("sprites\\floor_ladder.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(TrapDragon);
		spritecomponentTrapDragon->SetDepth(202);
		TrapDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* TrapDragonText = GetScene()->AddEntity<Entity>("TrapDragonTextAchievement");
		TextComponent* textcomponentTrapDragon = TrapDragonText->AddComponent<TextComponent>();
		textcomponentTrapDragon->Create("He's not going anywhere", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(TrapDragonText);
		textcomponentTrapDragon->SetDepth(202);
		TrapDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* TrapYourself = GetScene()->AddEntity<Entity>("TrapYourselfAchievement");
		SpriteComponent* spritecomponentTrapYourself = TrapYourself->AddComponent<SpriteComponent>();
		spritecomponentTrapYourself->Create("sprites\\skelet_idle_anim_f0.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(TrapYourself);
		spritecomponentTrapYourself->SetDepth(202);
		TrapYourself->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* TrapYourselfText = GetScene()->AddEntity<Entity>("TrapYourselfTextAchievement");
		TextComponent* textcomponentTrapYourselfText = TrapYourselfText->AddComponent<TextComponent>();
		textcomponentTrapYourselfText->Create("You're not going anywhere...", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(TrapYourselfText);
		textcomponentTrapYourselfText->SetDepth(202);
		TrapYourselfText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* starveDragon = GetScene()->AddEntity<Entity>("StarvationAchievement");
		SpriteComponent* spritecomponentStarveDragon = starveDragon->AddComponent<SpriteComponent>();
		spritecomponentStarveDragon->Create("sprites\\steak.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(starveDragon);
		spritecomponentStarveDragon->SetDepth(202);
		starveDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* starveDragonText = GetScene()->AddEntity<Entity>("StarvationTextAchievement");
		TextComponent* textcomponentStarveDragon = starveDragonText->AddComponent<TextComponent>();
		textcomponentStarveDragon->Create("My belly, It's sooooo empty.:(", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(starveDragonText);
		textcomponentStarveDragon->SetDepth(202);
		starveDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* DragonOfferingAchievement = GetScene()->AddEntity<Entity>("DragonOfferingAchievement");
		SpriteComponent* spritecomponentDragonOfferingAchievement = DragonOfferingAchievement->AddComponent<SpriteComponent>();
		spritecomponentDragonOfferingAchievement->Create("sprites\\coin_anim_f0.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(DragonOfferingAchievement);
		spritecomponentDragonOfferingAchievement->SetDepth(202);
		DragonOfferingAchievement->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* DragonOfferingAchievementText = GetScene()->AddEntity<Entity>("DragonOfferingTextAchievement");
		TextComponent* textcomponentDragonOffering = DragonOfferingAchievementText->AddComponent<TextComponent>();
		textcomponentDragonOffering->Create("Pay your Taxes", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(DragonOfferingAchievementText);
		textcomponentDragonOffering->SetDepth(202);
		DragonOfferingAchievementText->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* feedDragon = GetScene()->AddEntity<Entity>("FeedDragonAchievement");
		SpriteComponent* spritecomponentFeedDragon = feedDragon->AddComponent<SpriteComponent>();
		spritecomponentFeedDragon->Create("sprites\\apple.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(feedDragon);
		spritecomponentFeedDragon->SetDepth(202);
		feedDragon->GetTransform().position = Vector2D(-100.0f, -100.0f);

		Entity* feedDragonText = GetScene()->AddEntity<Entity>("FeedDragonTextAchievement");
		TextComponent* textcomponentFeedDragon = killDragonText->AddComponent<TextComponent>();
		textcomponentFeedDragon->Create("Thanks for the food", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(feedDragonText);
		textcomponentFeedDragon->SetDepth(202);
		feedDragonText->GetTransform().position = Vector2D(-100.0f, -100.0f);
}

void Achievement::updateAchievement(Entity * completedAchivement)
{
		bool exists = false;
		for (Entity* entity : m_completedAchievements) {
			if (entity == completedAchivement) {
				exists = true;
			}
		} 
		if (exists == false) {
				m_completedAchievements.push_back(completedAchivement);
		}

}

void Achievement::setVisibility(bool isVisible)
{
	int interval = 1;
	float x = 100.0f;
	float y = 100.0f;
	GetComponent<SpriteComponent>()->SetVisible(isVisible);

	for (Entity* entity : m_completedAchievements) {
		if (entity) {
			entity->GetTransform().position = Vector2D(x, y);
			entity->GetTransform().scale = Vector2D(2.0f, 2.0f);
			if (interval == 1) 
			{
				SpriteComponent* achieveSprite = entity->GetComponent<SpriteComponent>();
				if (achieveSprite) {
					entity->GetComponent<SpriteComponent>()->SetVisible(isVisible);
					if (y >= 600.0f) {
						y = 100.0f;
						x += 100.0f;
					}
					else {
						y -= 10.0f;
						x += 50;
					}
					++interval;
				}
			}
			else 
			{
				TextComponent* achieveText = entity->GetComponent<TextComponent>();
				if (achieveText) {
					entity->GetComponent<TextComponent>()->SetVisible(isVisible);
					if (x >= 700.0f) {
						x = 100.0f;
						y += 100.0f;
					}
					else {
						x -= 50;
						y += 10.0f;
						y += 50.0f;
					}
					--interval;
				}
			}
		}
	}
}

