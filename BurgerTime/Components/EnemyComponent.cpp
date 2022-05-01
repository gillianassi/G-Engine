#include "BurgerTimePCH.h"
#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(dae::GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_IsDead{ false }
{
}

void EnemyComponent::Update()
{
}

void EnemyComponent::FixedUpdate()
{
}

void EnemyComponent::Revive()
{
	if (!m_IsDead) return;
	m_IsDead = false;
	std::cout << "Player specific: Enemy Revived!" << std::endl;
}

void EnemyComponent::Die()
{
	if (m_IsDead) return;

	m_IsDead = true;
	Notify(this, Event::ENEMY_KILL);
	std::cout << "UNIQUE POINTS: Enemy Killed" << std::endl;
}
