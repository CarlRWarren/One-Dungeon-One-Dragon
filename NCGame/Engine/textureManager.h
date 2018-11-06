#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>
class ENGINE_API TextureManager : public Singleton<TextureManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	SDL_Texture* GetTexture(const std::string& textureName);
public:
	TextureManager() {}
	~TextureManager() {}

private:
	Engine * m_engine;
	std::map<std::string, SDL_Texture*> m_textures;
};

