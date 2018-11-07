#include "shipControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transform.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "missile.h"
#include "audioSystem.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_A, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_D, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("up", SDL_SCANCODE_W, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("down", SDL_SCANCODE_S, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	AudioSystem::Instance()->AddSound("fire", "laser.wav");
}

void ShipControllerComponent::Destroy()
{
}

void ShipControllerComponent::Update()
{
	
	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::left;
	}

	if ((InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::down;
	}
	if ((InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::up;
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::right;
	}

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED) 
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEntitiesWithTag("playerMissile");
		
		if (missiles.size() < 5) {
			Missile* missile = new Missile(m_owner->GetScene());
			missile->Create("playerMissile", m_owner->GetTransform().position, Vector2D::down, 300.0f);
			m_owner->GetScene()->AddEntity(missile);
			AudioSystem::Instance()->PlaySound("fire", false);
		}
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic) {
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}
}

