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

glm::vec3 dae::TransformComponent::GetPosition()
{
	glm::vec3 position = m_Transform.GetPosition();
	if (m_pOwner->GetParent() != nullptr)
	{
		if (m_pOwner->GetParent()->GetComponent<TransformComponent>())
		{
			position += m_pOwner->GetParent()->GetComponent<TransformComponent>()->GetPosition();
		}
	}
	return position;
}

void dae::TransformComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
