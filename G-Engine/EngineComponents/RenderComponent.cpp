#include "GEnginePCH.h"
#include "RenderComponent.h"
#include "SceneGraph/GameObject.h"
#include "TransformComponent.h"
#include "ResourceManagement/ResourceManager.h"
#include "ResourceManagement/Texture2D.h"
#include "Core/Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_spTexture{},
	m_MirrorHorizontal{false},
	m_MirrorVertical{false},
	m_srcRect{}
{

}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
	CalculateDimensions();
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& newTexture)
{
	m_spTexture = newTexture;
	CalculateDimensions();
}

void dae::RenderComponent::MirrorHorizontal(bool mirror)
{
	m_MirrorHorizontal = mirror;
}

void dae::RenderComponent::MirrorVertical(bool mirror)
{
	m_MirrorVertical = mirror;
}

void dae::RenderComponent::SetSourceRect(const SDL_Rect& rect)
{
	m_srcRect = rect;
}

void dae::RenderComponent::Render()
{
	if (m_spTexture)
	{
		const auto& pos = m_pOwner->GetTransform()->GetWorldPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y , m_srcRect, m_MirrorHorizontal, m_MirrorVertical);
	}
}

void dae::RenderComponent::CalculateDimensions()
{
	m_spTexture->QueryDimensions();
	SDL_Rect rect{};
	rect.x = 0;
	rect.y = 0;
	rect.w = m_spTexture->GetWidth();
	rect.h = m_spTexture->GetHeight();

	m_srcRect = rect;
}
