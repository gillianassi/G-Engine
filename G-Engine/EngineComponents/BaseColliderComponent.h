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
			float Density {1.f};
			float Restitution {0.f};
			float RestitutionThreshold{0.f};
			float Friction{0.1f};
		};

		BaseColliderComponent(GameObject* pOwner) :
			BaseComponent(pOwner)
		{

		}
		virtual ~BaseColliderComponent() = default;

		BaseColliderComponent(const BaseColliderComponent& other) = delete;
		BaseColliderComponent(BaseColliderComponent&& other) = delete;
		BaseColliderComponent& operator=(const BaseColliderComponent& other) = delete;
		BaseColliderComponent& operator=(BaseColliderComponent&& other) = delete;

		virtual void Update() override = 0;
		
		void SetIsTrigger(bool isTrigger) {m_IsTrigger = isTrigger;}
		bool IsTrigger() { return m_IsTrigger; };





		void SetFixture(b2Fixture* pFixture)
		{
			m_pFixture = pFixture;
		}
		b2Fixture* GetFixture() const { return m_pFixture; }

	private:
		bool m_IsTrigger{};


		b2Fixture* m_pFixture{};
		
	};
}