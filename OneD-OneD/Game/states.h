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

public:
	int foodCount = 0;

protected:
	float m_timerReset = 600.0f;
	float m_timerRate = 600.0f;

	float m_roomswitch = 0.0f;
};

//this state is for FINAL game over
class GameOverState : public IState
{
public:
	GameOverState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timerRate = 30.0f;
	float m_timerReset = 30.0f;
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
	float m_timerReset = 3.0f;
};

class HugDragonEnding : public IState
{
public:
	HugDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};

class KillDragonEnding : public IState
{
public:
	KillDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};

class RespectEnding : public IState
{
public:
	RespectEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timerRate = 6.0f;
	float m_timerReset = 6.0f;
};

class PoisonDragonEnding : public IState
{
public:
	PoisonDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};

class TrapDragonEnding : public IState
{
public:
	TrapDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};

class TrapYourselfEnding : public IState
{
public:
	TrapYourselfEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};

class StarveDragonEnding : public IState
{
public:
	StarveDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};


class DragonOfferingEnding : public IState
{
public:
	DragonOfferingEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};