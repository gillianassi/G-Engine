#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "misc/Structs.h"

namespace dae
{
	class GameObject;
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(GameObject* pOwner);
		virtual ~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Initialize() override {}
		virtual void Update() override {};
		virtual void FixedUpdate() override {};

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& newTexture);

		void MirrorHorizontal(bool mirror);
		void MirrorVertical(bool mirror);
		void SetSourceRect(const SDL_Rect& rect);

		void SetScale(float scaleX, float scaleY);

		void Render();

		Texture2D* GetTexture() { return m_spTexture.get(); }

	private:
		void CalculateDimensions();


		float m_ScaleX, m_ScaleY;
		bool m_MirrorHorizontal;
		bool m_MirrorVertical;
		SDL_Rect m_srcRect;

		std::shared_ptr<Texture2D> m_spTexture;
	};
}

