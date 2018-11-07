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

class EnterStageState : public IState
{
public:
	EnterStageState(StateMachine* owner) : IState(owner) {}

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

	void AddCredits(size_t credits) { m_credits += credits; }
	size_t GetCredits() { return m_credits; }

protected:
	size_t m_credits = 0;
};

class GameOverState : public IState
{
public:
	GameOverState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};