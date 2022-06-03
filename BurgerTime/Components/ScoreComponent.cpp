#include "BurgerTimePCH.h"
#include "ScoreComponent.h"
#include "SceneGraph/GameObject.h"
#include "EngineComponents/TextComponent.h"

ScoreComponent::ScoreComponent(dae::GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_Score{ 0 },
	m_NewlyAddedScore{ 0 },
	m_UpdateTextComponent{ true }
{
}

void ScoreComponent::Update()
{
	if (m_UpdateTextComponent)
	{
		if (auto textComponent = m_pOwner->GetComponentOfType<dae::TextComponent>())
		{
			textComponent->SetText("Score: " + std::to_string(m_Score));
		}
		m_UpdateTextComponent = false;
	}
}

void ScoreComponent::FixedUpdate()
{
}

int ScoreComponent::GetScore() const
{
    return m_Score;
}

int ScoreComponent::GetNewlyAddedScore() const
{
	return m_NewlyAddedScore;
}

void ScoreComponent::AddScore(int ammount)
{
	m_Score += ammount;
}

void ScoreComponent::OnNotify(dae::BaseComponent*, Event event)
{
	switch (event)
	{
	case Event::ENEMY_KILL:
		HandleScoreUpdate(100);
		break;
	case Event::BURGER_DROP:
		HandleScoreUpdate(50);
		break;
	default:
		break;
	}
}

void ScoreComponent::HandleScoreUpdate(int AddedPoints)
{
	AddScore(AddedPoints);
	Notify(this, Event::POINTS_ADDED);
	m_NewlyAddedScore = AddedPoints;
	m_UpdateTextComponent = true;
}
