#pragma once
struct SDL_Window;
namespace dae
{
	class GEngine 
	{
	public:
		void Initialize();
		virtual void LoadGame() const = 0;
		void Cleanup();
		void Run();
	private:
		static const int m_MinMsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		static const int m_MaxNrOfUpdatesPerFrame = 60; // This is simply a safeguard
		const float m_FixedTimeStep = 0.016f;
		SDL_Window* m_Window{};
	};
}