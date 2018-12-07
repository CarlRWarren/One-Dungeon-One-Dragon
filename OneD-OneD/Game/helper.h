#pragma once
#include "entity.h"
#include "vector2D.h"
#include "state.h"
#include "stateMachine.h"

class Helper : public Entity
{
public:
	Helper(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Helper() {}

	void Create(const Vector2D& position);
	void Update();


	void OnEvent(const Event & event);
protected:
	bool m_firsttimeclick = true;
	std::vector<std::string> m_hints = {
"Stabby Stabby.","You can use more than just WASD",
"Respect should be given to every kill.", "Not even dragons can withstand poison.",
"Patience is a virtue even for hunters.", "Stories tell of the Right Wizard just before this dungeon.",
"Spoiled Food can be melted away", "Hugs can cure those blind with anger",
"Be careful not to trap oneself.", "Ever wonder how many keys were mapped for this game?",
"If only there was a way to trap the dragon.", "Treasure sooths the soul.", "*stomach rumbling* ... Thats not me." };

	float m_hintTimerReset = 60.0f;
	float m_hintTimerRate = 60.0f;

	float m_hintVisibilityTimerReset = 5.0f;
	float m_hintVisibilityTimerRate = 5.0f;
	bool m_hintActive = false;

	std::vector<std::string> m_idleanimation = { "sprites//skelet_idle_anim_f0.png","sprites//skelet_idle_anim_f1.png" ,"sprites//skelet_idle_anim_f2.png" ,"sprites//skelet_idle_anim_f3.png" };

};