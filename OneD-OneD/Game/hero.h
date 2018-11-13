#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"
#include "timer.h"

class Hero : public Entity
{
public:
	Hero(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Hero() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);

	void SetItemHeld(ID* itemHeld) { m_itemHeld = itemHeld; }
	ID* GetItemHeld() { return m_itemHeld; }

protected:
	bool m_isFlipped = false;
	std::vector<std::string> m_runanimation = { "sprites//knight_m_run_anim_f0.png","sprites//knight_m_run_anim_f1.png" ,"sprites//knight_m_run_anim_f2.png" ,"sprites//knight_m_run_anim_f3.png" };
	std::vector<std::string> m_idleanimation = { "sprites//knight_m_idle_anim_f0.png","sprites//knight_m_idle_anim_f1.png" ,"sprites//knight_m_idle_anim_f2.png" ,"sprites//knight_m_idle_anim_f3.png" };

	ID* m_itemHeld = new ID("No Items");
};