#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>
#include <fmod.hpp>

class ENGINE_API AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	void Update();

	void AddSound(const std::string& id, const std::string& audioName);
	void PlaySound(const std::string& id, bool loop = false); 
	void RemoveSound(const std::string& id);

public:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};

