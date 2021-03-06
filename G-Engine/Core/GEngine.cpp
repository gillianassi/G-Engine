#include "GEnginePCH.h"
#include "GEngine.h"

#include <steam_api.h>
#include <thread>
#include <chrono>

#include "Core/Renderer.h"
#include "ResourceManagement/ResourceManager.h"
#include "SceneGraph/SceneManager.h"
#include "Input/InputManager.h"
#include "Core/Time.h"

#include "Audio/BaseAudio.h"
#include "ResourceManagement/Locator.h"

#include "b2_world.h"


using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::GEngine::Initialize()
{

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../BurgerTime/Resources/");

	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}



void dae::GEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::GEngine::Run()
{
	Initialize();


	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		Time time;
		bool doContinue = true;
		float lag = 0.0f;

		// GameLoop
		while (doContinue)
		{
			time.HandleTimeCalculations();
			int nrOfUpdates = 0;
			lag += Time::deltaTime;
			doContinue = input.ProcessInput();

			// handle init, enable, disable, and remove
			sceneManager.UpdateSceneGraph();

			// Fixed Update
			// MaxNrOfUpdates ensures you can escape the loop if there is too much lag
			while (lag >= Time::fixedTimeStep && nrOfUpdates <= m_MaxNrOfUpdatesPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= Time::fixedTimeStep;
				++nrOfUpdates;
			}

			sceneManager.Update();

			renderer.StartDraw();
			sceneManager.RenderImGui();
			sceneManager.Render();

			renderer.Render();

			renderer.EndDraw();
			

			//SteamAPI_RunCallbacks();


			// Sleep if faster than the minimum miliseconds per frame (max fps)
			const auto sleepTime = time.GetStartFrame() + chrono::milliseconds(m_MinMsPerFrame) - chrono::high_resolution_clock::now();
			if (sleepTime >= sleepTime.zero())
			{
				std::this_thread::sleep_for(sleepTime);
			}

		}
	}

	Cleanup();
}


