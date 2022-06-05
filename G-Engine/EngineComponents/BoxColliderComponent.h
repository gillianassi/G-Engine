#pragma once
#include "BaseColliderComponent.h"

namespace dae
{
	class RigidBodyComponent;
	class BoxColliderComponent : public BaseColliderComponent
	{
	public:
		struct BoxColliderDescr
		{
			BoxColliderDescr()
			{
				physicsMaterial = PhysicsMaterial();
				Width = 10.f;
				Height = 10.f;
				PivotX = 0.f;
				PivotY = 0.f;
				Rotation = 0.f;

			}
			PhysicsMaterial physicsMaterial;
			float Width;
			float Height;
			float PivotX;
			float PivotY;
			float Rotation;
		};

		BoxColliderComponent(GameObject* pOwner);
		virtual ~BoxColliderComponent() = default;

		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;


		virtual void Initialize() override;
		virtual void Render() override;
		virtual void RenderImGui() override;

		void SetColliderTransform(BoxColliderDescr descr);

		void SetWidth(float width);
		void SetHeight(float height);
		void SetPivot(float pivotX, float pivotY);
		void SetRotation(float rotation);

		void SetRenderColor(glm::vec4 color) { m_Color = color; }
	



	private:
		friend class Physics;
		friend class RigidBodyComponent;



		BoxColliderDescr m_Description{};
		RigidBodyComponent* m_pRigidbody{};

		glm::vec4 m_Color{};
	};
}