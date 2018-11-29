#pragma once
#include "entity.h"
#include "vector2D.h"
#include "state.h"
#include "stateMachine.h"

class PauseScreen : public Entity
{
public:
	PauseScreen(Scene* scene, const ID& id) : Entity(scene, id) {}
	~PauseScreen() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);
	void CreatePrompts();

	void setVisibility(bool isVisible);

protected:
		std::vector<Entity*> m_pausePrompts;
};