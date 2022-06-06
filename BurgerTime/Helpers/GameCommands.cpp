#include "BurgerTimePCH.h"
#include "GameCommands.h"
#include <iostream>
#include "Components/PeterPepperComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/BurgerComponent.h"
#include "SceneGraph/GameObject.h"



// #include <steam_api.h>

PlayerDieCommand::PlayerDieCommand(dae::GameObject* pPlayer) :
	Command(),
	m_pPlayer{ pPlayer->GetComponentOfType<PeterPepperComponent>() }
{
}

void PlayerDieCommand::KillPlayer()
{
	m_pPlayer->Die();
}


EnemyKillCommand::EnemyKillCommand(dae::GameObject* pEnemy) :
	Command(),
	m_pEnemy{ pEnemy->GetComponentOfType<EnemyComponent>() }
{
}

void EnemyKillCommand::KillEnemy()
{
	m_pEnemy->Die();
}

ReviveEnemyCommand::ReviveEnemyCommand(dae::GameObject* pEnemy) :
	Command(),
	m_pEnemy{ pEnemy->GetComponentOfType<EnemyComponent>() }
{
}

void ReviveEnemyCommand::ReviveEnemy()
{
	m_pEnemy->Revive();
}

BurgerDropCommand::BurgerDropCommand(dae::GameObject* pBurger) :
	Command(),
	m_pBurger{ pBurger->GetComponentOfType<BurgerComponent>() }
{
}

void BurgerDropCommand::DropBurger()
{
	m_pBurger->Drop();
}

ResetBurgerCommand::ResetBurgerCommand(dae::GameObject* pBurger) :
	Command(),
	m_pBurger{ pBurger->GetComponentOfType<BurgerComponent>() }
{
}

void ResetBurgerCommand::ResetBurger()
{
	m_pBurger->ResetBurger();
}

//void GetAchievementCommand::GetAchievement()
//{
//	//SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
//	//SteamUserStats()->StoreStats();
//}

MoveLeftCommand::MoveLeftCommand(dae::GameObject* pPeterPepper):
	Command(),
	m_pPlayer{ pPeterPepper->GetComponentOfType<PeterPepperComponent>()}
{
}

void MoveLeftCommand::MoveLeft()
{
	m_pPlayer->MoveLeft();
}

MoveRightCommand::MoveRightCommand(dae::GameObject* pPeterPepper):
	Command(),
	m_pPlayer{ pPeterPepper->GetComponentOfType<PeterPepperComponent>()}
{
}

void MoveRightCommand::MoveRight()
{
	m_pPlayer->MoveRight();
}

MoveUpCommand::MoveUpCommand(dae::GameObject* pPeterPepper):
	Command(),
	m_pPlayer{ pPeterPepper->GetComponentOfType<PeterPepperComponent>()}
{
}

void MoveUpCommand::MoveUp()
{
	m_pPlayer->MoveUp();
}

MoveDownCommand::MoveDownCommand(dae::GameObject* pPeterPepper):
	Command(),
	m_pPlayer{ pPeterPepper->GetComponentOfType<PeterPepperComponent>()}
{
}

void MoveDownCommand::MoveDown()
{
	m_pPlayer->MoveDown();
}

StopMovementCommand::StopMovementCommand(dae::GameObject* pPeterPepper) :
	Command(),
	m_pPlayer{ pPeterPepper->GetComponentOfType<PeterPepperComponent>() }
{
}

void StopMovementCommand::StopMovement()
{
	m_pPlayer->StopMovement();
}
