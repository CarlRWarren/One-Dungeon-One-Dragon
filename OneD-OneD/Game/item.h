#pragma once
#include "entity.h"
#include "vector2D.h"
#include "state.h"
#include "stateMachine.h"

class Item : public Entity
{
public:
	enum eType
	{
		SWORD
	};
public:
	Item(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Item() {}

	void Create(eType type, const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);
protected:
	bool InInventory = false;
};