#pragma once
#include "state.h"

class TitleState : public IState
{
public:
	TitleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	size_t m_credits = 0;
};

class InitializeState : public IState
{
public:
	InitializeState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

};

class GameState : public IState
{
public:
	GameState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timerReset = 600.0f;
	float m_timerRate = 600.0f;
};

//this state is for FINAL game over
class GameOverState : public IState
{
public:
	GameOverState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class BoreDragonEnding : public IState
{
public:
	BoreDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timerRate = 3.0f;
};

class HugDragonEnding : public IState
{
public:
	HugDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 3.0f;
};

class KillDragonEnding : public IState
{
public:
	KillDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 5.0f;
};

class RespectEnding : public IState
{
public:
	RespectEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timerRate = 5.0f;
};