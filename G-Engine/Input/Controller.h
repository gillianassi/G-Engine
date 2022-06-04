#pragma once
namespace dae
{
	class Controller final
	{

	public:
		enum class ControllerButton
		{
			DPAD_UP = 0x0001,
			DPAD_DOWN = 0x0002,
			DPAD_LEFT = 0x0004,
			DPAD_RIGHT = 0x0008,
			START = 0x0010,
			BACK = 0x0020,
			LEFT_THUMB = 0x0040,
			RIGHT_THUMB = 0x0080,
			LEFT_SHOULDER = 0x0100,
			RIGHT_SHOULDER = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		explicit Controller(int id);
		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
		// Update the input
		// wrapper functions
		void ProcessInput();
		bool IsHoldingDown(const ControllerButton& button) const;
		bool IsDownThisFrame(const ControllerButton& button) const;
		bool IsReleasedThisFrame(const ControllerButton& button) const;

		// Own functions
		bool IsConnected() const;
		unsigned int GetIndex() const;

	private:
		// implementation
		class ControllerImpl;
		ControllerImpl* m_pControllerImpl;

	};
}

