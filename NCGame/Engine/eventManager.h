#pragma once
#include "singleton.h"
#include "event.h"
#include "eventReceiver.h"
class ENGINE_API EventManager : public Singleton<EventManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SendMessage(const Event& event);
	void SendGameMessage(const Event& event);
	void SetGameEventReceiver(EventReceiver* eventReceiver) { m_gameEventReceiver = eventReceiver; }
	

protected:
	friend Singleton<EventManager>;
protected:
	Engine * m_engine = nullptr;
	EventReceiver* m_gameEventReceiver = nullptr;

};