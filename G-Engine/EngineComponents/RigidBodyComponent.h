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

		// Setters
		void SetTransform(glm::vec2 pos, float angle);
		void SetLinearVelocity(glm::vec2 vel);
		void SetAngularVelocity(float vel);
		void SetLinearDamiping(float damp);
		void SetAngularDamiping(float damp);
		void AllowSleep(bool allow);
		void SetAwake(bool isAwake);
		void EnableFixedRotation(bool enable);
		void SetBullet(bool enable);
		void SetRigidBodyType(RigidBodyType type);
		void EnableRigidBody(bool enable);
		void SetGravityScale(float scale);


		// Getters
		glm::vec2 GetPosition();
		float GetAngle() ;
		glm::vec2 GetLinearVelocity();
		float GetAngularVelocity();
		float GetLinearDamping() ;
		float GetAngularDamping();
		bool IsSleepAllowed();
		bool IsAwake();
		bool HasFixedRotation();
		bool IsBullet();
		RigidBodyType GetRigidBodyType();
		bool IsRigidBodyEnabled();
		float GetGravityScale();

		void UpdateTransformComponent();

		

		void ApplyForce(const glm::fvec2& force, bool wake = true);
		void ApplyImpulse(const glm::fvec2& impulse, bool wake = true);


	private:
		// only physics can set the rigid body
		friend Physics;
		void SetBody(b2Body* body) { m_pBody = body; }
		b2Body* GetBody() const { return m_pBody; }

		RigidBodyType m_BodyType;
		b2Body* m_pBody = nullptr;

	};
}