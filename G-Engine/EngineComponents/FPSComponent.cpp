#include "GEnginePCH.h"
#include "FPSComponent.h"
#include "SceneGraph/GameObject.h"

#include "Core/Time.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner) :
	dae::BaseComponent(pOwner),
	m_ElapsedFrameTime{},
	m_FrameCounter{}
{
}

void dae::FPSComponent::Update()
{
	++m_FrameCounter;
	m_ElapsedFrameTime += Time::deltaTime;
	if (m_ElapsedFrameTime > 1.f)
	{
		m_pOwner->GetComponent<TextComponent>()->SetText(std::to_string(m_FrameCounter) + " FPS");
		m_FrameCounter = 0;
		m_ElapsedFrameTime -= 1.f;
	}
}

void dae::FPSComponent::FixedUpdate()
{
}
