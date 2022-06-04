#pragma once

#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(GameObject* pOwner);
		virtual ~TransformComponent() override = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Initialize() override {}
		virtual void Update() override;
		virtual void FixedUpdate() override;


		glm::vec2 GetPosition();
		glm::vec2 GetWorldPosition();
		void SetPosition(float x, float y);

	private:

		glm::vec2 m_Position{};
		glm::vec2 m_Scale{};
		float m_Rotation{};

	};
}

