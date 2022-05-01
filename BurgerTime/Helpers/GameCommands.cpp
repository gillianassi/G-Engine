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
	m_pPlayer{ pPlayer->GetComponent<PeterPepperComponent>() }
{
}

void PlayerDieCommand::KillPlayer()
{
	m_pPlayer->Die();
}


EnemyKillCommand::EnemyKillCommand(dae::GameObject* pEnemy) :
	Command(),
	m_pEnemy{ pEnemy->GetComponent<EnemyComponent>() }
{
}

void EnemyKillCommand::KillEnemy()
{
	m_pEnemy->Die();
}

ReviveEnemyCommand::ReviveEnemyCommand(dae::GameObject* pEnemy) :
	Command(),
	m_pEnemy{ pEnemy->GetComponent<EnemyComponent>() }
{
}

void ReviveEnemyCommand::ReviveEnemy()
{
	m_pEnemy->Revive();
}

BurgerDropCommand::BurgerDropCommand(dae::GameObject* pBurger) :
	Command(),
	m_pBurger{ pBurger->GetComponent<BurgerComponent>() }
{
}

void BurgerDropCommand::DropBurger()
{
	m_pBurger->Drop();
}

ResetBurgerCommand::ResetBurgerCommand(dae::GameObject* pBurger) :
	Command(),
	m_pBurger{ pBurger->GetComponent<BurgerComponent>() }
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
