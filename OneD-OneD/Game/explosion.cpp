#include "explosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystem.h"

void Explosion::Create(const Vector2D & position, const eType type)
{
	m_type = type;
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spritecomponent01 = AddComponent<SpriteComponent>();
	spritecomponent01->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames;
	if (m_type == eType::ENEMY) textureNames = { "enemy-explosion01.png","enemy-explosion02.png" ,"enemy-explosion03.png" ,"enemy-explosion04.png","enemy-explosion05.png" };
	if (m_type == eType::PLAYER) textureNames = { "ship-explosion01.png","ship-explosion02.png" ,"ship-explosion03.png" ,"ship-explosion04.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f , AnimationComponent::ePlayback::ONE_TIME_DESTROY);
	if (m_type == eType::ENEMY) AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
	if (m_type == eType::PLAYER) AudioSystem::Instance()->AddSound("explosion", "ship-explosion.wav");
	AudioSystem::Instance()->PlaySound("explosion", false);
}

void Explosion::Update()
{
	Entity::Update();
}
