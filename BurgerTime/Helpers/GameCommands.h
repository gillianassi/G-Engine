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

class MoveLeftCommand final : public Command
{
public:
	MoveLeftCommand(dae::GameObject* pPeterPepper);
	virtual ~MoveLeftCommand() override = default;
	void Execute() override { MoveLeft(); }
private:
	void MoveLeft();
	PeterPepperComponent* m_pPlayer;
};

class MoveRightCommand final : public Command
{
public:
	MoveRightCommand(dae::GameObject* pPeterPepper);
	virtual ~MoveRightCommand() override = default;
	void Execute() override { MoveRight(); }
private:
	void MoveRight();
	PeterPepperComponent* m_pPlayer;
};

class MoveUpCommand final : public Command
{
public:
	MoveUpCommand(dae::GameObject* pPeterPepper);
	virtual ~MoveUpCommand() override = default;
	void Execute() override { MoveUp(); }
private:
	void MoveUp();
	PeterPepperComponent* m_pPlayer;
};

class MoveDownCommand final : public Command
{
public:
	MoveDownCommand(dae::GameObject* pPeterPepper);
	virtual ~MoveDownCommand() override = default;
	void Execute() override { MoveDown(); }
private:
	void MoveDown();
	PeterPepperComponent* m_pPlayer;
};

class StopMovementCommand final : public Command
{
public:
	StopMovementCommand(dae::GameObject* pPeterPepper);
	virtual ~StopMovementCommand() override = default;
	void Execute() override { StopMovement(); }
private:
	void StopMovement();
	PeterPepperComponent* m_pPlayer;
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