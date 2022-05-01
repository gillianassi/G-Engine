#include "GEnginePCH.h"
#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "xinput.lib")
#include <Windows.h>
#include <Xinput.h>

#include "Controller.h"

using namespace dae;
class Controller::ControllerImpl
{
public:
	ControllerImpl(int controllerIndex):
		m_Index{controllerIndex}
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}
	~ControllerImpl() = default;

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(m_Index, &m_CurrentState);
		// Set all buttons that changed to 1
		unsigned int buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		// All of those that are now high, are pressed
		m_ButtonsPressedThisFame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		// All of those that are now low, are released
		m_ButtonsReleasedThisFame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		// returns true if conected
		m_IsConnected = !result;
	}


	bool IsPressed(unsigned int button) const
	{
		return (m_CurrentState.Gamepad.wButtons & button);
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFame & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFame & button;
	}

	bool IsConnected() const
	{
		return m_IsConnected;
	}

	unsigned int GetControllerIndex()
	{
		return m_Index;
	}

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	unsigned int m_ButtonsPressedThisFame{};
	unsigned int m_ButtonsReleasedThisFame{};
	bool m_IsConnected{};
	int m_Index{};

};



dae::Controller::Controller(int id):
	m_pControllerImpl{nullptr}
{
	m_pControllerImpl = new ControllerImpl(id);
}

dae::Controller::~Controller()
{
	delete m_pControllerImpl;
	m_pControllerImpl = nullptr;
}

void dae::Controller::ProcessInput()
{
	m_pControllerImpl->Update();
}

bool dae::Controller::IsPressed(const ControllerButton& button) const
{
	return (m_pControllerImpl->IsPressed(static_cast<unsigned int>(button)));
}

bool dae::Controller::IsDownThisFrame(const ControllerButton& button) const
{
	return (m_pControllerImpl->IsDownThisFrame(static_cast<unsigned int>(button)));
}

bool dae::Controller::IsUpThisFrame(const ControllerButton& button) const
{
	return (m_pControllerImpl->IsUpThisFrame(static_cast<unsigned int>(button)));
}

bool dae::Controller::IsConnected() const
{
	return m_pControllerImpl->IsConnected();
}

unsigned int dae::Controller::GetIndex() const
{
	return m_pControllerImpl->GetControllerIndex();
}

