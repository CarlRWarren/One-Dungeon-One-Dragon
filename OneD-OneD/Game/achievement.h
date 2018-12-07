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

	void Save();
	void Load();

	void OnEvent(const Event & event);

	void CreateAchievements();
	void updateAchievement(std::string completedAchivement);

	void setVisibility(bool isVisible);

	int GetNumAchievments() {
		return (int)m_achievements.size();
	}
	int GetNumAchievmentsCompleted() {
		return (int)m_completedAchievementsTags.size();
	}
	//trims for saving/loading
	inline std::string trim(std::string& str)
	{
		str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
		str.erase(str.find_last_not_of(' ') + 1);         //surfixing spaces
		return str;
	}
protected:
		std::vector<Entity*> m_achievements;
		std::vector<std::string> m_completedAchievementsTags;
};