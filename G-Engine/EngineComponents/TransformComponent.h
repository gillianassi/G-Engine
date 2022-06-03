#pragma once

#include "BaseComponent.h"
#include "Transform.h"

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


		glm::vec3 GetPosition();
		void SetPosition(float x, float y);

	private:
		dae::Transform m_Transform;

	};
}

