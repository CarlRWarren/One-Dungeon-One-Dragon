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


void Achievement::OnEvent(const Event & event)
{
 	
}

void Achievement::CreateAchievements()
{
		Entity* hugDragon = GetScene()->AddEntity<Entity>("HugDragonAchievement");
		SpriteComponent* spritecomponentHugDragon = hugDragon->AddComponent<SpriteComponent>();
		spritecomponentHugDragon->Create("sprites\\ui_heart_full.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(hugDragon);

		Entity* hugDragonText = GetScene()->AddEntity<Entity>("HugDragonTextAchievement");
		TextComponent* textcomponentHugDragon = hugDragonText->AddComponent<TextComponent>();
		textcomponentHugDragon->Create("Awwee!", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(hugDragonText);

		Entity* boreDragon = GetScene()->AddEntity<Entity>("BoreDragonAchievement");
		SpriteComponent* spritecomponentBoreDragon = boreDragon->AddComponent<SpriteComponent>();
		spritecomponentBoreDragon->Create("sprites\\skull.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(boreDragon);

		Entity* boreDragonText = GetScene()->AddEntity<Entity>("BoreDragonTextAchievement");
		TextComponent* textcomponentBoreDragon = boreDragonText->AddComponent<TextComponent>();
		textcomponentBoreDragon->Create("Wow, you waited?", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(boreDragonText);

		Entity* killDragon = GetScene()->AddEntity<Entity>("KillDragonAchievement");
		SpriteComponent* spritecomponentKillDragon = killDragon->AddComponent<SpriteComponent>();
		spritecomponentKillDragon->Create("sprites\\weapon_regular_sword.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(killDragon);

		Entity* killDragonText = GetScene()->AddEntity<Entity>("KillDragonTextAchievement");
		TextComponent* textcomponentKillDragon = killDragonText->AddComponent<TextComponent>();
		textcomponentKillDragon->Create("Murderer...", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(killDragonText);

		Entity* respectDragon = GetScene()->AddEntity<Entity>("RespectDragonAchievement");
		SpriteComponent* spritecomponentRespectDragon = respectDragon->AddComponent<SpriteComponent>();
		spritecomponentRespectDragon->Create("sprites\\F.png", Vector2D(0.5f, 0.5f));
		m_achievements.push_back(respectDragon);

		Entity* respectDragonText = GetScene()->AddEntity<Entity>("RespectDragonTextAchievement");
		TextComponent* textcomponentRespectDragon = respectDragonText->AddComponent<TextComponent>();
		textcomponentRespectDragon->Create("Press F to Pay Respects.", "Textures\\emulogic.ttf", 8, Color::white);
		m_achievements.push_back(respectDragonText);
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
				entity->GetTransform().position = Vector2D(x, y);
				entity->GetTransform().scale = Vector2D(2.0f, 2.0f);
				if (interval == 1) {
						SpriteComponent* achieveSprite = entity->GetComponent<SpriteComponent>();
						achieveSprite->SetDepth(201);
						entity->GetComponent<SpriteComponent>()->SetVisible(isVisible);
						if(y >= 600.0f) {
								y = 100.0f;
								x += 100.0f;
						}
						else {
								y -= 10.0f;
								x += 50;
						}
						++interval;
				}
				else {
						TextComponent* achieveText = entity->GetComponent<TextComponent>();
						achieveText->SetDepth(201);
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

