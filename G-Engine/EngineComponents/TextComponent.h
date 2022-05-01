#pragma once

#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Font;
	class GameObject;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(GameObject* pOwner);
		virtual ~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override;

		void SetText(std::string newText);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetColor(SDL_Color color);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color;
	};
}
