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
	if (m_type == eType::ENEMY) textureNames = { "galaga\\enemy-explosion01.png","galaga\\enemy-explosion02.png" ,"galaga\\enemy-explosion03.png" ,"galaga\\enemy-explosion04.png","galaga\\enemy-explosion05.png" };
	if (m_type == eType::PLAYER) textureNames = { "galaga\\ship-explosion01.png","galaga\\ship-explosion02.png" ,"galaga\\ship-explosion03.png" ,"galaga\\ship-explosion04.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f , AnimationComponent::ePlayback::ONE_TIME_DESTROY);
	if (m_type == eType::ENEMY) AudioSystem::Instance()->AddSound("explosion", "galaga\\enemy-hit01.wav");
	if (m_type == eType::PLAYER) AudioSystem::Instance()->AddSound("explosion", "galaga\\ship-explosion.wav");
	AudioSystem::Instance()->PlaySound("explosion", false);
}

void Explosion::Update()
{
	Entity::Update();
}
