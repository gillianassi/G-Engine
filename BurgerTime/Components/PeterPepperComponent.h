#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observable.h"

class PeterPepperComponent : public dae::BaseComponent, public Observable
{
public:
	PeterPepperComponent(dae::GameObject* pOwner);
	virtual ~PeterPepperComponent() = default;
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	virtual void Update() override;
	virtual void FixedUpdate() override;
	void Die();
private:
	bool m_IsDead;
};

