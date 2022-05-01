#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observable.h"

class EnemyComponent : public dae::BaseComponent, public Observable
{
public:
	EnemyComponent(dae::GameObject* pOwner);
	virtual ~EnemyComponent() = default;
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;


	virtual void Update() override;
	virtual void FixedUpdate() override;

	void Revive();
	void Die();
private:
	bool m_IsDead;
};

