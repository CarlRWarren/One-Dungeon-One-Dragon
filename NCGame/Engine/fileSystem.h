#pragma once
#include "engine.h"
#include "singleton.h"
#include <string>

class ENGINE_API FileSystem : public Singleton<FileSystem>
{
public:
	bool Initialize(Engine* engine) { m_engine = engine; return true; }
	void Shutdown() {}
	void Update() {}

	void SetPathName(const std::string& pathname) { m_pathName = pathname; }
	const std::string& GetPathName() { return m_pathName; }
	
public:
	FileSystem() {}
	~FileSystem() {}

private:
	Engine * m_engine;
	std::string m_pathName;
};
