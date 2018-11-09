#pragma once
#include "entity.h"
#include "vector2D.h"
#include "id.h"

class Hero : public Entity
{
public:
	Hero(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Hero() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event & event);
<<<<<<< HEAD
	bool GetHugged() { return m_hugged; }

protected:
	bool m_isFlipped = false;
	bool m_hasItem = false;

	bool m_hugged = false;
=======
protected:
	bool m_isFlipped = false;
>>>>>>> fae5f329ad87e9a833e3cfd4ad7c92730c4d115c
};