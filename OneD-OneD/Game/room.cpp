#include "room.h"
#include "door.h"
#include "spriteComponent.h"

void Room::SetRooms()
{
	Roomx* room1= new Roomx();
	room1->m_texture = "Sprites\\MainRoomDesign.png";
	/*Item* item = GetScene()->AddEntity<Item>("sword");
	item->Create(Item::eType::SWORD, Vector2D(200.0f, 200.0f));
	room1->itemsInRoom.push_back(item);*/
	Door* topLeftDoor = GetScene()->AddEntity<Door>("topLeftDoor");
	topLeftDoor->Create(Vector2D(5.0f, 280.0f), false);
	topLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	room1->doors.push_back(topLeftDoor);
	m_rooms.push_back(room1);

	Roomx* room2 = new Roomx();
	room2->m_texture = "Sprites\\Room2Design.png";
	Item* item2 = (Item*)GetScene()->GetEntitiesWithID("sword");
	room2->itemsInRoom.push_back(item2);
	Door* door = GetScene()->AddEntity<Door>("room2door");
	door->Create(Vector2D(800.0f, 680.0f), true);
	door->GetComponent<SpriteComponent>()->SetDepth(2);
	room2->doors.push_back(door);
	m_rooms.push_back(room2);

	ChangeRoom();


}

 void Room::ChangeRoom(int roomNum)
{
	//set current one equal to the room you're entering
	m_currentRoom = m_rooms[roomNum];
	//load texture
	Entity* Background = GetScene()->AddEntity<Entity>("background");
	Background->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* backgroundSpriteComponent = Background->AddComponent<SpriteComponent>();
	backgroundSpriteComponent->Create(m_currentRoom->m_texture, Vector2D(0.5f, 0.5f));
	Background->GetTransform().scale = Vector2D(5.0f, 5.0f);
	backgroundSpriteComponent->SetDepth(1);

	//load items in room currently
	for (Item* item : m_currentRoom->itemsInRoom)
	{
		item->GetComponent<SpriteComponent>()->SetVisible();
	}

	//place doors in proper location
	for (Door* door : m_currentRoom->doors)
	{
		door->GetComponent<SpriteComponent>()->SetVisible();
	}

	for (Roomx* room : m_rooms)
	{
		if (room != m_currentRoom)
		{
			for (Door* door : room->doors)
			{
				door->GetComponent<SpriteComponent>()->SetVisible(false);
			}
			for (Item* item : room->itemsInRoom)
			{
				item->GetComponent<SpriteComponent>()->SetVisible(false);
			}
		}

	
	}
}

 void Room::Update()
 {
		 if (m_currentRoom->itemsInRoom.size() > 0) {
				for (Item* item : m_currentRoom->itemsInRoom) {
						if (item->GetTransform().position == Vector2D(50.0f, 25.0f) && item->GetComponent<SpriteComponent>()->GetVisible() == true) {
								m_currentRoom->itemsInRoom.remove(item);
								break;
						}
				}
		 }

		 Item* item2 = (Item*)GetScene()->GetEntitiesWithID("sword");
		 if (item2->GetTransform().position != Vector2D(50.0f, 25.0f) && item2->GetComponent<SpriteComponent>()->GetVisible() == true) {
				 bool exists = false;
				 for (Item* item : m_currentRoom->itemsInRoom) {
						 if (item == item2) {
								 exists = true;
						 }
				 }
				 if (!exists) {
						 m_currentRoom->itemsInRoom.push_back(item2);
				 }
		 }

 }


