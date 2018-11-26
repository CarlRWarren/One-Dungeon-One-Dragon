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

	void Update();

	struct Roomx
	{
	public:
		//texture
		std::string m_texture;
		//items
		std::list<Item*> itemsInRoom;
		//list of doors
		std::vector<Door*> doors;
		//list of possible Fountains
		std::vector<Fountain*> fountains;
	};

public:
	std::vector<Roomx*> m_rooms;
	int m_roomIndex = 0;
	Roomx* m_currentRoom=nullptr;
};

