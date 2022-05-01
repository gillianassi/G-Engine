#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"


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

		virtual void Update() override {};
		virtual void FixedUpdate() override {};

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& newTexture);
		void Render();

	private:
		std::shared_ptr<Texture2D> m_spTexture;
	};
}

