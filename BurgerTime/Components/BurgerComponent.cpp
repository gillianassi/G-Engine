#include "BurgerTimePCH.h"
#include "BurgerComponent.h"

BurgerComponent::BurgerComponent(dae::GameObject* pOwner) :
	dae::BaseComponent(pOwner),
	m_IsDropped{ false }
{
}



void BurgerComponent::Initialize()
{
}

void BurgerComponent::Update()
{
}

void BurgerComponent::FixedUpdate()
{
}

void BurgerComponent::Drop()
{
	//if (m_IsDropped) return;

	m_IsDropped = true;
	Notify(this, Event::BURGER_DROP);
	std::cout << "SHARED POINTS: Burger Dropped" << std::endl;
}

void BurgerComponent::ResetBurger()
{
	std::cout << "Burger Reset" << std::endl;
	m_IsDropped = false;
}
