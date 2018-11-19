#include "GalagaGame.h"
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
#include "Galagastates.h"

GalagaGame::~GalagaGame()
{
}

bool GalagaGame::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathName("..\\content\\");
	EventManager::Instance()->SetGameEventReceiver(this);

	m_scene = new Scene();
	m_stateMachine = new StateMachine(m_scene);

	//Flips through states in states.cpp
	m_stateMachine->AddState("Galagatitle", new  GalagaTitleState(m_stateMachine));
	m_stateMachine->AddState("Galagaenter_state", new  GalagaEnterStageState(m_stateMachine));
	m_stateMachine->AddState("Galagagame", new  GalagaGameState(m_stateMachine));
	m_stateMachine->AddState("Galagagame_over", new  GalagaGameOverState(m_stateMachine));

	m_stateMachine->SetState("Galagatitle");

	m_running = success;

	return success;
}

void GalagaGame::Shutdown()
{
	m_engine->Shutdown();
}

void GalagaGame::Update()
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

//Events, takes event from object and updates score
void GalagaGame::OnEvent(const Event & event)
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
		m_stateMachine->SetState("Galagagame_over");
	}
}

//The End 