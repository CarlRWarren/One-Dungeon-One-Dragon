#include "Helper.h"
#include "transform.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "hero.h"
#include "inputManager.h"
#include "textComponent.h"
#include "animationComponent.h"

void Helper::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(5.0f, 5.0f);
	SetTag("helper");

	SpriteComponent* spritecomponent01 = AddComponent<SpriteComponent>();
	spritecomponent01->Create("", Vector2D(0.5f, 0.5f));
	spritecomponent01->SetDepth(2);
	spritecomponent01->SetVisible(false);

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	animationComponent->Create(m_idleanimation, 1.0f / 5.0f, AnimationComponent::ePlayback::LOOP);
	
	int random = rand() % m_hints.size();
	Entity* hintText = GetScene()->AddEntity<Entity>("hintText");
	hintText->GetTransform().position = Vector2D(60.0f, 650.0f);
	TextComponent* hintTextComponent = hintText->AddComponent<TextComponent>();
	hintTextComponent->Create(m_hints[random], "Textures\\emulogic.ttf", 12, Color::white);
	hintTextComponent->SetDepth(120);
	hintTextComponent->SetVisible(false);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(1.0f,1.0f));
}

void Helper::Update()
{
	Entity::Update();

	float dt = Timer::Instance()->DeltaTime();

	if (m_hintTimerRate > 0.0f)
	{
		m_hintTimerRate = m_hintTimerRate - dt;
	}

	if (m_hintTimerRate > 0.0f)
	{
		m_hintTimerRate = m_hintTimerRate - dt;
	}

	Entity* eHero = GetScene()->GetEntitiesWithID("hero");
	if (InputManager::Instance()->GetActionButton("use") == InputManager::eButtonState::PRESSED && eHero->GetComponent<AABBComponent>()->Intersects(GetComponent<AABBComponent>()) && GetComponent<SpriteComponent>()->GetVisible() == true)
	{
		Entity* eHint = GetScene()->GetEntitiesWithID("hintText");
		m_hintActive = true;
		eHint->GetComponent<TextComponent>()->SetVisible(true);

		if (m_firsttimeclick){
			m_firsttimeclick = false;
			std::string text = "Hi there! I died but you can ask me if you need help";
			eHint->GetComponent<TextComponent>()->SetText(text);
			eHint->GetTransform().position = Vector2D(650.0f - (text.size() * 10), 75.0f);
		}
		else if (m_hintTimerRate <= 0.0f) {

			int random = rand() % m_hints.size();
			std::string text = m_hints[random];
			eHint->GetComponent<TextComponent>()->SetText(text);
			eHint->GetTransform().position = Vector2D(650.0f - (text.size() * 10), 75.0f);
		}
		else {
			std::string text = "Didn't we just talk? Go look around more";
			eHint->GetComponent<TextComponent>()->SetText(text);
			eHint->GetTransform().position = Vector2D(650.0f - (text.size() * 10), 75.0f);
		}
	}
	if (m_hintActive)
	{
		m_hintVisibilityTimerRate = m_hintVisibilityTimerRate - dt;
		if (m_hintVisibilityTimerRate <= 0.0f)
		{
			m_hintVisibilityTimerRate = m_hintVisibilityTimerReset;
			m_hintTimerRate = m_hintTimerReset;
			m_hintActive = false;
			Entity* eHint = GetScene()->GetEntitiesWithID("hintText");
			eHint->GetComponent<TextComponent>()->SetVisible(false);
		}
	}
}


void Helper::OnEvent(const Event & event)
{
	if (GetComponent<SpriteComponent>()->GetVisible() == true) {
		if (event.eventID == "collision") {
			if (event.sender->GetTag() == "hero") {
				if (InputManager::Instance()->GetActionButton("pick_up") == InputManager::eButtonState::PRESSED) {
					Entity* hero = m_scene->GetEntitiesWithID("hero");
					Hero* ehero = (Hero*)hero;
					ID* id = new ID(m_id.GetIDString());
				}
			}
		}
	}
}

