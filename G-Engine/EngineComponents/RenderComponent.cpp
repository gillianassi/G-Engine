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
	m_srcRect{},
	m_ScaleX{1.f},
	m_ScaleY{1.f}
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

void dae::RenderComponent::SetScale(float scaleX, float scaleY)
{
	m_ScaleX = scaleX;
	m_ScaleY = scaleY;
}

void dae::RenderComponent::Render()
{
	if (m_spTexture)
	{
		const auto& pos = m_pOwner->GetTransform()->GetWorldPosition();
		Renderer::TransformDescription descr{};
		descr.x = pos.x;
		descr.y = pos.y;
		descr.srcRect = m_srcRect;
		descr.mirrorHorizontal = m_MirrorHorizontal;
		descr.mirrorVertical = m_MirrorVertical;
		descr.scaleX = m_ScaleX;
		descr.scaleY = m_ScaleY;

		dae::Renderer::GetInstance().RenderTexture(*m_spTexture, descr);
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
