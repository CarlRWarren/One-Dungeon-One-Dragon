#include "enemy.h"
#include "transform.h"
#include"spriteComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "waypointControllerComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "explosion.h"
#include "animationComponent.h"
#include "transformControllerComponent.h"
#include <vector>
#include "missile.h"
#include "formation.h"

void Enemy::Create(const Info & info)
{
	m_info = info;
	SetTag("enemy");
	m_transform.scale = Vector2D(2.0f, 2.0f);
	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(800.0f, 0.3f, false);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> animations;
	if (m_info.type == BEE) animations = { "galaga\\enemy02A.png","galaga\\enemy02B.png" };
	if (m_info.type == BUG) animations = { "galaga\\enemy03A.png","galaga\\enemy03B.png" };
	if (m_info.type == BOSS) animations = { "galaga\\enemy01A.png","galaga\\enemy01B.png" };
	if (m_info.type == BOSS_GREEN) animations = { "galaga\\enemy01C.png","galaga\\enemy01D.png" };

	animationComponent->Create(animations, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create( Vector2D(0.75f, 0.9f));

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("attack", new AttackState(m_stateMachine));
	m_stateMachine->SetState("enter_path");
}

void Enemy::Update()
{
	Entity::Update();
	m_stateMachine->Update();

}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision") {
		if (event.sender->GetTag() == "playerMissile") {
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position, Explosion::eType::ENEMY);

			Event _event;
			_event.eventID ="add_score";
			
			if (m_info.type == Enemy::eType::BEE) _event.variants[0].asInteger = 100;
			if (m_info.type == Enemy::eType::BUG) _event.variants[0].asInteger = 50;
			if (m_info.type == Enemy::eType::BOSS) _event.variants[0].asInteger = 500;
			if (m_info.type == Enemy::eType::BOSS_GREEN) _event.variants[0].asInteger = 750;


			_event.variants[0].type = Variant::INTEGER;
			EventManager::Instance()->SendGameMessage(_event);

			SetState(Entity::DESTROY);
		}
		else if (event.sender->GetTag() == "player") {
			SetState(Entity::DESTROY);
		}

	}
}

void EnterPathState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetEnterPath(m_owner->GetEntity<Enemy>()->m_info.side), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, true);
}

void EnterPathState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete()) {
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");
	}
}

void EnterPathState::Exit()
{
	
}

void EnterFormationState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	std::vector<Vector2D> target = { m_owner->GetEntity<Enemy>()->m_info.target };
	waypointController->Create (target, m_owner->GetEntity<Enemy>()->m_info.speed, 3.0f, false );
}

void EnterFormationState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete()) {
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("idle");
	}
}

void EnterFormationState::Exit()
{
}

void IdleState::Enter()
{
	TransformControllerComponent* controller = m_owner->GetEntity()->AddComponent<TransformControllerComponent>();
	controller->Create(m_owner->GetEntity<Enemy>()->m_info.target, 180.0f,m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);
	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}

void IdleState::Update()
{
	TransformControllerComponent* controller = m_owner->GetEntity()->GetComponent<TransformControllerComponent>();
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f) {
		m_owner->GetEntity()->RemoveComponent(controller);
		m_owner->SetState("attack");
	}
}

void IdleState::Exit()
{

}

void AttackState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetRandomAttackPath(), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, false);
}

void AttackState::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f) {
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create("enemyMissile",m_owner->GetEntity<Enemy>()->GetTransform().position, Vector2D::up, 200.0f);
		m_owner->GetScene()->AddEntity(missile);
		m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
	}

	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete()) {
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_path");
	}
}

void AttackState::Exit()
{
}
