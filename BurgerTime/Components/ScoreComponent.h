#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observer.h"
#include "Helpers/Observable.h"

class ScoreComponent : public dae::BaseComponent, public Observer, public Observable
{
public:
	ScoreComponent(dae::GameObject* pOwner);
	virtual ~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void FixedUpdate() override;

	int GetScore() const;
	int GetNewlyAddedScore() const;
	void AddScore(int ammount);

	virtual void OnNotify(dae::BaseComponent * entity, Event event)  override;


private:
	int m_Score;
	int m_NewlyAddedScore;
	bool m_UpdateTextComponent;

	void HandleScoreUpdate(int AddedPoints);
};

