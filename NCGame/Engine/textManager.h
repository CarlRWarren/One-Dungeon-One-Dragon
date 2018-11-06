#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>
#include "color.h"
#include "text.h"
#include <vector>

class ENGINE_API TextManager : public Singleton<TextManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<TextManager>;

public:
	TextManager() {}
	~TextManager() {}

private:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};

