#pragma once
#include "BaseComponent.h"

class b2Fixture;

namespace dae
{

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
		virtual ~BaseColliderComponent() = default;

		BaseColliderComponent(const BaseColliderComponent& other) = delete;
		BaseColliderComponent(BaseColliderComponent&& other) = delete;
		BaseColliderComponent& operator=(const BaseColliderComponent& other) = delete;
		BaseColliderComponent& operator=(BaseColliderComponent&& other) = delete;

		
		virtual void Initialize() override = 0;
		virtual void Update() override = 0;
		
		void SetIsTrigger(bool isTrigger) {m_IsTrigger = isTrigger;}
		bool IsTrigger() { return m_IsTrigger; };



		void SetPhysicsMaterial(const PhysicsMaterial& mat) { m_PhysicsMaterial = mat; }

		void SetFixture(b2Fixture* pFixture)
		{
			m_pFixture = pFixture;
		}
		b2Fixture* GetFixture() const { return m_pFixture; }

	protected:
		bool m_IsTrigger{};

		PhysicsMaterial m_PhysicsMaterial;

		// necessary too bind the shape to a rigid body
		b2Fixture* m_pFixture{};
		
	};
}