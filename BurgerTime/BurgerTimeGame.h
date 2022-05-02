#pragma once
#include "Core/GEngine.h"

class AudioInterface;
class BurgerTimeGame final : public dae::GEngine
{
public:
	BurgerTimeGame();
	~BurgerTimeGame();
	BurgerTimeGame(const BurgerTimeGame& other) = delete;
	BurgerTimeGame(BurgerTimeGame&& other) = delete;
	BurgerTimeGame& operator=(const BurgerTimeGame& other) = delete;
	BurgerTimeGame& operator=(BurgerTimeGame&& other) = delete;

	virtual void LoadGame() const override;

private:
	AudioInterface* m_pAudio;
};