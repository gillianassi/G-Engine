#include "BurgerTimePCH.h"
#include "BurgerTimeGame.h"

// Engine Includes
#include "Core/Time.h"

#include "SceneGraph/SceneManager.h"
#include "SceneGraph/GameObject.h"
#include "SceneGraph/Scene.h"

#include "ResourceManagement/ResourceManager.h"

#include "Input/InputManager.h"
#include "Input/Command.h"

#include "EngineComponents/RenderComponent.h"
#include "EngineComponents/TransformComponent.h"
#include "EngineComponents/FPSComponent.h"

#include "Audio/BaseAudio.h"
#include "ResourceManagement/Locator.h"

// Game includes
//#include "TrashTheCacheComponent.h"
#include "Components/PeterPepperComponent.h"
#include "Components/LivesComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/BurgerComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/AchievementComponent.h"

#include "Helpers/GameCommands.h"


using namespace std;
using namespace dae;
using ControllerButton = dae::Controller::ControllerButton;
using ActivationState = dae::InputManager::ActivationState;

BurgerTimeGame::BurgerTimeGame()
{
	m_pAudio = new BaseAudio();
	Locator::provide(m_pAudio);
}

BurgerTimeGame::~BurgerTimeGame()
{
	delete m_pAudio;
	m_pAudio = nullptr;
}

void BurgerTimeGame::LoadGame() const
{

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	// ToDo: add render component referebce ub text component
	// ToDo: add TetComponent in constructor of fpsComponent
	auto go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponentOfType<RenderComponent>()->SetTexture("background.jpg");
	go->AddComponent<TransformComponent>();
	go->GetComponentOfType<TransformComponent>()->SetPosition(0, 0);
	scene.Add(go);


	go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>();
	go->GetComponentOfType<RenderComponent>()->SetTexture("logo.png");
	go->AddComponent<TransformComponent>();
	go->GetComponentOfType<TransformComponent>()->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>();
	go->AddComponent<TransformComponent>();
	go->GetComponentOfType<TransformComponent>()->SetPosition(80, 20);
	go->AddComponent<TextComponent>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->GetComponentOfType<TextComponent>()->SetFont(font);
	go->GetComponentOfType<TextComponent>()->SetText("Programming 4 Assignment");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<RenderComponent>();
	go->AddComponent<TransformComponent>();
	go->GetComponentOfType<TransformComponent>()->SetPosition(10, 10);
	go->AddComponent<TextComponent>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go->GetComponentOfType<TextComponent>()->SetFont(font);
	go->GetComponentOfType<TextComponent>()->SetText("XX FPS");
	go->AddComponent<FPSComponent>();

	scene.Add(go);

	// Week 5
	// Achievment Manager
	auto achievement = std::make_shared<GameObject>();
	auto achievementComponent = achievement->AddComponent<AchievementComponent>();

	scene.Add(achievement);
	// Player 1 Life display
	auto player1LiveDisplay = std::make_shared<GameObject>();
	player1LiveDisplay->AddComponent<RenderComponent>();
	auto transformComponent = player1LiveDisplay->AddComponent<TransformComponent>();
	transformComponent->SetPosition(0.0f, 100.0f);
	auto textComponent = player1LiveDisplay->AddComponent<TextComponent>();
	textComponent->SetText("Lives: X");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 255, 255, 0 });
	LivesComponent* Player1Lives = player1LiveDisplay->AddComponent<LivesComponent>();
	scene.Add(player1LiveDisplay);

	// Player1 Actor
	auto peterPepper1 = std::make_shared<GameObject>();
	auto peterPepper1Component = peterPepper1->AddComponent<PeterPepperComponent>();
	peterPepper1Component->AddObserver(Player1Lives);
	scene.Add(peterPepper1);

	// Player1 Score Display
	auto player1Score = std::make_shared<GameObject>();
	transformComponent = player1Score->AddComponent<TransformComponent>();
	transformComponent->SetPosition(0.0f, 200.0f);
	textComponent = player1Score->AddComponent<TextComponent>();
	textComponent->SetText("Score: XX");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 255, 255, 0 });
	player1Score->AddComponent<RenderComponent>();
	auto Player1scoreComponent = player1Score->AddComponent<ScoreComponent>();
	Player1scoreComponent->AddObserver(achievementComponent);
	scene.Add(player1Score);

	scene.Add(peterPepper1);
	// Player 2 Life display
	auto player2LiveDisplay = std::make_shared<GameObject>();
	player2LiveDisplay->AddComponent<RenderComponent>();
	transformComponent = player2LiveDisplay->AddComponent<TransformComponent>();
	transformComponent->SetPosition(0.0f, 300.0f);
	textComponent = player2LiveDisplay->AddComponent<TextComponent>();
	textComponent->SetText("Lives: 3");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 0, 100, 100 });
	LivesComponent* Player2Lives = player2LiveDisplay->AddComponent<LivesComponent>();
	scene.Add(player2LiveDisplay);

	// Player 2 Actor
	auto peterPepper2 = std::make_shared<GameObject>();
	auto peterPepper2Component = peterPepper2->AddComponent<PeterPepperComponent>();
	peterPepper2Component->AddObserver(Player2Lives);
	scene.Add(peterPepper2);


	// Player2 Score Display
	auto player2Score = std::make_shared<GameObject>();
	transformComponent = player2Score->AddComponent<TransformComponent>();
	transformComponent->SetPosition(0.0f, 400.0f);
	textComponent = player2Score->AddComponent<TextComponent>();
	textComponent->SetText("Score: XX");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 0, 100, 100 });
	player2Score->AddComponent<RenderComponent>();
	auto Player2scoreComponent = player2Score->AddComponent<ScoreComponent>();
	Player2scoreComponent->AddObserver(achievementComponent);
	scene.Add(player2Score);

	// Enemy 1 
	auto enemy1 = std::make_shared<GameObject>();
	auto enemyComp = enemy1->AddComponent<EnemyComponent>();
	enemyComp->AddObserver(Player1scoreComponent);
	scene.Add(enemy1);
	// Enemy 2
	auto enemy2 = std::make_shared<GameObject>();
	enemyComp = enemy2->AddComponent<EnemyComponent>();
	enemyComp->AddObserver(Player2scoreComponent);
	scene.Add(enemy2);


	// SHARED Burger 
	auto burger = std::make_shared<GameObject>();
	auto burgerComp = burger->AddComponent<BurgerComponent>();
	burgerComp->AddObserver(Player2scoreComponent);
	burgerComp->AddObserver(Player1scoreComponent);
	scene.Add(burger);

	std::cout << "Controls:" << std::endl;
	std::cout << "\t\t[A] - Player Dies\t\t- Unique" << std::endl;
	std::cout << "\t\t[B] - Enemy Dies\t\t- Unique" << std::endl;
	std::cout << "\t\t[Y] - Enemy Revives\t\t- Unique" << std::endl;
	std::cout << "\t\t[X] - Burger drops\t\t- Shared" << std::endl;
	// Instantiate Controls:
	//p1
	InputManager::GetInstance().AddButtonCommand<PlayerDieCommand>
		(ControllerButton::ButtonA, ActivationState::BTN_DOWN, 0, peterPepper1.get());
	InputManager::GetInstance().AddButtonCommand<EnemyKillCommand>
		(ControllerButton::ButtonB, ActivationState::BTN_DOWN, 0, enemy1.get());
	InputManager::GetInstance().AddButtonCommand<ReviveEnemyCommand>
		(ControllerButton::ButtonY, ActivationState::BTN_DOWN, 0, enemy1.get());
	//p2
	InputManager::GetInstance().AddButtonCommand<PlayerDieCommand>
		(ControllerButton::ButtonA, ActivationState::BTN_DOWN, 1, peterPepper2.get());
	InputManager::GetInstance().AddButtonCommand<EnemyKillCommand>
		(ControllerButton::ButtonB, ActivationState::BTN_DOWN, 1, enemy2.get());
	InputManager::GetInstance().AddButtonCommand<ReviveEnemyCommand>
		(ControllerButton::ButtonY, ActivationState::BTN_DOWN, 1, enemy2.get());
	//Shared
	InputManager::GetInstance().AddButtonCommand<BurgerDropCommand>
		(ControllerButton::ButtonX, ActivationState::BTN_DOWN, burger.get());

}