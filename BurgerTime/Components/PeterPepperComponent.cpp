#include "BurgerTimePCH.h"
#include "PeterPepperComponent.h"

PeterPepperComponent::PeterPepperComponent(dae::GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_IsDead{false}
{
}

void PeterPepperComponent::Update()
{
}

void PeterPepperComponent::FixedUpdate()
{
}


void PeterPepperComponent::Die()
{
	m_IsDead = true;
	Notify(this, Event::PLAYER_DEATH);
	std::cout << "Player Died" << std::endl;
}
