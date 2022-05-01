#include "BurgerTimePCH.h"
#include "AchievementComponent.h"
#include "ScoreComponent.h"
//#include <steam_api.h>

AchievementComponent::AchievementComponent(dae::GameObject* pOwner) :
	dae::BaseComponent(pOwner),
	m_TotalScore{0},
	m_AchievementGet{false}
{
}

void AchievementComponent::Update()
{

}

void AchievementComponent::FixedUpdate()
{
}

void AchievementComponent::OnNotify(dae::BaseComponent* entity, Event event)
{
	if (!m_AchievementGet && event == Event::POINTS_ADDED) {

		if (auto scoreComponent = static_cast<ScoreComponent*>(entity))
		{
			m_TotalScore+= scoreComponent->GetNewlyAddedScore();
		}

		if (m_TotalScore >= 500)
		{
			//SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
			//SteamUserStats()->StoreStats();
			m_AchievementGet = true;
		}
	}
}
