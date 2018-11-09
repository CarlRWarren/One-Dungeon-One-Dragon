#include "spriteComponent.h"
#include "transform.h"
#include "entity.h"
#include "renderer.h"
void SpriteComponent::Create(const std::string & textureName, const Vector2D& origin, bool IsFlipped)
{
	if (textureName != "") {
		m_texture = new Texture;
		m_texture->SetFlip(IsFlipped);
		m_texture->Create(textureName);
	}

	m_origin = origin;
}

void SpriteComponent::Destroy()
{
	//
}

void SpriteComponent::Update()
{
	//
}

void SpriteComponent::Draw()
{
	if (m_texture) {
		Transform transform = m_owner->GetTransform();
		m_texture->Draw(transform.position, m_origin, transform.scale, transform.rotation);
	}
}
