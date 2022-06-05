#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class RigidBodyComponent;
	class Physics;
	class Scene final
	{
	public:
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		GameObject* AddChild (const std::string& name);
		std::vector<GameObject*> GetSceneChildren() const
		{
			return m_Objects;
		}

		std::string GetSceneName() const { return m_Name; }
		
		Physics* GetScenePhysics() const { return m_ScenePhysics; }

		void AddForInitialize(GameObject* pGameObject);
		void AddToRigidBodyQueue(RigidBodyComponent* pRigidBody);

	private: 
		friend class SceneManager;
		explicit Scene(const std::string& name);

		void Initialize() const;
		void Update() const;
		void FixedUpdate() const;
		void Render() const;
		void RenderImGui();

		void UpdateSceneGraph();



		friend void dae::GameObject::ReParent(GameObject* pGo, bool hasCheckedHierarchy);
		friend void dae::GameObject::ReChild(GameObject* pGo, bool hasCheckedHierarchy);
		void RemoveChildFromChildVec(GameObject* go);

		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
		std::vector <GameObject*> m_UnInitializedObjects{};
		std::vector <RigidBodyComponent*> m_RigidBodyQueue{};

		bool m_IsInitialized{ false };

		static unsigned int m_IdCounter; 

		Physics* m_ScenePhysics;

	};

}
