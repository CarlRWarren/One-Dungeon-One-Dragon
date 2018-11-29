#include "PauseScreen.h"
#include "transform.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "hero.h"
#include "inputManager.h"

void PauseScreen::Create(const Vector2D & position)
{
	SpriteComponent* achievementBackgroundSpriteComponent = AddComponent<SpriteComponent>();
	achievementBackgroundSpriteComponent->Create("Sprites\\AchievementBackground.png", Vector2D(0.5f, 0.5f));
	GetTransform().scale = Vector2D(1.0f, 1.0f);
	achievementBackgroundSpriteComponent->SetDepth(200);
	achievementBackgroundSpriteComponent->SetVisible(false);

	m_transform.position = position;
	SetTag("pauseScreen");
		
	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(1.0f,1.0f));
	CreatePrompts();
}

void PauseScreen::Update()
{
	Entity::Update();
}


void PauseScreen::OnEvent(const Event & event)
{
 	
}

void PauseScreen::CreatePrompts()
{
		//achievments
		Entity* PausePrompt1 = GetScene()->AddEntity<Entity>("PausePrompt1");
		SpriteComponent* PausePromptSprite1 = PausePrompt1->AddComponent<SpriteComponent>();
		PausePromptSprite1->Create("sprites\\wall_side_top_left.png", Vector2D(0.5f, 0.5f));
		m_pausePrompts.push_back(PausePrompt1);

		Entity* PausePromptText1 = GetScene()->AddEntity<Entity>("PausePromptText1");
		TextComponent* PausePromptTextComponent1 = PausePromptText1->AddComponent<TextComponent>();
		PausePromptTextComponent1->Create("Press WASD to move", "Textures\\emulogic.ttf", 8, Color::white);
		m_pausePrompts.push_back(PausePromptText1);

		Entity* PausePrompt2 = GetScene()->AddEntity<Entity>("PausePrompt2");
		SpriteComponent* PausePromptSprite2 = PausePrompt2->AddComponent<SpriteComponent>();
		PausePromptSprite2->Create("sprites\\wall_side_top_left.png", Vector2D(0.5f, 0.5f));
		m_pausePrompts.push_back(PausePrompt2);

		Entity* PausePromptTExt2 = GetScene()->AddEntity<Entity>("PausePromptText2");
		TextComponent* PausePromptTExtComponent2 = PausePromptTExt2->AddComponent<TextComponent>();
		PausePromptTExtComponent2->Create("Press Q to View Achievements", "Textures\\emulogic.ttf", 8, Color::white);
		m_pausePrompts.push_back(PausePromptTExt2);

		Entity* PausePrompt3 = GetScene()->AddEntity<Entity>("PausePrompt3");
		SpriteComponent* PausePromptSprite3 = PausePrompt3->AddComponent<SpriteComponent>();
		PausePromptSprite3->Create("sprites\\wall_side_top_left.png", Vector2D(0.5f, 0.5f));
		m_pausePrompts.push_back(PausePrompt3);

		Entity* PausePromptText3 = GetScene()->AddEntity<Entity>("PausePromptText3");
		TextComponent* PausePromptTextComponent3 = PausePromptText3->AddComponent<TextComponent>();
		PausePromptTextComponent3->Create("Press E to use item", "Textures\\emulogic.ttf", 8, Color::white);
		m_pausePrompts.push_back(PausePromptText3);

		Entity* PausePrompt4 = GetScene()->AddEntity<Entity>("PausePrompt4");
		SpriteComponent* PausePromptsprite4 = PausePrompt4->AddComponent<SpriteComponent>();
		PausePromptsprite4->Create("sprites\\wall_side_top_left.png", Vector2D(0.5f, 0.5f));
		m_pausePrompts.push_back(PausePrompt4);

		Entity* PausePromptText4 = GetScene()->AddEntity<Entity>("PausePromptText4");
		TextComponent* PausePromptTextComponent4 = PausePromptText4->AddComponent<TextComponent>();
		PausePromptTextComponent4->Create("Press Space to pick up or drop items", "Textures\\emulogic.ttf", 8, Color::white);
		m_pausePrompts.push_back(PausePromptText4);

		Entity* PausePrompt5 = GetScene()->AddEntity<Entity>("PausePrompt5");
		SpriteComponent* PausePromptSprite5 = PausePrompt5->AddComponent<SpriteComponent>();
		PausePromptSprite5->Create("sprites\\wall_side_top_left.png", Vector2D(0.5f, 0.5f));
		m_pausePrompts.push_back(PausePrompt5);

		Entity* PausePromptText5 = GetScene()->AddEntity<Entity>("PausePromptText5");
		TextComponent* PausePromptTextComponent5 = PausePromptText5->AddComponent<TextComponent>();
		PausePromptTextComponent5->Create("Press ESC to leave game", "Textures\\emulogic.ttf", 8, Color::white);
		m_pausePrompts.push_back(PausePromptText5);

		Entity* PausePrompt6 = GetScene()->AddEntity<Entity>("PausePrompt6");
		SpriteComponent* PausePrompt6sprite = PausePrompt6->AddComponent<SpriteComponent>();
		PausePrompt6sprite->Create("sprites\\wall_side_top_left.png", Vector2D(0.5f, 0.5f));
		m_pausePrompts.push_back(PausePrompt6);

		Entity* PausePromptText6 = GetScene()->AddEntity<Entity>("PausePromptText6");
		TextComponent* PausePromptTextComponent6 = PausePromptText6->AddComponent<TextComponent>();
		PausePromptTextComponent6->Create("Find ALL the achievements to win", "Textures\\emulogic.ttf", 8, Color::white);
		m_pausePrompts.push_back(PausePromptText6);

}

void PauseScreen::setVisibility(bool isVisible)
{
		int interval = 1;
		float x = 100.0f;
		float y = 100.0f;
		GetComponent<SpriteComponent>()->SetVisible(isVisible);

		for (Entity* entity : m_pausePrompts) {
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

