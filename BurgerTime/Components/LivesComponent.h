#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observer.h"
class LivesComponent : public dae::BaseComponent, public Observer
{
public:
	LivesComponent(dae::GameObject* pOwner);
	virtual ~LivesComponent() = default;
	LivesComponent(const LivesComponent& other) = delete;
	LivesComponent(LivesComponent&& other) = delete;
	LivesComponent& operator=(const LivesComponent& other) = delete;
	LivesComponent& operator=(LivesComponent&& other) = delete;

	virtual void Initialize() override {}
	virtual void Update() override;
	virtual void FixedUpdate() override;

	int GetNrOfLives() const;
	void SetLives(int ammount);

	virtual void OnNotify(dae::BaseComponent* entity, Event event)  override;


private:
	int m_NrOfLives;
	bool m_UpdateTextComponent;

};

