#pragma once
#include "entity.h"
#include "achievement.h"
class achievementSave : public Entity
{
public:
		void Save();
		void Load();
};