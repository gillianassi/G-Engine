#include "GEnginePCH.h"
#include "TransformComponent.h"
#include "SceneGraph/GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner):
	dae::BaseComponent(pOwner)
{
}


void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::FixedUpdate()
{
}

glm::vec2 dae::TransformComponent::GetPosition()
{
	return m_Position;
}

glm::vec2 dae::TransformComponent::GetWorldPosition()
{
	glm::vec2 pos = m_Position;
	if (m_pOwner->GetParent() != nullptr)
	{
		if (m_pOwner->GetParent()->GetComponentOfType<TransformComponent>())
		{
			pos += m_pOwner->GetParent()->GetComponentOfType<TransformComponent>()->GetPosition();
		}
	}
	return pos;
}

void dae::TransformComponent::SetPosition(float x, float y)
{
	m_Position = glm::vec2(x, y);
}
