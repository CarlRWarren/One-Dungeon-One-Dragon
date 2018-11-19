#pragma once
#include "roomx.h"
class Room : public Entity
{

public:
	Room(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Room() {};
	
	//Initialize and create all the initial rooms
	void SetRooms();
	//changes room based on passed index defaults to 0 index which should be the main room
	void ChangeRoom(int roomNum = 0);

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

public:
	std::vector<Roomx*> m_rooms;
	Roomx* m_currentRoom=nullptr;
};

