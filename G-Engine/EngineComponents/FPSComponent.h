#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class GameObject;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(GameObject* pOwner);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Initialize() override {}
		virtual void Update() override;
		virtual void FixedUpdate() override;

	private:
		float m_ElapsedFrameTime;
		int m_FrameCounter;

	};
}

