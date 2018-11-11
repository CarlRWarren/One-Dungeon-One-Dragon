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

	bool GetHugged() { return m_hugged; }
	bool GetIdle() { return m_idled; }

	void SetItemHeld(ID itemHeld) { m_itemHeld = itemHeld; }
	ID GetItemHeld() { return m_itemHeld; }

protected:
	float m_timerReset = 600.0f;
	float m_timerRate = 600.0f;
	bool m_isFlipped = false;
	bool m_hugged = false;
	bool m_idled;

	std::vector<std::string> m_idleanimation = { "sprites//knight_m_run_anim_f0.png","sprites//knight_m_run_anim_f1.png" ,"sprites//knight_m_run_anim_f2.png" ,"sprites//knight_m_run_anim_f3.png" };
	std::vector<std::string> m_runanimation  = { "sprites//knight_m_idle_anim_f0.png","sprites//knight_m_idle_anim_f1.png" ,"sprites//knight_m_idle_anim_f2.png" ,"sprites//knight_m_idle_anim_f3.png" };

	ID m_itemHeld = "";
};