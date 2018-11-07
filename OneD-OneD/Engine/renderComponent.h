#pragma once

#include "component.h"

class ENGINE_API IRenderComponent : public Component
{
public:
	IRenderComponent(Entity* owner) : Component(owner) {}

	virtual void Draw() = 0;

	void SetVisible(bool visible = true) { m_visible = visible; }
	bool GetVisible() const { return m_visible; }

	void SetDepth(int depth = 0) { m_depth = depth; }
	int GetDepth() const { return m_depth; }

	static bool CompareDepth(IRenderComponent* renderComponent1, IRenderComponent* renderComponent2)
	{
		return (renderComponent1->GetDepth() < renderComponent2->GetDepth());
	}

protected:
	bool m_visible = true;
	int m_depth = 0;
};