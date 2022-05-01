#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observable.h"

class BurgerComponent : public dae::BaseComponent, public Observable
{
public:
	BurgerComponent(dae::GameObject* pOwner);
	virtual ~BurgerComponent() = default;
	BurgerComponent(const BurgerComponent& other) = delete;
	BurgerComponent(BurgerComponent&& other) = delete;
	BurgerComponent& operator=(const BurgerComponent& other) = delete;
	BurgerComponent& operator=(BurgerComponent&& other) = delete;


	virtual void Update() override;
	virtual void FixedUpdate() override;

	void Drop();
	void ResetBurger();
private:
	bool m_IsDropped;
};

