#include "GEnginePCH.h"
#include "RenderComponent.h"
#include "SceneGraph/GameObject.h"
#include "TransformComponent.h"
#include "ResourceManagement/ResourceManager.h"
#include "Core/Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_spTexture{}
{

}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& newTexture)
{
	m_spTexture = newTexture;
}

void dae::RenderComponent::Render()
{
	if (m_spTexture)
	{
		const auto& pos = m_pOwner->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
	}
}
