#pragma once
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);

		void StartDraw() const;
		void Render() const;
		void EndDraw() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const float x, const float y) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const SDL_Rect& srcRect, bool mirrorHorizontal, bool mirrorVertical) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const SDL_Rect& srcRect, bool mirrorHorizontal, bool mirrorVertical) const;
		void DrawRect(glm::vec2 pos, float width, float height, glm::vec4 color = glm::vec4(1.f,1.f,1.f,1.f));


		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:
		void ShowDearImGuiExercises() const;
	};
}

