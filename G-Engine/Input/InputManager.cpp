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
	m_ActionCommandMaps = std::vector<ActionCommandsMap>(m_NrOfControllers);
	for (int i = 0; i < m_NrOfControllers; i++)
	{
		m_pControllers.emplace_back(std::move(std::make_unique<Controller>(i)));
	}
}


bool dae::InputManager::ProcessInput()
{ 
	// reset all key states
	for (auto& [key, state] : m_KeyStatesMap)
	{
		state.isDownThisFrame = false;
		state.isReleasedThisFrame = false;
	}

	// Process Keyboard
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) {
			return false;
		}

		char key = (char)e.key.keysym.sym;

		if (e.type == SDL_KEYDOWN)
		{
			m_KeyStatesMap[key] = KeyState{true, true, false};
		}
		if (e.type == SDL_KEYUP)
		{
			m_KeyStatesMap[key] = KeyState{ false, false, true };
		}
		
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
		}


		ImGui_ImplSDL2_ProcessEvent(&e);

	}
	// Process Controllers
	for (size_t controllerIndex = 0; controllerIndex < m_pControllers.size(); controllerIndex++)
	{
		m_pControllers[controllerIndex]->ProcessInput();
		// Handle both controller and keyboard
		HandleInput((unsigned int)controllerIndex);
	}
	return true;
}



void dae::InputManager::HandleInput(unsigned int controllerIdx)
{
	for (const auto& [buttonAction, command] : m_ActionCommandMaps[controllerIdx])
	{
		switch (buttonAction.behaviour)
		{
		case InputManager::ActivationState::BTN_DOWN:
			HandleBtnDown(buttonAction, command.get(), controllerIdx);
			break;
		case InputManager::ActivationState::BTN_UP:
			HandleBtnUp(buttonAction, command.get(), controllerIdx);
			break;
		case InputManager::ActivationState::BTN_HOLD:
			HandleBtnHold(buttonAction, command.get(), controllerIdx);
			break;
		default:
			break;
		}
	}
}

void dae::InputManager::HandleBtnDown(InputAction inputAction, Command* command, unsigned int controllerIdx)
{
	
	// if the controller is up, or
	if (m_pControllers[controllerIdx].get()->IsDownThisFrame(inputAction.button) || 
		m_KeyStatesMap[inputAction.sdlKey].isDownThisFrame)
	{
		command->Execute();
	}
}

void dae::InputManager::HandleBtnUp(InputAction inputAction, Command* command, unsigned int controllerIdx)
{
	if (m_pControllers[controllerIdx].get()->IsReleasedThisFrame(inputAction.button) ||
		m_KeyStatesMap[inputAction.sdlKey].isReleasedThisFrame)
	{
		command->Execute();
	}
}

void dae::InputManager::HandleBtnHold(InputAction inputAction, Command* command, unsigned int controllerIdx)
{
	if (m_pControllers[controllerIdx].get()->IsHoldingDown(inputAction.button) ||
		m_KeyStatesMap[inputAction.sdlKey].isHoldingDown)
	{
		command->Execute();
	}
}
