#pragma once
#include "state.h"

class GalagaTitleState : public IState
{
public:
	GalagaTitleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	size_t m_credits = 0;
};

class  GalagaEnterStageState : public IState
{
public:
	GalagaEnterStageState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};
class  GalagaGameState : public IState
{
public:
	GalagaGameState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

	void AddCredits(size_t credits) { m_credits += credits; }
	size_t GetCredits() { return m_credits; }

protected:
	size_t m_credits = 0;
};

class  GalagaGameOverState : public IState
{
public:
	GalagaGameOverState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};