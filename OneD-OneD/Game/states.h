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
	int cutscene = 0;
	std::vector<std::string> intro = {"In that land...", "There lived a mighty dragon...", 
		"and a brave knight...", "and a wizard...",
		"the knight asked the wizard","''What is the best way",
		"to defeat the dragon?''",  "the wizard said...",
		"''I dont know the best way,","but I will let you try"," as many times as you need.''",
		"and the wizard cast his spell...",
	};
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
	std::vector<std::string> m_hints = {
   "Stabby Stabby.","You can use more than just WASD",
   "Respect should be given to every kill.","Not even dragons can withstand poison.",
   "Patience is a virtue even for hunters.", "Stories tell of the Right Wizard just before this dungeon.",
   "Spoiled Food can be melted away", "Hugs can cure those blind with anger",
   "Be careful not to trap oneself.", "Ever wonder how many keys were mapped for this game?",
   "If only there was a way to trap the dragon.", "Treasure sooths the soul.", "*stomach rumbling*" };
protected:
	float m_timerReset = 600.0f;
	float m_timerRate = 600.0f;

	float m_hintTimerReset = 60.0f;
	float m_hintTimerRate = 60.0f;
	
	float m_hintVisibilityTimerReset = 5.0f;
	float m_hintVisibilityTimerRate = 5.0f;
	bool m_hintActive = false;

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