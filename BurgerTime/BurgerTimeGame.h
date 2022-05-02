#pragma once
#include "Core/GEngine.h"

//class Audio;
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
	//Audio* m_pAudio;
};