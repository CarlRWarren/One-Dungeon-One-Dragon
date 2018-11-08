#include "Galagastates.h"
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

//Shows title
void  GalagaTitleState::Enter()
{
	//shows title, instructions, etc.
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spritecomponent = entity->AddComponent<SpriteComponent>();
	spritecomponent->Create("galaga\\galaga.png", Vector2D(0.5f, 0.5f));
	spritecomponent->SetDepth(100);

	Entity* returnText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	returnText->GetTransform().position = Vector2D(200.0f, 500.0f);
	TextComponent* returntextComponent = returnText->AddComponent<TextComponent>();
	returntextComponent->Create("Press Enter To Begin", "galaga\\emulogic.ttf", 18, Color::white);
	returntextComponent->SetDepth(120);

	Entity* instructions = m_owner->GetScene()->AddEntity<Entity>("Instructions");
	instructions->GetTransform().position = Vector2D(200.0f, 400.0f);
	TextComponent* instructionsComponent = instructions->AddComponent<TextComponent>();
	instructionsComponent->Create("WASD to Move, Space to Fire", "galaga\\emulogic.ttf", 6, Color::white);
	instructionsComponent->SetDepth(120);

	Ship* ship = m_owner->GetScene()->AddEntity<Ship>("player");
	float x = 400.0f;
	float y = 400.0f;
	ship->Create(Vector2D(x, y));

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
}

void GalagaTitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start")==InputManager::eButtonState::PRESSED) {
		m_owner->SetState("Galagaenter_state");
	}
}

void GalagaTitleState::Exit()
{
	//Destroys title entities
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

//Start stage
void GalagaEnterStageState::Enter()
{
	//starts stage and creates galaga "formation
	Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntitiesWithID("formation"));
	if (formation == nullptr) {
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}
}

void GalagaEnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntitiesWithID("formation"));
	formation->Update();
	m_owner->SetState("Galagagame");
}

void GalagaEnterStageState::Exit()
{
}

//COntinuation of game
void GalagaGameState::Enter()
{
	//starts tracking score
	Entity* textEntity = m_owner->GetScene()->AddEntity<Entity>("score");
	textEntity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textComponent = textEntity->AddComponent<TextComponent>();
	textComponent->Create("00000", "galaga\\emulogic.ttf", 18, Color::white);
	textComponent->SetDepth(120);
	m_credits = 0;

}
void GalagaGameState::Update()
{
	//stays in here while game is playing
}

void GalagaGameState::Exit()
{
	//destroys entities in game state
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntitiesWithID("formation"));
	formation->SetState(Entity::DESTROY);
	for (Entity* enemy : m_owner->GetScene()->GetEntitiesWithTag("enemy")) {
		enemy->SetState(Enemy::DESTROY);
	}

}

//game over screen
void GalagaGameOverState::Enter()
{
	//Shows text for game over
	Entity* textEntity = m_owner->GetScene()->AddEntity<Entity>("GameOver");
	textEntity->GetTransform().position = Vector2D(300.0f, 200.0f);
	TextComponent* textComponent = textEntity->AddComponent<TextComponent>();
	textComponent->Create("Game Over", "galaga\\emulogic.ttf", 24, Color::white);
	textComponent->SetDepth(120);
	Entity* returnText = m_owner->GetScene()->AddEntity<Entity>("ReturnText");
	returnText->GetTransform().position = Vector2D(200.0f, 300.0f);
	TextComponent* returntextComponent = returnText->AddComponent<TextComponent>();
	returntextComponent->Create("Press Space To Return To Title", "galaga\\emulogic.ttf", 18, Color::white);
	returntextComponent->SetDepth(120);
	Entity* FinalScore = m_owner->GetScene()->AddEntity<Entity>("FinalScore");
	FinalScore->GetTransform().position = Vector2D(300.0f, 400.0f);
	TextComponent* FinalScoreComponent = FinalScore->AddComponent<TextComponent>();
	FinalScoreComponent->Create("Final Score", "galaga\\emulogic.ttf", 18, Color::white);
	FinalScoreComponent->SetDepth(120);
	Entity* scoretext = m_owner->GetScene()->GetEntitiesWithID("score");
	scoretext->GetTransform().position = Vector2D(300.0f, 450.0f);
}

void GalagaGameOverState::Update()
{
	//moves on if they press space
	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED) {
		m_owner->SetState("title");
	}
}

void GalagaGameOverState::Exit()
{
	//destroys gameover entities
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
