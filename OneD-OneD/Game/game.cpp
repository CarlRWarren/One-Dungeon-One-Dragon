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
#include "scene.h"
#include "fileSystem.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "eventReceiver.h"
#include "animationComponent.h"
#include "eventManager.h"
#include "stateMachine.h"
#include "states.h"

Game::~Game()
{
}

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathName("..\\content\\");
	EventManager::Instance()->SetGameEventReceiver(this);

	m_scene = new Scene();
	m_stateMachine = new StateMachine(m_scene);

	//Flips through states in states.cpp
	//can add more later
	m_stateMachine->AddState("title", new TitleState(m_stateMachine));
	m_stateMachine->AddState("intitialize", new InitializeState(m_stateMachine));
	m_stateMachine->AddState("game", new GameState(m_stateMachine));
	m_stateMachine->AddState("game_over", new GameOverState(m_stateMachine));

	m_stateMachine->AddState("BoreDragonEnding", new BoreDragonEnding(m_stateMachine));
	m_stateMachine->AddState("HugDragonEnding", new HugDragonEnding(m_stateMachine));
	m_stateMachine->AddState("KillDragonEnding", new KillDragonEnding(m_stateMachine));
	m_stateMachine->AddState("RespectEnding", new RespectEnding(m_stateMachine));
	m_stateMachine->AddState("PoisionEnding", new PoisonDragonEnding(m_stateMachine));
	m_stateMachine->AddState("TrapYourselfEnding", new TrapYourselfEnding(m_stateMachine));
	m_stateMachine->AddState("TrapDragonEnding", new TrapDragonEnding(m_stateMachine));
	m_stateMachine->AddState("Starvation", new StarveDragonEnding(m_stateMachine));

	m_stateMachine->SetState("title");

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
	//Events, takes event from object if needed
}

//The End 