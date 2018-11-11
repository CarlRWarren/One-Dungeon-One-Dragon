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

class GameState : public IState
{
public:
	GameState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

};

class GameOverState : public IState
{
public:
	GameOverState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};