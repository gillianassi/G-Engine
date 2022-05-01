#include "GEnginePCH.h"
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "xinput.lib")
#include <Windows.h>
#include <Xinput.h>

#include "InputManager.h"
#include "backends/imgui_impl_sdl.h"

using namespace dae;

dae::InputManager::InputManager():
	m_NrOfControllers{4}
{
	m_ControllerCommandMaps = std::vector<ControllerCommandsMap>(m_NrOfControllers);
	for (int i = 0; i < m_NrOfControllers; i++)
	{
		m_pControllers.emplace_back(std::move(std::make_unique<Controller>(i)));
	}
}


bool dae::InputManager::ProcessInput()
{ 
	for (size_t controllerIndex = 0; controllerIndex < m_pControllers.size(); controllerIndex++)
	{
		m_pControllers[controllerIndex]->ProcessInput();

		if (!m_pControllers[controllerIndex]->IsConnected()) continue;

		HandleInput((unsigned int)controllerIndex);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}

		ImGui_ImplSDL2_ProcessEvent(&e);

	}
	return true;
}



void dae::InputManager::HandleInput(unsigned int controllerIdx)
{
	for (const auto& [buttonAction, command] : m_ControllerCommandMaps[controllerIdx])
	{
		switch (buttonAction.behaviour)
		{
		case InputManager::ActivationState::BTN_DOWN:
			HandleBtnDown(buttonAction.button, command.get(), controllerIdx);
			break;
		case InputManager::ActivationState::BTN_UP:
			HandleBtnUp(buttonAction.button, command.get(), controllerIdx);
			break;
		case InputManager::ActivationState::BTN_HOLD:
			HandleBtnHold(buttonAction.button, command.get(), controllerIdx);
			break;
		default:
			break;
		}
	}
}

void dae::InputManager::HandleBtnDown(ControllerButton button, Command* command, unsigned int controllerIdx)
{
	if (m_pControllers[controllerIdx].get()->IsUpThisFrame(button))
	{
		command->Execute();
	}
}

void dae::InputManager::HandleBtnUp(ControllerButton button, Command* command, unsigned int controllerIdx)
{
	if (m_pControllers[controllerIdx].get()->IsUpThisFrame(button))
	{
		command->Execute();
	}
}

void dae::InputManager::HandleBtnHold(ControllerButton button, Command* command, unsigned int controllerIdx)
{
	if (m_pControllers[controllerIdx].get()->IsPressed(button))
	{
		command->Execute();
	}
}
