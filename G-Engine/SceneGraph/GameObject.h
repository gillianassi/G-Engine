#pragma once
//#include "Transform.h"
#include <memory>
#include <vector>
#include <algorithm>
#include "EngineComponents/BaseComponent.h"

namespace dae
{
	class GameObject final
	{
	public:

		GameObject():
			m_Active{ true },
			m_upComponentVec{},
			m_pChildrenVec{},
			m_pParent{nullptr}
		{};


		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// Getters
		bool IsActive() const { return m_Active; };

		// Setters
		void Destroy() { m_Active = false; };


		template <typename T> T* AddComponent();
		template <typename T> T* GetComponent() const;


		void Update();
		void FixedUpdate();



		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index ) const;
		void RemoveChild(int index);
		void RemoveChild(GameObject* go);
		void AddChild(GameObject* go);


	private:
		bool m_Active;
		std::vector<std::unique_ptr<BaseComponent>> m_upComponentVec;

		std::vector<GameObject*> m_pChildrenVec;
		GameObject* m_pParent;

	};

	template<typename T>
	inline T* GameObject::AddComponent()
	{
		m_upComponentVec.emplace_back(std::move(std::make_unique<T>(this)));

		return dynamic_cast<T*>(m_upComponentVec.back().get());
	}

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (const auto& c: m_upComponentVec)
		{
			if (dynamic_cast<T*>(c.get()))
				return dynamic_cast<T*>(c.get());
		}
		return nullptr;
	}

}
