#pragma once

#include <memory>
#include <vector>
#include <map>
#include <unordered_map>

#include "Command.h"
#include "Controller.h"
#include "Core/Singleton.h"

namespace dae
{
	using ControllerButton = Controller::ControllerButton;
	class GameObject;
	class InputManager : public Singleton<InputManager>
	{
	public:

		enum class PlayerIndex
		{
			P1 = 0,
			P2 = 1,
			P3 = 2,
			P4 = 3,
			ALL = 4
		};

		enum class ActivationState
		{
			BTN_DOWN,
			BTN_UP,
			BTN_HOLD
		};

		struct KeyState
		{
			KeyState(bool isDown = false, bool isPressed = false, bool isReleased = false)
				: isHoldingDown{ isDown }
				, isDownThisFrame{ isPressed }
				, isReleasedThisFrame{ isReleased }
			{
			}
			bool isHoldingDown = false;
			bool isDownThisFrame = false;
			bool isReleasedThisFrame = false;
		};

		explicit InputManager();
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;


		// Own functions
		bool ProcessInput();

		template<class myCommand>
		void AddInputCommand(char sdlInput, const ControllerButton& button, const ActivationState& state, GameObject* gameObject, PlayerIndex playerIndex = PlayerIndex::P1);
		
		template<class myCommand>
		void AddInputCommand(const ControllerButton& button, const ActivationState& state, GameObject* gameObject, PlayerIndex playerIndex = PlayerIndex::P1);
		
		template<class myCommand>
		void AddInputCommand(char sdlInput, const ActivationState& state, GameObject* gameObject, PlayerIndex playerIndex = PlayerIndex::P1);

	private:
		struct InputAction
		{
			char sdlKey;
			ControllerButton button;
			ActivationState behaviour;

			InputAction(char _sdlKey, ControllerButton _button, ActivationState _behaviour) :
				sdlKey{ _sdlKey },
				button{ _button },
				behaviour{ _behaviour }
			{}

			bool operator<(const InputAction& rhs) const
			{
				return button < rhs.button;
			}
		};
		using ControllerCommandsPair = std::pair<InputAction, std::unique_ptr<Command>>;
		using ActionCommandsMap = std::map<InputAction, std::unique_ptr<Command>>;
		using KeyStatePair = std::pair<char, KeyState>;
		using KeyStateMap = std::unordered_map<char, KeyState>;





		void HandleInput(unsigned int controllerIdx);
		void HandleBtnDown(InputAction input, Command* command, unsigned int controllerIdx);
		void HandleBtnUp(InputAction input, Command* command, unsigned int controllerIdx);
		void HandleBtnHold(InputAction input, Command* command, unsigned int controllerIdx);


		// variables
		

		int m_NrOfControllers;
		std::vector<ActionCommandsMap> m_ActionCommandMaps;
		KeyStateMap m_KeyStatesMap;
		std::vector<std::unique_ptr<Controller>> m_pControllers;
	};


	template<class myCommand>
	inline void InputManager::AddInputCommand(char sdlInput, const ControllerButton& button, const ActivationState& state, GameObject* gameObject, PlayerIndex playerIndex)
	{
		InputAction inputAction = InputAction(sdlInput, button, state);
		if (int(playerIndex) < m_NrOfControllers)
		{
			m_ActionCommandMaps[int(playerIndex)].insert(ControllerCommandsPair(inputAction, std::make_unique<myCommand>(gameObject)));

		}
		else
		{
			for (size_t i = 0; i < m_ActionCommandMaps.size(); i++)
			{
				m_ActionCommandMaps[i].insert(ControllerCommandsPair(inputAction, std::make_unique<myCommand>(gameObject)));
			}
		}

		if (sdlInput != NULL)
		{
			// insert all keys to a map to easilly find
			m_KeyStatesMap.insert(KeyStatePair(sdlInput, KeyState()));
		}
	}

	template<class myCommand>
	inline void InputManager::AddInputCommand(const ControllerButton& button, const ActivationState& state, GameObject* gameObject, PlayerIndex playerIndex)
	{
		AddInputCommand<myCommand>(NULL, button, state, gameObject, playerIndex);
	}

	template<class myCommand>
	inline void InputManager::AddInputCommand(char sdlInput, const ActivationState& state, GameObject* gameObject, PlayerIndex playerIndex)
	{
		AddInputCommand<myCommand>(sdlInput, NULL, state, gameObject, playerIndex);
	}
}