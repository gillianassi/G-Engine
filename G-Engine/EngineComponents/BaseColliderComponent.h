#pragma once
#include "BaseComponent.h"


class b2Fixture;
class b2Shape;
namespace dae
{
	class RigidBodyComponent;
	class Physics;
	class BaseColliderComponent : public BaseComponent
	{
	public:

		struct PhysicsMaterial
		{
			PhysicsMaterial()
			{
				Density = 1.f ;
				Restitution = 0.f;
				RestitutionThreshold = 0.f;
				Friction =0.3f;
			}
			float Density;
			float Restitution;
			float RestitutionThreshold;
			float Friction;
		};

		BaseColliderComponent(GameObject* pOwner) :
			BaseComponent(pOwner),
			m_PhysicsMaterial{ PhysicsMaterial() }
		{

		}
		virtual ~BaseColliderComponent();

		BaseColliderComponent(const BaseColliderComponent& other) = delete;
		BaseColliderComponent(BaseColliderComponent&& other) = delete;
		BaseColliderComponent& operator=(const BaseColliderComponent& other) = delete;
		BaseColliderComponent& operator=(BaseColliderComponent&& other) = delete;

		
		virtual void Initialize() override = 0;
		
		void SetIsTrigger(bool isTrigger) {m_IsTrigger = isTrigger;}
		bool IsTrigger() { return m_IsTrigger; };

		void EnableRenderCollider(bool enable)
		{
			m_RenderCollider = enable;
		}



		void SetPhysicsMaterial(const PhysicsMaterial& mat) { m_PhysicsMaterial = mat; }

		void SetFixture(b2Fixture* pFixture)
		{
			m_pFixture = pFixture;
		}
		b2Fixture* GetFixture() const { return m_pFixture; }

	protected:

		friend class RigidBodyComponent;

		void AttachShapeToRigidBody();
		bool m_IsTrigger{};

		bool m_RenderCollider{true};

		PhysicsMaterial m_PhysicsMaterial;
		// necessary too bind the shape to a rigid body
		b2Fixture* m_pFixture{};
		b2Shape* m_pColliderShape{};

	};
}