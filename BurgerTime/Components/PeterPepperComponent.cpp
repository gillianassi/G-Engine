#include "BurgerTimePCH.h"
#include "PeterPepperComponent.h"
#include "ResourceManagement/Locator.h"
#include <SceneGraph/GameObject.h>

#include <cassert>


PeterPepperComponent::PeterPepperComponent(dae::GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_IsDead{false},
	m_pAnimator{nullptr},
	m_pRigidBodyComponent{nullptr}
{
	m_CounSoundID = Locator::getAudio().LoadSound("../Data/Coin.wav");
}

void PeterPepperComponent::Initialize()
{
	m_pAnimator = GetGameObject()->GetComponentOfType<dae::AnimatorComponent>();
	m_pRigidBodyComponent = GetGameObject()->GetComponentOfType<dae::RigidBodyComponent>();

	//assert(m_pAnimator != nullptr && m_pRigidBodyComponent != nullptr);
	assert(m_pAnimator != nullptr);

	dae::AnimationSprite::SpriteDescription spriteDesc{};
	spriteDesc.framesPerSecond = 0.16f;
	spriteDesc.nrAngles = 1;
	spriteDesc.nrFrames = 3;
	spriteDesc.nrPerType = { 1, 1, 1 };
	int walk = m_pAnimator->AddSpriteSheet("Textures/Player/PeterPepper_Walking.png", spriteDesc);
	spriteDesc = dae::AnimationSprite::SpriteDescription();
	spriteDesc.framesPerSecond = 0.f;
	spriteDesc.nrAngles = 1;
	spriteDesc.nrFrames = 1;
	spriteDesc.nrPerType = { 1 };
	int idle = m_pAnimator->AddSpriteSheet("Textures/Player/PeterPepper_Idle.png", spriteDesc);
	
	dae::AnimatorComponent::AnimationDescription animDesc{};
	animDesc = dae::AnimatorComponent::AnimationDescription(walk, true, 0, 0);
	MoveDownIndx = m_pAnimator->AddAnimation(animDesc);
	
	animDesc = dae::AnimatorComponent::AnimationDescription(walk, true, 0, 1);
	MoveUpIndx = m_pAnimator->AddAnimation(animDesc);

	animDesc = dae::AnimatorComponent::AnimationDescription(walk, true, 0, 2);
	MoveUpIndx = m_pAnimator->AddAnimation(animDesc);

	animDesc = dae::AnimatorComponent::AnimationDescription(walk, true, 0, 2,false,true);
	MoveRightIndx = m_pAnimator->AddAnimation(animDesc);
	
	animDesc = dae::AnimatorComponent::AnimationDescription(idle, true, 0, 2,false,true);
	IdleIndx = m_pAnimator->AddAnimation(animDesc);

}

void PeterPepperComponent::Update()
{
}

void PeterPepperComponent::FixedUpdate()
{

}

void PeterPepperComponent::StopMovement()
{
	m_pRigidBodyComponent->SetLinearVelocity({ 0.0f, 0.0f });
	m_pAnimator->PlayAnimation(IdleIndx, true);
}
void PeterPepperComponent::MoveLeft()
{
	m_pRigidBodyComponent->SetLinearVelocity({ -50.0f, 0.0f });
	m_pAnimator->PlayAnimation(MoveLeftIndx, true);
}

void PeterPepperComponent::MoveRight()
{
	m_pRigidBodyComponent->SetLinearVelocity({ 50.0f, 0.0f });
	m_pAnimator->PlayAnimation(MoveLeftIndx, true);
}

void PeterPepperComponent::MoveUp()
{
	m_pRigidBodyComponent->SetLinearVelocity({ 0.0f, -50.0f });
	m_pAnimator->PlayAnimation(MoveLeftIndx, true);
}

void PeterPepperComponent::MoveDown()
{
	m_pRigidBodyComponent->SetLinearVelocity({ 0.0f, 50.0f });
	m_pAnimator->PlayAnimation(MoveLeftIndx, true);
}


void PeterPepperComponent::Die()
{
	Locator::getAudio().PlaySound(m_CounSoundID);
	m_IsDead = true;
	Notify(this, Event::PLAYER_DEATH);
	std::cout << "Player Died" << std::endl;
}
