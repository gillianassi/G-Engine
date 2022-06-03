#include "GEnginePCH.h"
#include "Scene.h"
#include "G-Engine/SceneGraph/GameObject.h"

#include "EngineComponents/RenderComponent.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (object->GetComponentOfType<RenderComponent>())
		{
			auto renderComponent = object->GetComponentOfType<RenderComponent>();
			renderComponent->Render();
			renderComponent->RenderImGui();
		}
	}
}

