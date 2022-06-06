#pragma once
#include "EngineComponents/BaseComponent.h"
#include "Helpers/Observable.h"
#include <EngineComponents/AnimatorComponent.h>
#include <EngineComponents/RigidBodyComponent.h>

class PeterPepperComponent : public dae::BaseComponent, public Observable
{
public:
	PeterPepperComponent(dae::GameObject* pOwner);
	virtual ~PeterPepperComponent() = default;
	PeterPepperComponent(const PeterPepperComponent& other) = delete;
	PeterPepperComponent(PeterPepperComponent&& other) = delete;
	PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
	PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void StopMovement();

	void Die();
private:
	bool m_IsDead;
	int m_CounSoundID;

	int MoveLeftIndx;
	int MoveRightIndx;
	int MoveUpIndx;
	int MoveDownIndx;
	int IdleIndx;

	dae::AnimatorComponent* m_pAnimator;
	dae::RigidBodyComponent* m_pRigidBodyComponent;
};

