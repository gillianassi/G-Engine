#pragma once
#include "EngineComponents/BaseComponent.h"

namespace dae
{
	class GameObject;
	class TrashTheCacheComponent final : public BaseComponent
	{
	public:
		TrashTheCacheComponent(GameObject* pOwner);
		virtual ~TrashTheCacheComponent() override;
		TrashTheCacheComponent(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent(TrashTheCacheComponent&& other) = delete;
		TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other) = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override;

		virtual void RenderImGui() override;
	private:
		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};
		class GameObject3D
		{
		public:
			Transform transform{};
			int ID{ 1 };
		};

		class GameObject3DAlt
		{
		public:
			GameObject3DAlt() : transform{ new Transform() } {  }
			~GameObject3DAlt() { delete transform; }
			Transform* transform;
			int ID{ 1 };
		};


		bool m_CalcInts;
		bool m_CalcGameObject3D;
		bool m_CalcGameObject3DAlt;

		const size_t m_BufferSize{ 1000000 };
		static const size_t m_nrOfStepsizes{ 10 }; // untill 1024
		int m_NrOfSamplesEx1{ 50 };
		int m_NrOfSamplesEx2{ 50 };
												  // Guiny pigs
		int* m_IntBuffer = new int[m_BufferSize] {};
		GameObject3D* m_GameObject3DBuffer = new GameObject3D[m_BufferSize]{};
		GameObject3DAlt* m_GameObject3DAltBuffer = new GameObject3DAlt[m_BufferSize]{};    //Heap
		// Samples
		float m_IntDurationArr[m_nrOfStepsizes];
		float m_GameObject3DDurationArr[m_nrOfStepsizes];
		float m_GameObject3DAltDurationArr[m_nrOfStepsizes];

		int* x = new int{ 10 };

		void CalculateWithInts();
		void CalculateWithGameObject3D();
		void CalculateWithGameObject3DAlt();

		void PrintTimeStepArray(const float timeStepArray[], size_t nrOfSteps);

	};
}
