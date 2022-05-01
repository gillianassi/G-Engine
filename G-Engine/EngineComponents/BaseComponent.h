#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pOwner) { m_pOwner = pOwner; };
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		// TODO: Move this to scene
		virtual void RenderImGui() {};

	protected:
		GameObject* m_pOwner;
	};
}
