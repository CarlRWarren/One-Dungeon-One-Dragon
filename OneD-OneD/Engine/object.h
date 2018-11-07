#pragma once
#include "engine.h"
#include "id.h"

class ENGINE_API Object
{
public:
	Object(const ID& id = ID()) : m_id(id) {}
	~Object() {}

	bool operator == (const Object& object) const { return m_id == object.m_id; }
	bool operator != (const Object& object) const { return m_id != object.m_id; }


	bool operator == (const ID& id) const { return m_id == id; }
	bool operator != (const ID& id) const { return m_id != id; }

protected:
	ID m_id;
};

