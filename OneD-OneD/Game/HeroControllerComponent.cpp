#include "HeroControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transform.h"
#include "timer.h"
#include "kinematicComponent.h"
#include "audioSystem.h"

void HeroControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_A, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_D, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("up", SDL_SCANCODE_W, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("down", SDL_SCANCODE_S, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("pick_up", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

}

void HeroControllerComponent::Destroy()
{
}

void HeroControllerComponent::Update()
{
	
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
<<<<<<< HEAD
		m_owner->GetTransform().position += Vector2D::left;
=======
		m_owner->GetTransform().position += Vector2D::left * m_speed;
>>>>>>> fae5f329ad87e9a833e3cfd4ad7c92730c4d115c
	}

	if ((InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD))
	{
<<<<<<< HEAD
		m_owner->GetTransform().position += Vector2D::down;
=======
		m_owner->GetTransform().position += Vector2D::down* m_speed;
>>>>>>> fae5f329ad87e9a833e3cfd4ad7c92730c4d115c
	}
	if ((InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD))
	{
<<<<<<< HEAD
		m_owner->GetTransform().position += Vector2D::up;
=======
		m_owner->GetTransform().position += Vector2D::up* m_speed;
>>>>>>> fae5f329ad87e9a833e3cfd4ad7c92730c4d115c
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
<<<<<<< HEAD
		m_owner->GetTransform().position += Vector2D::right;
=======
		m_owner->GetTransform().position += Vector2D::right* m_speed;
>>>>>>> fae5f329ad87e9a833e3cfd4ad7c92730c4d115c
	}
	
	if ((InputManager::Instance()->GetActionButton("pick_up") == InputManager::eButtonState::PRESSED))	{
		//Item pickup
	}
}

