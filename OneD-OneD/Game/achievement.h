#pragma once
#include "entity.h"
#include "vector2D.h"
#include "state.h"
#include "stateMachine.h"

class Achievement : public Entity
{
public:
	Achievement(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Achievement() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);

	void CreateAchievements();
	void updateAchievement(Entity* completedAchivement);

	void setVisibility(bool isVisible);
protected:
		std::vector<Entity*> m_achievements;
		std::vector<Entity*> m_completedAchievements;
};