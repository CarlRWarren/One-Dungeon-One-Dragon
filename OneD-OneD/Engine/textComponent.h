#pragma once
#include "renderComponent.h"
#include "vector2D.h"
#include "color.h"
class Text;

class ENGINE_API TextComponent : public IRenderComponent {
public:
	TextComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& text, const std::string& fontName, int fontSize, const Color& color,  const Vector2D& origin = Vector2D::zero);
	void Destroy();
	void Update();

	void SetText(const std::string& text);
	void SetColor(const Color& color);

	void Draw();
protected:
	Text * m_text = nullptr;
	Vector2D m_origin;

};