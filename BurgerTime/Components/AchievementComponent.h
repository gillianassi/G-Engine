#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observer.h"
class AchievementComponent: public dae::BaseComponent, public Observer
{
public:
	AchievementComponent(dae::GameObject* pOwner);
	virtual ~AchievementComponent() = default;
	AchievementComponent(const AchievementComponent& other) = delete;
	AchievementComponent(AchievementComponent&& other) = delete;
	AchievementComponent& operator=(const AchievementComponent& other) = delete;
	AchievementComponent& operator=(AchievementComponent&& other) = delete;


	virtual void Update() override;
	virtual void FixedUpdate() override;

	virtual void OnNotify(dae::BaseComponent* entity, Event event)  override;

private:
	int m_TotalScore;
	bool m_AchievementGet;
};

