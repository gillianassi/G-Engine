#pragma once
#include "Input/Command.h"

namespace dae
{
	class GameObject;
}

class PeterPepperComponent;
class EnemyComponent;
class BurgerComponent;

class PlayerDieCommand final : public Command
{
public:
	PlayerDieCommand(dae::GameObject* pPlayer);
	virtual ~PlayerDieCommand() override = default;
	void Execute() override { KillPlayer(); }
private:
	void KillPlayer();
	PeterPepperComponent* m_pPlayer;
};

class EnemyKillCommand final : public Command
{
public:
	EnemyKillCommand(dae::GameObject* pEnemy);
	virtual ~EnemyKillCommand() override = default;
	void Execute() override { KillEnemy(); }
private:
	void KillEnemy();
	EnemyComponent* m_pEnemy;
};
class ReviveEnemyCommand final : public Command
{
public:
	ReviveEnemyCommand(dae::GameObject* pEnemy);
	virtual ~ReviveEnemyCommand() override = default;
	void Execute() override { ReviveEnemy(); }
private:
	void ReviveEnemy();
	EnemyComponent* m_pEnemy;
};

class BurgerDropCommand final : public Command
{
public:
	BurgerDropCommand(dae::GameObject* pBurger);
	virtual ~BurgerDropCommand() override = default;
	void Execute() override { DropBurger(); }
private:
	void DropBurger();
	BurgerComponent* m_pBurger;
};
class ResetBurgerCommand final : public Command
{
public:
	ResetBurgerCommand(dae::GameObject* pBurger);
	virtual ~ResetBurgerCommand() override = default;
	void Execute() override { ResetBurger(); }
private:
	void ResetBurger();
	BurgerComponent* m_pBurger;
};
//
//class GetAchievementCommand final : public Command
//{
//public:
//	GetAchievementCommand() = default;
//	virtual ~GetAchievementCommand() override = default;
//	void Execute() override { GetAchievement(); }
//private:
//	void GetAchievement();
//};