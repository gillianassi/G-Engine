#include "GEnginePCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>
#include <cassert>
#include "SceneGraph/GameObject.h"
#include "RenderComponent.h"
#include "G-Engine/Core/Renderer.h"
#include "ResourceManagement/Font.h"
#include "ResourceManagement/Texture2D.h"


dae::TextComponent::TextComponent(GameObject* pOwner):
	dae::BaseComponent(pOwner),
	m_Text{},
	m_NeedsUpdate{true},
	m_Font{},
	m_Color{ 255,255,255 }
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		assert(m_Font.get());
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pOwner->GetComponentOfType<RenderComponent>()->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::FixedUpdate()
{
}

void dae::TextComponent::SetText(std::string newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
}

void dae::TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}
