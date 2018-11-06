#pragma once
#include "engine.h"
#include <string>
#include <map>
class Scene;
class IState;
class Entity;

class ENGINE_API StateMachine
{
public:
	StateMachine(Scene* scene, Entity* entity = nullptr) : m_scene(scene), m_entity(entity) {}
	~StateMachine() {}

	void Update();

	void AddState(const std::string& stateName, IState* state);
	void SetState(const std::string& stateName);

	Scene* GetScene() { return m_scene; }
	Entity* GetEntity() { return m_entity; }
	template<typename T> 
	T* GetEntity() 
	{
		return dynamic_cast<T*>(m_entity);
	}

protected: 
	Scene * m_scene = nullptr;
	Entity * m_entity = nullptr;

	IState* m_state = nullptr;
	std::map<std::string, IState*> m_states;
};