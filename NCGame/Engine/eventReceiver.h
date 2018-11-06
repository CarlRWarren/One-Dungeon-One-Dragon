#pragma once
#include "engine.h"
#include "event.h"

class ENGINE_API EventReceiver {
public: 
	EventReceiver() {}

	virtual void OnEvent(const Event& event) = 0;
};