#include "game.h"
#include "engine.h"
#include"inputManager.h"
#include "audioSystem.h"
#include "text.h"
#include "textManager.h"
#include "renderer.h"
#include "textureManager.h"
#include <string>
#include <iostream>
#include "entity.h"
#include "shipControllerComponent.h"
#include "scene.h"
#include "ship.h"
#include "fileSystem.h"
#include "enemy.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "eventReceiver.h"
#include "animationComponent.h"
#include "eventManager.h"
#include "stateMachine.h"
#include "states.h"
Vector2D position(400.0f, 300.0f);
float angle = 0;

Text* text;

Game::~Game()
{
}

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathName("..\\content\\galaga\\");
	EventManager::Instance()->SetGameEventReceiver(this);

	m_scene = new Scene();
	m_stateMachine = new StateMachine(m_scene);

	m_stateMachine->AddState("title", new TitleState(m_stateMachine));
	m_stateMachine->AddState("enter_state", new EnterStageState(m_stateMachine));
	m_stateMachine->AddState("game", new GameState(m_stateMachine));
	m_stateMachine->AddState("game_over", new GameOverState(m_stateMachine));

	m_stateMachine->SetState("title");

	Vector2D size = Renderer::Instance()->GetSize();

	m_running = success;

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();

	

	m_stateMachine->Update();

	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.eventID == "add_score") {
		m_score = m_score + event.variants[0].asInteger;

		Entity* scoreEntity = m_scene->GetEntitiesWithID("score");
		if (scoreEntity) {
			TextComponent* textComponent = scoreEntity->GetComponent<TextComponent>();
			std::string score = std::to_string(m_score);
			while (score.length() < 5) {
				score = "0" + score;
			}
			textComponent->SetText(score);
		}
	}
	if (event.eventID == "player_death") {
		m_stateMachine->SetState("game_over");
	}
}

//The End 