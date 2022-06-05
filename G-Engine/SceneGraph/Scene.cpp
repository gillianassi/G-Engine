#include "GEnginePCH.h"
#include "Scene.h"

#include "GameObject.h"
#include "EngineComponents/RenderComponent.h"
#include "Core/Physics.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

void dae::Scene::AddForInitialize(GameObject* pGameObject)
{
	m_UnInitializedObjects.emplace_back(pGameObject);
}

void dae::Scene::AddToRigidBodyQueue(RigidBodyComponent* pRigidBody)
{
	m_RigidBodyQueue.emplace_back(pRigidBody);
}

Scene::Scene(const std::string& name) :
	m_Name(name),
	m_ScenePhysics{new Physics()}
{}

Scene::~Scene()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		delete m_Objects[i];
		m_Objects[i] = nullptr;
	}
	m_Objects.clear();

	delete m_ScenePhysics;
	m_ScenePhysics = nullptr;
}

GameObject* Scene::AddChild(const std::string& name)
{
	// GameObj
	GameObject* pObject = new GameObject(name, nullptr, this);
	m_Objects.push_back(pObject);
	AddForInitialize(pObject);

	return pObject;
}

void Scene::Initialize() const
{
	if (m_IsInitialized)
		return;

	for(GameObject* object : m_Objects)
	{
		object->Initialize();
	}
}

void Scene::Update() const
{
	for(GameObject* object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate() const
{
	for (GameObject* object : m_Objects)
	{
		object->FixedUpdate();
	}

	m_ScenePhysics->Update();
}

void Scene::Render() const
{
	for (GameObject* object : m_Objects)
	{
		object->Render();
	}
}
void Scene::RenderImGui()
{
	for (GameObject* object : m_Objects)
	{
		object->RenderImGui();
	}
}

void dae::Scene::UpdateSceneGraph()
{
	for (GameObject* pChild : m_Objects)
	{
		if (pChild->IsMarkedForDestroy())
		{
			pChild->OnDestroy();
			delete pChild;
			pChild = nullptr;
		}
	}
	// Initialize all unInitialized Objects
	for (GameObject* pObj : m_UnInitializedObjects)
	{
		pObj->Initialize();
	}
	m_UnInitializedObjects.clear();

	// Add rigidbodies
	for (RigidBodyComponent* pRigidBody : m_RigidBodyQueue)
	{
		m_ScenePhysics->AddRigidBody(pRigidBody);
	}
	m_RigidBodyQueue.clear();

	// move all elements you want to erase to the end
	const auto beginEraseGameObjectItt = std::remove_if(m_Objects.begin(), m_Objects.end(),
		[](GameObject* pObject) { return pObject->IsMarkedForDestroy(); });
	// erase all those elements
	m_Objects.erase(beginEraseGameObjectItt, m_Objects.end());

	for (GameObject* pChild : m_Objects)
	{
		pChild->UpdateGameObjectState();
	}

}

void dae::Scene::RemoveChildFromChildVec(GameObject* go)
{
	auto childItt = std::find_if(m_Objects.begin(), m_Objects.end(), [go](GameObject* child)
		{
			return (child == go);
		});
	if (childItt != m_Objects.end())
	{
		m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), *childItt));
	}
}
