#pragma once
#include "Core/Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void SetActiveGameScene(const std::string& sceneName);
		void NextScene();
		void PreviousScene();
		Scene* GetActiveScene() const { return m_shpActiveScene.get(); }


	private:
		friend class Singleton<SceneManager>;
		friend class GEngine;
		SceneManager() = default;

		void Initialize();
		void Update();
		void FixedUpdate() const;
		void Render() const;
		void RenderImGui();
		void UpdateSceneGraph();

		std::vector<std::shared_ptr<Scene>> m_shpScenes;
		std::shared_ptr <Scene> m_shpActiveScene{}, m_shpNextScene{};


	};
}
