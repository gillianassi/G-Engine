#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pOwner, bool enabled = true) 
		{ 
			m_pOwner = pOwner;
			m_IsEnabled = enabled;
		};
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void OnEnable() {}
		virtual void OnDIsable() {}
		virtual void Render() {}
		virtual void RenderImGui() {}


		GameObject* GetGameObject() { return m_pOwner; }

		void Destroy() { m_IsMarkedForDestroy = true; }
		bool IsMarkedForDestroy() { return m_IsMarkedForDestroy; }

		bool IsEnabled() const { return m_IsEnabled; }
		void SetEnabled(bool enabled) { m_SetEnable = enabled; }

		void UpdateComponentState()
		{
			if (m_SetEnable == m_IsEnabled) return;

			m_IsEnabled = m_SetEnable;
			(m_IsEnabled) ? OnEnable() : OnDIsable();
		}



	protected:
		bool m_IsEnabled{ true }, m_SetEnable{true};
		bool m_IsMarkedForDestroy{ false };
		GameObject* m_pOwner;
	};
}
