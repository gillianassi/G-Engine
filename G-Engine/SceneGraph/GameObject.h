#pragma once
//#include "Transform.h"
#include <memory>
#include <vector>
#include <algorithm>
#include "EngineComponents/BaseComponent.h"

namespace dae
{
	class Scene;
	class BaseComponent;
	class TransformComponent;
	class GameObject final
	{
	public:
		
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// scene graph
		
		template <typename TypeToAdd> 
		std::enable_if_t<std::is_base_of_v<BaseComponent, TypeToAdd>, TypeToAdd*> 
			AddComponent();

		template <typename TypeToGet>
		std::enable_if_t<std::is_base_of_v<BaseComponent, TypeToGet>, TypeToGet*>
			GetComponentOfType() const;

		template <typename TypeToGet>
		std::vector<std::enable_if_t<std::is_base_of_v<BaseComponent, TypeToGet>, TypeToGet*>>
			 GetAllComponentsOfType() const;

		TransformComponent* GetTransform() const { return m_pTransform; }
		

		GameObject* GetParent() const;
		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;

		// create a new gameobject
		GameObject* AddChild(std::string name, bool inheritTags = true);
		// edit the hierarchy
		void ReChild(GameObject* go, bool hasCheckedHierarchy = false);
		void ReParent(GameObject* parent, bool hasCheckedHierarchy = false);

		// base
		bool IsEnabled() const { return m_IsEnabled; }
		void SetEnabled(bool enabled) { m_MarkedForEnable = enabled; }

		bool HasTag(int tag) const;
		const std::vector<int>& GetTags() const { return m_Tags; }
		void AddTag(int tag, bool propagateToChildren = true);
		
		void Destroy();
		bool IsMarkedForDestroy() { return m_IsMarkedForDestroy; }

		Scene* GetScene() { return m_pScene; }

	private:
		friend Scene;
		GameObject(const std::string& name, GameObject* pParent, Scene* pScene, bool propagateTags = true);

		void Initialize() const;
		void Update() const;
		void FixedUpdate() const;
		void Render() const;
		void RenderImGui() const;


		void OnEnable()const;
		void OnDIsable()const;
		void OnDestroy()const;

		void UpdateGameObjectState();

		void RemoveChildFromChildVec(int index);
		void RemoveChildFromChildVec(GameObject* go);

		bool HasChildInHierarchy(GameObject* pGo);
		
		GameObject* m_pParent{};
		std::vector<std::unique_ptr<BaseComponent>> m_upComponentVec{};
		std::vector<GameObject*> m_pChildrenVec{};

		std::string m_Name;
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
	inline std::enable_if_t<std::is_base_of_v<BaseComponent, TypeToAdd>, TypeToAdd*> 
		GameObject::AddComponent()
	{
		m_upComponentVec.emplace_back(std::move(std::make_unique<TypeToAdd>(this)));

		return dynamic_cast<TypeToAdd*>(m_upComponentVec.back().get());
	}



	template<typename TypeToGet>
	inline std::enable_if_t<std::is_base_of_v<BaseComponent, TypeToGet>, TypeToGet*>
		GameObject::GetComponentOfType() const
	{
		for (const auto& c : m_upComponentVec)
		{
			if (TypeToGet* pComponent = dynamic_cast<TypeToGet*>(c.get()))
				return pComponent;
		}
		return nullptr;
	}

	template<typename TypeToGet>
	inline std::vector<std::enable_if_t<std::is_base_of_v<BaseComponent, TypeToGet>, TypeToGet*>>
		 GameObject::GetAllComponentsOfType() const
	{
		std::vector<TypeToGet*> componentsVec{};
		for (const auto& c: m_upComponentVec)
		{
			if (TypeToGet* pComponent = dynamic_cast<TypeToGet*>(c.get()))
				componentsVec.emplace_back(pComponent);
		}
		return componentsVec;
	}

}
