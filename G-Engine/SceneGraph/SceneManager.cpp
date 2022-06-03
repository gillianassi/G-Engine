#include "GEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"

#include <algorithm>
#include <cassert>

void dae::SceneManager::Initialize()
{
	for (const auto& shpScene : m_shpScenes)
	{
		shpScene->Initialize();
	}
}

void dae::SceneManager::Update()
{
	if (m_shpNextScene != nullptr)
	{
		if (m_shpNextScene != m_shpActiveScene)
		{

			//Set New Scene
			m_shpActiveScene = m_shpNextScene;
		}

		m_shpNextScene = nullptr;
	}
	if (m_shpActiveScene == nullptr)
	{
		std::cerr << "No Active Scene Set!" << std::endl;
	}
	m_shpActiveScene->Update();
}

void dae::SceneManager::FixedUpdate() const
{
	if (m_shpActiveScene != nullptr)
		m_shpActiveScene->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	if (m_shpActiveScene != nullptr)
		m_shpActiveScene->Render();
}

void dae::SceneManager::RenderImGui()
{
	if (m_shpActiveScene != nullptr)
		m_shpActiveScene->RenderImGui();
}

void dae::SceneManager::UpdateSceneGraph()
{
	if (m_shpActiveScene != nullptr)
		m_shpActiveScene->UpdateSceneGraph();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& shpScene = std::shared_ptr<Scene>(new Scene(name));
	m_shpScenes.push_back(shpScene);

	shpScene->Initialize();

	if (m_shpActiveScene == nullptr && m_shpNextScene == nullptr)
		m_shpNextScene = shpScene;
	return *shpScene;
}

void dae::SceneManager::SetActiveGameScene(const std::string& sceneName)
{
	const auto it = std::ranges::find_if(m_shpScenes, [sceneName](const auto& pScene)
		{
			return std::strcmp(pScene->GetSceneName().c_str(), sceneName.c_str()) == 0;
		});

	if (it != m_shpScenes.end())
	{
		m_shpNextScene = *it;
	}
}

void dae::SceneManager::NextScene()
{
	for (size_t i = 0; i < m_shpScenes.size(); ++i)
	{
		if (m_shpScenes[i] == m_shpActiveScene)
		{
			const auto nextScene = ++i % m_shpScenes.size();
			m_shpNextScene = m_shpScenes[nextScene];
			break;
		}
	}
}

void dae::SceneManager::PreviousScene()
{
	const size_t maxScemeIdx = m_shpScenes.size() - 1;
	for (size_t i = 0; i < m_shpScenes.size(); ++i)
	{
		if (m_shpScenes[i] == m_shpActiveScene)
		{
			--i;
			if (i < 0) i = maxScemeIdx;
			m_shpNextScene = m_shpScenes[i];
			break;
		}
	}
}
