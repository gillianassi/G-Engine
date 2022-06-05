#pragma once
#include "BaseColliderComponent.h"

namespace dae
{
	class RigidBodyComponent;
	class BoxCollider : public BaseColliderComponent
	{
	public:
		struct BoxColliderDescr
		{
			float Width;
			float Height;
			float PivotX;
			float PivotY;
			float Rotation;
		};

		BoxCollider(GameObject* pOwner);
		virtual ~BoxCollider() = default;

		BoxCollider(const BoxCollider& other) = delete;
		BoxCollider(BoxCollider&& other) = delete;
		BoxCollider& operator=(const BoxCollider& other) = delete;
		BoxCollider& operator=(BoxCollider&& other) = delete;


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		virtual void RenderImGui() override;

		void SetColliderTransform(BoxColliderDescr descr);

		void SetWidth(float width);
		void SetHeight(float height);
		void SetPivot(float pivotX, float pivotY);
		void SetRotation(float rotation);

	



	private:
		friend class Physics;
		friend class RigidBodyComponent;
		friend class TransformComponent;

		void AttachToRigidBody(GameObject* pGameObject);


		BoxColliderDescr m_Description;
		RigidBodyComponent* m_pRigidbody;
	};
}