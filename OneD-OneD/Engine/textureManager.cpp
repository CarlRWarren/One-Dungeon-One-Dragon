#include "textureManager.h"
#include <cassert>
#include "renderer.h"
#include "SDL_image.h"
#include <string>
#include "fileSystem.h"

bool TextureManager::Initialize(Engine* engine)
{
	m_engine = engine;
	return true;
}

void TextureManager::Shutdown()
{
	for (auto texture : m_textures) {
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture * TextureManager::GetTexture(const std::string & textureName)
{
	SDL_Texture* texture = m_textures[textureName];
	if (texture == nullptr) {
		std::string filename = FileSystem::Instance()->GetPathName() + textureName;
		SDL_Surface* surface = IMG_Load(filename.c_str());
		assert(surface);
		texture = SDL_CreateTextureFromSurface(Renderer::Instance()->GetRenderer(), surface);
		SDL_FreeSurface(surface);

		m_textures[textureName] = texture;
	}
	return texture;
}
