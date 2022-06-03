#pragma once
//#include "Transform.h"
#include <memory>
#include <vector>
#include <algorithm>
#include "EngineComponents/BaseComponent.h"

namespace dae
{
	class Scene;
	class Component;
	class TransformComponent;
	class GameObject final
	{
	public:

		
		GameObject(bool propagateTags = true);

		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// scene graph
		
		template <typename TypeToAdd> TypeToAdd* AddComponent();
		template <typename TypeToGet> TypeToGet* GetComponentOfType() const;
		template <typename TypeToGet> TypeToGet* GetAllComponentsOfType() const;

		TransformComponent* GetTransform() const { return m_pTransform; }
		

		GameObject* GetParent() const;
		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		void RemoveChildFromChildVec(int index);
		void RemoveChildFromChildVec(GameObject* go);
		void SetParent(GameObject* parent, bool hasCheckedHierarchy = false);
		void AddChild(GameObject* go, bool hasCheckedHierarchy = false);

		// base
		bool IsEnabled() const { return m_IsEnabled; }
		void SetEnabled(bool enabled) { m_MarkedForEnable = enabled; }

		bool HasTag(int tag) const;
		const std::vector<int>& GetTags() const { return m_Tags; }
		void AddTag(int tag, bool propagateToChildren = true);
		
		void Destroy() { m_IsMarkedForDestroy = true; };

		
	protected:




	private:
		friend Scene;
		// only the scene can create GameObjects and handle them
		//GameObject(GameObject* pParent, Scene* pScene, bool propagateTags = true);

		void Initialize() const;
		void Update() const;
		void FixedUpdate() const;
		virtual void Render() const;
		virtual void RenderImGui() const;


		bool HasChildInHierarchy(GameObject* pGo);
		
		GameObject* m_pParent{};
		std::vector<std::unique_ptr<BaseComponent>> m_upComponentVec{};
		std::vector<GameObject*> m_pChildrenVec{};

		Scene* m_pScene{};

		TransformComponent* m_pTransform{};


		std::vector<int> m_Tags{};


		bool m_IsMarkedForDestroy{ false };
		bool m_IsEnabled{ true }, m_MarkedForEnable{ true };

	};


	// *************************************
	// ******** Tempated functions *********
	// *************************************
	template<typename TypeToAdd>
	inline TypeToAdd* GameObject::AddComponent()
	{
		m_upComponentVec.emplace_back(std::move(std::make_unique<TypeToAdd>(this)));

		return dynamic_cast<TypeToAdd*>(m_upComponentVec.back().get());
	}

	template<typename TypeToGet>
	inline TypeToGet* GameObject::GetComponentOfType() const
	{
		for (const auto& c: m_upComponentVec)
		{
			if (dynamic_cast<TypeToGet*>(c.get()))
				return dynamic_cast<TypeToGet*>(c.get());
		}
		return nullptr;
	}

	template<typename TypeToGet>
	inline TypeToGet* GameObject::GetAllComponentsOfType() const
	{
		std::vector<TypeToGet*> componentsVec{};
		for (const auto& c: m_upComponentVec)
		{
			if (dynamic_cast<TypeToGet*>(c.get()))
				componentsVec.push_back(dynamic_cast<TypeToGet*>(c.get()));
		}
		return componentsVec;
	}

}
