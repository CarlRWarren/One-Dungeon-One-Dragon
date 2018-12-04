#pragma once
#include "state.h"
#include <vector>

class CutSceneState : public IState
{
public:
	CutSceneState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
	float m_timer = 4.0f;
	int m_cutscene = 0;
};

class TitleState : public IState
{
public:
	TitleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();

protected:
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

class FeedDragonEnding : public IState
{
public:
	FeedDragonEnding(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
protected:
	float m_timerRate = 10.0f;
	float m_timerReset = 10.0f;
};