#pragma once
#include "BaseComponent.h"

class b2Body;
namespace dae
{
	class TransformComponent;
	class BoxColliderComponent;
	class RigidBodyComponent final : public BaseComponent
	{
	public:
		enum class RigidBodyType
		{
			Static,
			Kinematic,
			Dynamic
		};

		RigidBodyComponent(GameObject* pOwner);
		
		~RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent & other) = delete;
		RigidBodyComponent(RigidBodyComponent && other) = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent & other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent && other) = delete;

		void Initialize() override;
		void OnDestroy() override;

		void UpdateTransformComponent();


		void EnableFixedRotation(bool enable);
		bool HasFixedRotation() {return m_HasFixedRotation;}

		void SetGravityScale(float scale);
		float GetGravityScale() { return m_GravityScale; }

		void SetRigidBodyType(RigidBodyType type);
		RigidBodyType GetRigidBodyType() { return m_BodyType; }
		

		void ApplyForce(const glm::fvec2& force, bool wake = true);
		void ApplyImpulse(const glm::fvec2& impulse, bool wake = true);


	private:
		friend Physics;
		void SetBody(b2Body* body) { m_pBody = body; }
		b2Body* GetBody() const { return m_pBody; }


		bool m_HasFixedRotation;
		float m_GravityScale;

		RigidBodyType m_BodyType;
		b2Body* m_pBody = nullptr;

	};
}