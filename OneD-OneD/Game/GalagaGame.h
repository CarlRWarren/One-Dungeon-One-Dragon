#pragma once
#include "eventReceiver.h"

class Engine;
class Scene;
class StateMachine;

class GalagaGame : public EventReceiver
{
public:
	GalagaGame(Engine* engine) : m_engine(engine) {}
	~GalagaGame();

	bool Initialize();
	void Shutdown();
	void Update();

	void OnEvent(const Event& event);
	size_t GetScore() { return m_score; }

	bool Run() { return m_running; }
protected:
	size_t m_score = 0;
	bool m_running = false;
	Engine* m_engine = nullptr;
	Scene* m_scene = nullptr;
	StateMachine* m_stateMachine = nullptr;
};

