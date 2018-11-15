#pragma once
#include "item.h"
#include "door.h"
#include <vector>

struct Roomx
{
public:
	//texture
	std::string m_texture;
	//items
	std::vector<Item*> itemsInRoom;
	//list of doors
	std::vector<Door*> doors;
};