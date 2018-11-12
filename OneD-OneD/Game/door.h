#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Door : public Entity
{
public:
	Door(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Door() {}

	void Create(const Vector2D& position, bool isFlipped);

	void OnEvent(const Event & event);

public:
	std::vector<std::string> m_idleanimation = { "textures//leftdoor1.png", "textures//leftdoor2.png", "textures//leftdoor3.png", "textures//leftdoor4.png", "textures//leftdoor5.png" };
};