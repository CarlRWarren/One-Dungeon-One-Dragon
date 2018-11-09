#pragma once

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#pragma warning(disable:4251)

#include <SDL.h>
#include <SDL_ttf.h>

class TextureManager;

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Initialize();
	void Shutdown();
	void Update();

	bool IsQuit() { return m_isQuit; }
	bool IsDebug() { return m_isDebug; }

	SDL_Window * GetWindow() { return m_window;  }

protected:
	bool m_isQuit = false;
	bool m_isDebug = true;
	SDL_Window * m_window = nullptr;
};
