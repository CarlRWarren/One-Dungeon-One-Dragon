#include "formation.h"
#include "timer.h"
void Formation::Create()
{
	m_enterPaths[0] = { Vector2D(100.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };
	m_enterPaths[1] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
	m_enterPaths[2] = { Vector2D(-64.0f, 600.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };
	m_enterPaths[3] = { Vector2D(800.0f, 600.0f), Vector2D(500.0f, 300.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f) };
	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(100.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 600.0f) });
	m_attackPaths.push_back({ Vector2D(200.0f, 400.0f), Vector2D(400.0f, 300.0f), Vector2D(300.0f, 200.0f), Vector2D(200.0f, 300.0f), Vector2D(100.0f, 600.0f) });
	m_attackPaths.push_back({ Vector2D(300.0f, 400.0f), Vector2D(500.0f, 300.0f), Vector2D(400.0f, 200.0f), Vector2D(300.0f, 300.0f), Vector2D(400.0f, 600.0f) });
	m_attackPaths.push_back({ Vector2D(400.0f, 400.0f), Vector2D(200.0f, 300.0f), Vector2D(300.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(300.0f, 600.0f) });
	m_attackPaths.push_back({ Vector2D(500.0f, 400.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(300.0f, 300.0f), Vector2D(100.0f, 600.0f) });

	m_formation =
	{ 
	{ { Enemy::BEE, Enemy::TOP_LEFT, 300.0f, Vector2D(100.0f, 80.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::BOTTOM_LEFT, 300.0f, Vector2D(140.0f, 80.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::TOP_LEFT, 300.0f, Vector2D(100.0f, 120.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::BOTTOM_LEFT, 300.0f, Vector2D(140.0f, 120.0f), this }, 1.05f, false },

	{ { Enemy::BUG, Enemy::TOP_RIGHT, 300.0f, Vector2D(200.0f, 80.0f), this }, 0.0f, false },
	{ { Enemy::BUG, Enemy::BOTTOM_RIGHT, 300.0f, Vector2D(240.0f, 80.0f), this }, 0.35f, false },
	{ { Enemy::BUG, Enemy::TOP_RIGHT, 300.0f, Vector2D(200.0f, 120.0f), this }, 0.7f, false },
	{ { Enemy::BUG, Enemy::BOTTOM_RIGHT, 300.0f, Vector2D(240.0f, 120.0f), this }, 1.05f, false },

	{ { Enemy::BOSS, Enemy::TOP_RIGHT, 300.0f, Vector2D(300.0f, 80.0f), this }, 6.0f, false },
	{ { Enemy::BOSS, Enemy::BOTTOM_RIGHT, 300.0f, Vector2D(340.0f, 80.0f), this }, 6.35f, false },
	{ { Enemy::BOSS, Enemy::TOP_RIGHT, 300.0f, Vector2D(300.0f, 120.0f), this }, 6.7f, false },
	{ { Enemy::BOSS, Enemy::BOTTOM_RIGHT, 300.0f, Vector2D(340.0f, 120.0f), this }, 6.05f, false },

	{ { Enemy::BOSS_GREEN, Enemy::TOP_RIGHT, 300.0f, Vector2D(400.0f, 80.0f), this }, 10.0f, false },
	{ { Enemy::BOSS_GREEN, Enemy::BOTTOM_RIGHT, 300.0f, Vector2D(440.0f, 80.0f), this }, 10.35f, false },
	{ { Enemy::BOSS_GREEN, Enemy::TOP_RIGHT, 300.0f, Vector2D(400.0f, 120.0f), this }, 10.7f, false },
	{ { Enemy::BOSS_GREEN, Enemy::BOTTOM_RIGHT, 300.0f, Vector2D(440.0f, 120.0f), this }, 10.05f, false },
	};

	m_timer = 0.0f;
	m_isEnterComplete = false;
}


void Formation::Destroy()
{

}

void Formation::Update()
{
	m_timer = m_timer + Timer::Instance()->DeltaTime();
	for (Info& info : m_formation)
	{
		if (info.isActive == false && m_timer > info.enterTime) {
			info.isActive = true;
			Enemy* enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);
		}
	}
}

const Formation::Path & Formation::GetRandomAttackPath()
{
	size_t index = (size_t)(rand() % m_attackPaths.size());
	return m_attackPaths[index];
}
