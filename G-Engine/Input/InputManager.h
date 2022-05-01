#pragma once

#include <memory>
#include <vector>
#include <map>

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

		enum class ActivationState
		{
			BTN_DOWN,
			BTN_UP,
			BTN_HOLD
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
		void AddButtonCommand(const ControllerButton& button, const ActivationState& state, GameObject* gameObject);
		template<class myCommand>
		void AddButtonCommand(const ControllerButton& button, const ActivationState& state, unsigned int controllerIdx, GameObject* gameObject);


		// TODO multiple controllers

		// TODO hide all internals

		// while using multiple controllers, make sure\
		// that even when disconecting, your state gets updated

	private:
		struct ButtonAction
		{
			ControllerButton button;
			ActivationState behaviour;

			ButtonAction(ControllerButton _button, ActivationState _behaviour) :
				button{ _button },
				behaviour{ _behaviour }
			{}

			bool operator<(const ButtonAction& rhs) const
			{
				return button < rhs.button;
			}
		};
		using ControllerCommandsPair = std::pair<ButtonAction, std::unique_ptr<Command>>;
		using ControllerCommandsMap = std::map<ButtonAction, std::unique_ptr<Command>>;





		void HandleInput(unsigned int controllerIdx);
		void HandleBtnDown(ControllerButton button, Command* command, unsigned int controllerIdx);
		void HandleBtnUp(ControllerButton button, Command* command, unsigned int controllerIdx);
		void HandleBtnHold(ControllerButton button, Command* command, unsigned int controllerIdx);


		// variables
		

		int m_NrOfControllers;
		std::vector<ControllerCommandsMap> m_ControllerCommandMaps;
		std::vector<std::unique_ptr<Controller>> m_pControllers;
	};


	template<class myCommand>
	inline void InputManager::AddButtonCommand(const ControllerButton& button, const ActivationState& state, GameObject* gameObject)
	{
		for (size_t i = 0; i < m_ControllerCommandMaps.size(); i++)
		{
			m_ControllerCommandMaps[i].insert(ControllerCommandsPair(ButtonAction(button, state), std::make_unique<myCommand>(gameObject)));

		}
	}

	template<class myCommand>
	inline void InputManager::AddButtonCommand(const ControllerButton& button, const ActivationState& state, unsigned int controllerIdx, GameObject* gameObject)
	{
		if (controllerIdx < m_ControllerCommandMaps.size())
		{
			m_ControllerCommandMaps[controllerIdx].insert(ControllerCommandsPair(ButtonAction(button, state), std::make_unique<myCommand>(gameObject)));
		}
	}

}