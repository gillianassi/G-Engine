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

	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

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

			// Fixed Update
			// MaxNrOfUpdates ensures you can escape the loop if there is too much lag
			while (lag >= m_FixedTimeStep && nrOfUpdates <= m_MaxNrOfUpdatesPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= m_FixedTimeStep;
				++nrOfUpdates;
			}

			sceneManager.Update();

			// pass lag / MS_PER_UPDATE (normalized)
			// 0 = start of previous frame, 1 = start of next frame 
			// This numer can be used to draw a fram [0...1[ frames ahead of time
			// This makes it frame independant 
			renderer.Render();

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


