#pragma once

#include <functional>
#include "Core/ContactListener.h"



namespace dae
{
	class GameObject;
	class Physics;
	class BaseComponent
	{
	public:
		typedef std::function<void(GameObject* pTriggerObject, GameObject* pOtherObject, ContactListener::ContactType action)> PhysicsCallback;

		BaseComponent(GameObject* pOwner, bool enabled = true):
			m_pOwner{ pOwner },
			m_IsEnabled{ enabled },
			m_MarkedForEnable{ enabled }
		{ };

		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		// base
		virtual void Initialize() = 0;
		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void Render() {}
		virtual void RenderImGui() {}

		GameObject* GetGameObject() { return m_pOwner; }
		
		// transition
		virtual void OnEnable() {}
		virtual void OnDIsable() {}
		virtual void OnDestroy() {}

		bool IsEnabled() const { return m_IsEnabled; }
		void SetEnabled(bool enabled) { m_MarkedForEnable = enabled; }

		void Destroy() { m_IsMarkedForDestroy = true; }
		bool IsMarkedForDestroy() { return m_IsMarkedForDestroy; }

		void SetOnTriggerCallBack(PhysicsCallback callback) { m_OnTriggerCallback = callback; };

		bool IsInitialized() {return m_IsInitialized;}
		void SetInitialized(bool initialized) { m_IsInitialized = initialized; }

	protected:
		bool m_IsEnabled{ true };
		bool m_IsInitialized{ false };
		GameObject* m_pOwner{};

	private:
		friend GameObject;
		friend Physics;


		bool m_IsMarkedForDestroy{ false }, m_MarkedForEnable{ true };


		void UpdateComponentState()
		{
			if (m_MarkedForEnable == m_IsEnabled) return;

			m_IsEnabled = m_MarkedForEnable;
			(m_IsEnabled) ? OnEnable() : OnDIsable();
		}

		PhysicsCallback m_OnTriggerCallback{};

	};
}
