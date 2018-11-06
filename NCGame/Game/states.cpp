#include "states.h"
#include "entity.h"
#include "spriteComponent.h"
#include "scene.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"
#include "formation.h"
#include "timer.h"
#include "textComponent.h"
#include "ship.h"
void TitleState::Enter()
{
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spritecomponent = entity->AddComponent<SpriteComponent>();
	spritecomponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spritecomponent->SetDepth(100);

	Entity* returnText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	returnText->GetTransform().position = Vector2D(200.0f, 500.0f);
	TextComponent* returntextComponent = returnText->AddComponent<TextComponent>();
	returntextComponent->Create("Press Enter To Begin", "emulogic.ttf", 18, Color::white);
	returntextComponent->SetDepth(120);

	Entity* instructions = m_owner->GetScene()->AddEntity<Entity>("Instructions");
	instructions->GetTransform().position = Vector2D(200.0f, 400.0f);
	TextComponent* instructionsComponent = instructions->AddComponent<TextComponent>();
	instructionsComponent->Create("WASD to Move, Space to Fire", "emulogic.ttf", 6, Color::white);
	instructionsComponent->SetDepth(120);

	Ship* ship = m_owner->GetScene()->AddEntity<Ship>("player");
	float x = 400.0f;
	float y = 400.0f;
	ship->Create(Vector2D(x, y));

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start")==InputManager::eButtonState::PRESSED) {
		m_owner->SetState("enter_state");
	}
}

void TitleState::Exit()
{
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("title");
	if (entity1) {
		entity1->SetState(Entity::DESTROY);
	}
	Entity* entity2 = m_owner->GetScene()->GetEntitiesWithID("ReturnText");
	if (entity2) {
		entity2->SetState(Entity::DESTROY);
	}
	Entity* entity3 = m_owner->GetScene()->GetEntitiesWithID("Instructions");
	if (entity3) {
		entity3->SetState(Entity::DESTROY);
	}
}

void EnterStageState::Enter()
{
	Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntitiesWithID("formation"));
	if (formation == nullptr) {
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}
}

void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntitiesWithID("formation"));
	formation->Update();
	m_owner->SetState("game");
}

void EnterStageState::Exit()
{
}


void GameState::Enter()
{
	Entity* textEntity = m_owner->GetScene()->AddEntity<Entity>("score");
	textEntity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textComponent = textEntity->AddComponent<TextComponent>();
	textComponent->Create("00000", "emulogic.ttf", 18, Color::white);
	textComponent->SetDepth(120);
	m_credits = 0;

}
void GameState::Update()
{

}

void GameState::Exit()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntitiesWithID("formation"));
	formation->SetState(Entity::DESTROY);
	for (Entity* enemy : m_owner->GetScene()->GetEntitiesWithTag("enemy")) {
		enemy->SetState(Enemy::DESTROY);
	}

}

void GameOverState::Enter()
{
	Entity* textEntity = m_owner->GetScene()->AddEntity<Entity>("GameOver");
	textEntity->GetTransform().position = Vector2D(300.0f, 200.0f);
	TextComponent* textComponent = textEntity->AddComponent<TextComponent>();
	textComponent->Create("Game Over", "emulogic.ttf", 24, Color::white);
	textComponent->SetDepth(120);
	Entity* returnText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	returnText->GetTransform().position = Vector2D(200.0f, 300.0f);
	TextComponent* returntextComponent = returnText->AddComponent<TextComponent>();
	returntextComponent->Create("Press Space To Return To Title", "emulogic.ttf", 18, Color::white);
	returntextComponent->SetDepth(120);
	Entity* FinalScore = m_owner->GetScene()->AddEntity<Entity>("FinalScore");
	FinalScore->GetTransform().position = Vector2D(300.0f, 400.0f);
	TextComponent* FinalScoreComponent = FinalScore->AddComponent<TextComponent>();
	FinalScoreComponent->Create("Final Score", "emulogic.ttf", 18, Color::white);
	FinalScoreComponent->SetDepth(120);
	Entity* scoretext = m_owner->GetScene()->GetEntitiesWithID("score");
	scoretext->GetTransform().position = Vector2D(300.0f, 450.0f);
}

void GameOverState::Update()
{
	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED) {
		m_owner->SetState("title");
	}
}

void GameOverState::Exit()
{
	Entity* entity1 = m_owner->GetScene()->GetEntitiesWithID("GameOver");
	if (entity1) {
		entity1->SetState(Entity::DESTROY);
	}
	Entity* entity2 = m_owner->GetScene()->GetEntitiesWithID("ReturnText");
	if (entity2) {
		entity2->SetState(Entity::DESTROY);
	}
	Entity* entity3 = m_owner->GetScene()->GetEntitiesWithID("FinalScore");
	if (entity3) {
		entity3->SetState(Entity::DESTROY);
	}
	Entity* entity4 = m_owner->GetScene()->GetEntitiesWithID("score");
	if (entity4) {
		entity4->SetState(Entity::DESTROY);
	}
}
