#pragma once
#include "object.h"
#include "component.h"
#include <vector>
#include "assert.h"
#include "scene.h"
#include "transform.h"
#include "event.h"
#include "eventReceiver.h"
class ENGINE_API Entity : public Object, public EventReceiver
{
public:
	enum eState
	{
		INACTIVE,
		ACTIVE,
		DESTROY
	};
public:
	Entity(Scene* scene, const ID& id = ID()) : m_scene(scene), Object(id) {}
	virtual~Entity() {} 

	virtual void Destroy();
	virtual void Update();
	virtual void Draw();

	virtual void OnEvent(const Event& event) {}

	template <typename T>
	T* AddComponent() 
	{
		T* component = new T(this);
		assert(dynamic_cast<Component*>(component));
		m_components.push_back(component);
		return component;
	}

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components){
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}
		return component;
	}

	bool Intersects(Entity* otherEntity);

	Scene* GetScene() { return m_scene; }
	Transform& GetTransform() { return m_transform; }

	eState GetState() { return m_state; }
	void SetState(eState state) { m_state = state; }

	void SetTag(const ID& tag) { m_tag = tag; }
	const ID& GetTag() { return m_tag; }


protected:
	Transform m_transform;
	Scene * m_scene;
	ID m_tag;
	std::vector<Component*> m_components;
	eState m_state = ACTIVE;
};

