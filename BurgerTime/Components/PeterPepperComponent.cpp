#include "BurgerTimePCH.h"
#include "PeterPepperComponent.h"
#include "ResourceManagement/Locator.h"

PeterPepperComponent::PeterPepperComponent(dae::GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_IsDead{false}
{
	m_CounSoundID = Locator::getAudio().LoadSound("../Data/Coin.wav");
}

void PeterPepperComponent::Update()
{
}

void PeterPepperComponent::FixedUpdate()
{
}


void PeterPepperComponent::Die()
{
	Locator::getAudio().PlaySound(m_CounSoundID);
	m_IsDead = true;
	Notify(this, Event::PLAYER_DEATH);
	std::cout << "Player Died" << std::endl;
}
