#include "BurgerTimePCH.h"
#include "LivesComponent.h"
#include "EngineComponents/TextComponent.h"
#include "SceneGraph/GameObject.h"
#include "Components/ScoreComponent.h"

LivesComponent::LivesComponent(dae::GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_NrOfLives{ 3 },
	m_UpdateTextComponent{true}
{
}

void LivesComponent::Update()
{
	if (m_UpdateTextComponent)
	{
		if (auto textComponent = m_pOwner->GetComponentOfType<dae::TextComponent>())
		{
			textComponent->SetText("Lives: " + std::to_string(m_NrOfLives));
		}
		m_UpdateTextComponent = false;
	}
}

void LivesComponent::FixedUpdate()
{
}

int LivesComponent::GetNrOfLives() const
{
	return m_NrOfLives;
}

void LivesComponent::SetLives(int ammount)
{
	m_NrOfLives = ammount;
}

void LivesComponent::OnNotify(dae::BaseComponent*, Event event)
{
	if (event == Event::PLAYER_DEATH) 
	{
		m_NrOfLives--;
		m_UpdateTextComponent = true;
	}
}

