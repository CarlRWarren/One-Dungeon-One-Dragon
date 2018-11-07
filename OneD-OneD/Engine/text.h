#pragma once
#include <string>
#include "color.h"
#include "vector2d.h"
#include "texture.h"

class ENGINE_API Text
{
public:
	Text();
	~Text();

	void Create(const std::string& text, const std::string& fontName, int fontSize, const Color& color);

	void Draw(const Vector2D& position, const Vector2D& origin = Vector2D::zero, const Vector2D& scale = Vector2D::one, float angle = 0);

	void SetText(const std::string& text);
	void SetText(const std::string& text,const Color& color);
	void SetColor(Color color);
	void SetSize(int size);

protected:
	void CreateTexture();
protected:
	Texture * m_texture = nullptr;
	TTF_Font * m_font = nullptr;
	std::string m_text;
	Color m_color;
	int m_size;
};

