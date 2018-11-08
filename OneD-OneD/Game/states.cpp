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
	//Adds action for enter key
	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* spritecomponent = entity->AddComponent<SpriteComponent>();
	spritecomponent->Create("Sprites\\MainRoomDesignNoDragon.png", Vector2D(0.5f, 0.5f));
	entity->GetTransform().scale = Vector2D(5.0f, 5.0f);
	spritecomponent->SetDepth(1);



}

void TitleState::Update()
{
	//if pressed moves to next state
	if (InputManager::Instance()->GetActionButton("start")==InputManager::eButtonState::PRESSED) {
		m_owner->SetState("game");
	}
}

void TitleState::Exit()
{
	//destroy entities made in title here
}

void GameState::Enter()
{
	//set up game
}
void GameState::Update()
{
	//stays in here while game is playing
}

void GameState::Exit()
{
	//destroy entities in game state here
}

void GameOverState::Enter()
{
	// Create entities for game over screen
	// add action or timer
}

void GameOverState::Update()
{
	//moves on if they press action or timer runs out
}

void GameOverState::Exit()
{
	//destroy gameover entities here
}
