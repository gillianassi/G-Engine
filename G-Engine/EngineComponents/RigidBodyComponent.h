#pragma once
#include "BaseComponent.h"
#include "BaseColliderComponent.h"

class b2Body;
class b2Shape;
namespace dae
{
	class BaseColliderComponent;
	class TransformComponent;
	class RigidBodyComponent final : public BaseComponent
	{
	public:
		enum class RigidBodyType
		{
			Static,
			Kinematic,
			Dynamic
		};

		struct RigidBodyDescription
		{
			RigidBodyDescription()
			{
				position = glm::vec2(0.f, 0.f);
				angle = 0.f;
				linearVelocity = glm::vec2(0.f,0.f);
				angularVelocity = 0.f;
				linearDamping = 0.f;
				angularDamping = 0.f;
				allowSleep = true;
				awake = true;
				fixedRotation = false;
				bullet = false;
				type = RigidBodyType::Static;
				enabled = true;
				gravityScale = 1.f;
			}

			glm::vec2 position;
			float angle;
			glm::vec2 linearVelocity;
			float angularVelocity;
			float linearDamping;
			float angularDamping;
			bool allowSleep;
			bool awake;
			bool fixedRotation;
			bool bullet;
			RigidBodyType type;
			bool enabled;
			float gravityScale;
		};

		RigidBodyComponent(GameObject* pOwner);
		
		~RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent & other) = delete;
		RigidBodyComponent(RigidBodyComponent && other) = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent & other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent && other) = delete;

		void Initialize() override;
		void FixedUpdate() override;
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
		const RigidBodyDescription& GetInitialDescription() { return m_Description; }
		void SetInitialDescription( const RigidBodyDescription& desc) { m_Description = desc; }

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
		friend BaseColliderComponent;
		void AttachShapeToRigidBody(BaseColliderComponent* pCollider);
		// only 
		void SetBody(b2Body* body) { m_pBody = body; }
		b2Body* GetBody() const { return m_pBody; }

		b2Body* m_pBody = nullptr;

		RigidBodyDescription m_Description;

		TransformComponent* m_pTransform;

	};
}