#include "room.h"
#include "door.h"
#include "Fountain.h"
#include "spriteComponent.h"
#include "animationComponent.h"

void Room::SetRooms()
{
	Entity* Background = GetScene()->AddEntity<Entity>("background");
	SpriteComponent* backgroundSpriteComponent = Background->AddComponent<SpriteComponent>();

	Roomx* room1= new Roomx();
	room1->m_texture = "Sprites\\MainRoomDesign.png";
	Door* topLeftDoor = GetScene()->AddEntity<Door>("topLeftDoor");
	topLeftDoor->Create(Vector2D(5.0f, 280.0f), false);
	topLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	room1->doors.push_back(topLeftDoor);
	Door* bottomLeftDoor = GetScene()->AddEntity<Door>("bottomLeftDoor");
	bottomLeftDoor->Create(Vector2D(5.0f, 518.0f), false);
	bottomLeftDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	room1->doors.push_back(bottomLeftDoor);
	Door* topRightDoor = GetScene()->AddEntity<Door>("topRightDoor");
	topRightDoor->Create(Vector2D(800.0f, 280.0f), true);
	topRightDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	room1->doors.push_back(topRightDoor);
	Door* bottomRightDoor = GetScene()->AddEntity<Door>("bottomRightDoor");
	bottomRightDoor->Create(Vector2D(800.0f, 518.0f), true);
	bottomRightDoor->GetComponent<SpriteComponent>()->SetDepth(2);
	room1->doors.push_back(bottomRightDoor);
	m_rooms.push_back(room1);

	Roomx* room2 = new Roomx();
	room2->m_texture = "Sprites\\Room2Design.png";
	Item* item2 = (Item*)GetScene()->GetEntitiesWithID("sword");
	room2->itemsInRoom.push_back(item2);
	Door* door = GetScene()->AddEntity<Door>("room2door");
	door->Create(Vector2D(800.0f, 680.0f), true);
	door->GetComponent<SpriteComponent>()->SetDepth(2);
	room2->doors.push_back(door);
	Fountain* leftFountain = GetScene()->AddEntity<Fountain>("leftLavaFountain");
	leftFountain->Create(Vector2D(360.0f, 75.0f), 1);
	leftFountain->GetComponent<SpriteComponent>()->SetDepth(2);
	room2->fountains.push_back(leftFountain);
	Fountain* rightFountain = GetScene()->AddEntity<Fountain>("rightLavaFountain");
	rightFountain->Create(Vector2D(440.0f, 75.0f), 1);
	rightFountain->GetComponent<SpriteComponent>()->SetDepth(2);
	room2->fountains.push_back(rightFountain);
	m_rooms.push_back(room2);

	Roomx* room3 = new Roomx();
	room3->m_texture = "Sprites\\Room3Design.png";
	Item* item3 = (Item*)GetScene()->GetEntitiesWithID("poison");
	room3->itemsInRoom.push_back(item3);
	Door* door3 = GetScene()->AddEntity<Door>("room3door");
	door3->Create(Vector2D(800.0f, 200.0f), true);
	door3->GetComponent<SpriteComponent>()->SetDepth(2);
	room3->doors.push_back(door3);
	m_rooms.push_back(room3);

	Roomx* room4 = new Roomx();
	room4->m_texture = "Sprites\\Room4Design.png";
	Item* steak1 = (Item*)GetScene()->GetEntitiesWithID("food");
	room4->itemsInRoom.push_back(steak1);
	Door* door4_1 = GetScene()->AddEntity<Door>("room4_1door");
	door4_1->Create(Vector2D(5.0f, 680.0f), false);
	door4_1->GetComponent<SpriteComponent>()->SetDepth(2);
	room4->doors.push_back(door4_1);
	Door* door4_2 = GetScene()->AddEntity<Door>("room4_2door");
	door4_2->Create(Vector2D(800.0f, 680.0f), true);
	door4_2->GetComponent<SpriteComponent>()->SetDepth(2);
	room4->doors.push_back(door4_2);
	Door* door4_3 = GetScene()->AddEntity<Door>("room4_3door");
	door4_3->Create(Vector2D(440.0f, 40.0f), true,true);
	door4_3->GetComponent<SpriteComponent>()->SetDepth(2);
	room4->doors.push_back(door4_3);
	m_rooms.push_back(room4);

	Roomx* room5 = new Roomx();
	room5->m_texture = "Sprites\\Room5Design.png";
	Door* door5_1 = GetScene()->AddEntity<Door>("room5_1door");
	door5_1->Create(Vector2D(5.0f, 200.0f), false);
	door5_1->GetComponent<SpriteComponent>()->SetDepth(2);
	room5->doors.push_back(door5_1);
	Door* door5_2 = GetScene()->AddEntity<Door>("room5_2door");
	door5_2->Create(Vector2D(800.0f, 600.0f), true);
	door5_2->GetComponent<SpriteComponent>()->SetDepth(2);
	room5->doors.push_back(door5_2);
	Door* door5_3 = GetScene()->AddEntity<Door>("room5_3door");
	door5_3->Create(Vector2D(440.0f, 800.0f), true);
	door5_3->GetComponent<SpriteComponent>()->SetDepth(2);
	room5->doors.push_back(door5_3);
	m_rooms.push_back(room5);

	ChangeRoom();


}

 void Room::ChangeRoom(int roomNum)
{
	//set current one equal to the room you're entering
	m_roomIndex = roomNum;
	m_currentRoom = m_rooms[m_roomIndex];
	//load texture
	Entity* Background = GetScene()->GetEntitiesWithID("background");
	Background->GetTransform().position = Vector2D(400.0f, 400.0f);
	SpriteComponent* backgroundSpriteComponent = Background->GetComponent<SpriteComponent>();
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
		 Item* item3 = (Item*)GetScene()->GetEntitiesWithID("poison");
		 if (item3->GetTransform().position != Vector2D(50.0f, 25.0f) && item3->GetComponent<SpriteComponent>()->GetVisible() == true) {
			 bool exists = false;
			 for (Item* item1 : m_currentRoom->itemsInRoom) {
				 if (item1 == item3) {
					 exists = true;
				 }
			 }
			 if (!exists) {
				 m_currentRoom->itemsInRoom.push_back(item3);
			 }
		 }
		 Item* item4 = (Item*)GetScene()->GetEntitiesWithID("food");
		 if (item4->GetTransform().position != Vector2D(50.0f, 25.0f) && item4->GetComponent<SpriteComponent>()->GetVisible() == true) {
			 bool exists = false;
			 for (Item* item1 : m_currentRoom->itemsInRoom) {
				 if (item1 == item4) {
					 exists = true;
				 }
			 }
			 if (!exists) {
				 m_currentRoom->itemsInRoom.push_back(item4);
			 }
		 }

 }


