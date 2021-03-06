#include "BurgerTimePCH.h"
#include "BurgerTimeGame.h"

// Engine Includes
#include <Core/Time.h>

#include <SceneGraph/SceneManager.h>
#include <SceneGraph/GameObject.h>
#include <SceneGraph/Scene.h>

#include <ResourceManagement/ResourceManager.h>

#include <Input/InputManager.h>
#include <Input/Command.h>

#include <EngineComponents/RenderComponent.h>
#include <EngineComponents/TransformComponent.h>
#include <EngineComponents/FPSComponent.h>
#include <EngineComponents/RigidBodyComponent.h>
#include <EngineComponents/BoxColliderComponent.h>
#include <EngineComponents/AnimatorComponent.h>
#include <Core/Physics.h>

#include <Audio/BaseAudio.h>
#include <ResourceManagement/Locator.h>

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
	auto go = scene.AddChild("background");
	go->AddComponent<RenderComponent>();
	go->GetComponentOfType<RenderComponent>()->SetTexture("background.jpg");
	go->GetComponentOfType<TransformComponent>()->SetPosition(0, 0);


	go = scene.AddChild("logo");
	go->AddComponent<RenderComponent>();
	go->GetComponentOfType<RenderComponent>()->SetTexture("logo.png");
	go->GetComponentOfType<TransformComponent>()->SetPosition(216, 180);

	auto title = scene.AddChild("Title");
	title->AddComponent<RenderComponent>();
	title->GetComponentOfType<TransformComponent>()->SetPosition(80, 20);
	title->AddComponent<TextComponent>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	title->GetComponentOfType<TextComponent>()->SetFont(font);
	title->GetComponentOfType<TextComponent>()->SetText("Programming 4 Assignment");

	auto rigidBody = title->AddComponent<dae::RigidBodyComponent>();
	rigidBody->SetRigidBodyType(dae::RigidBodyComponent::RigidBodyType::Dynamic);
	//auto boxCollision= title->AddComponent<BoxColliderComponent>();
	//title->AddComponent<RigidBodyComponent>();
	title->AddComponent<BoxColliderComponent>();
	

	go = title->AddChild("fpsCounter");
	go->AddComponent<RenderComponent>();
	go->GetComponentOfType<TransformComponent>()->SetPosition(20, 50);
	auto pos = go->GetComponentOfType<TransformComponent>()->GetPosition();
	std::cout << "pos: " << pos.x << ", " << pos.y << std::endl;
	go->AddComponent<TextComponent>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go->GetComponentOfType<TextComponent>()->SetFont(font);
	go->GetComponentOfType<TextComponent>()->SetText("XX FPS");
	go->AddComponent<FPSComponent>();

	go = scene.AddChild("platform");
	go->GetTransform()->SetPosition(80, 50);



	float platformScale = 3.f;
	for (size_t i = 0; i < 10; i++)
	{
		// create game object
		go = scene.AddChild("platform" + i);
		// place platform
		go->GetTransform()->SetPosition(10.f+ 16.f * i * platformScale, 100.f);
		// create physics
		rigidBody = go->AddComponent<dae::RigidBodyComponent>();

		dae::RigidBodyComponent::RigidBodyDescription desc{};
		desc.position = go->GetTransform()->GetWorldPosition();
		desc.type = dae::RigidBodyComponent::RigidBodyType::Static;
		rigidBody->SetInitialDescription(desc);
		auto collider = go->AddComponent<BoxColliderComponent>();
		BoxColliderComponent::BoxColliderDescr colliderDesc{};
		colliderDesc.Width = 16.f * platformScale;
		colliderDesc.Height = 4.f * platformScale;
		collider->SetInitialDescription(colliderDesc);
		// render
		auto visuals = go->AddChild("visuals" + 1);
		RenderComponent* renderer = visuals->AddComponent<RenderComponent>();
		renderer->SetTexture("Textures/Level/Platform.png");
		renderer->SetScale(platformScale, platformScale);
		visuals->GetTransform()->SetPosition(-8.f * platformScale, - 1.f * platformScale);
	}

	// Week 5
	// Achievment Manager
	auto achievement = scene.AddChild("achievement");
	auto achievementComponent = achievement->AddComponent<AchievementComponent>();

	// Player 1 Life display
	auto player1LiveDisplay = scene.AddChild("player1LiveDisplay");
	player1LiveDisplay->AddComponent<RenderComponent>();
	auto transformComponent = player1LiveDisplay->GetComponentOfType<TransformComponent>();
	transformComponent->SetPosition(0.0f, 100.0f);
	auto textComponent = player1LiveDisplay->AddComponent<TextComponent>();
	textComponent->SetText("Lives: X");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 255, 255, 0 });
	LivesComponent* Player1Lives = player1LiveDisplay->AddComponent<LivesComponent>();

	// Player1 Actor
	auto peterPepper1 = scene.AddChild("peterPepper1");
	peterPepper1->AddComponent<RenderComponent>();
	peterPepper1->AddComponent<dae::AnimatorComponent>();
	auto peterPepper1Component = peterPepper1->AddComponent<PeterPepperComponent>();
	peterPepper1Component->AddObserver(Player1Lives);
	rigidBody = peterPepper1->AddComponent<dae::RigidBodyComponent>();
	dae::RigidBodyComponent::RigidBodyDescription desc{};
	desc.position = peterPepper1->GetTransform()->GetWorldPosition();
	desc.type = dae::RigidBodyComponent::RigidBodyType::Dynamic;
	rigidBody->SetInitialDescription(desc);
	peterPepper1->AddComponent<BoxColliderComponent>();


	// Player1 Score Display
	auto player1Score = scene.AddChild("player1Score");
	transformComponent = player1Score->AddComponent<TransformComponent>();
	transformComponent->SetPosition(0.0f, 200.0f);
	textComponent = player1Score->AddComponent<TextComponent>();
	textComponent->SetText("Score: XX");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 255, 255, 0 });
	player1Score->AddComponent<RenderComponent>();
	auto Player1scoreComponent = player1Score->AddComponent<ScoreComponent>();
	Player1scoreComponent->AddObserver(achievementComponent);
;
	// Player 2 Life display
	auto player2LiveDisplay = scene.AddChild("player2LiveDisplay");
	player2LiveDisplay->AddComponent<RenderComponent>();
	transformComponent = player2LiveDisplay->GetComponentOfType<TransformComponent>();
	transformComponent->SetPosition(0.0f, 300.0f);
	textComponent = player2LiveDisplay->AddComponent<TextComponent>();
	textComponent->SetText("Lives: 3");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 0, 100, 100 });
	LivesComponent* Player2Lives = player2LiveDisplay->AddComponent<LivesComponent>();

	// Player 2 Actor
	auto peterPepper2 = scene.AddChild("peterPepper2");
	auto peterPepper2Component = peterPepper2->AddComponent<PeterPepperComponent>();
	peterPepper2Component->AddObserver(Player2Lives);
	peterPepper2->AddComponent<RenderComponent>();
	peterPepper2->AddComponent<dae::AnimatorComponent>();


	// Player2 Score Display
	auto player2Score = scene.AddChild("player2Score");
	transformComponent = player2Score->GetComponentOfType<TransformComponent>();
	transformComponent->SetPosition(0.0f, 400.0f);
	textComponent = player2Score->AddComponent<TextComponent>();
	textComponent->SetText("Score: XX");
	textComponent->SetFont(font);
	textComponent->SetColor(SDL_Color{ 0, 100, 100 });
	player2Score->AddComponent<RenderComponent>();
	auto Player2scoreComponent = player2Score->AddComponent<ScoreComponent>();

	// Enemy 1 
	auto enemy1 = scene.AddChild("enemy1");
	auto enemyComp = enemy1->AddComponent<EnemyComponent>();
	enemyComp->AddObserver(Player1scoreComponent);
	// Enemy 2
	auto enemy2 = scene.AddChild("enemy2");
	enemyComp = enemy2->AddComponent<EnemyComponent>();
	enemyComp->AddObserver(Player2scoreComponent);


	// SHARED Burger 
	auto burger = scene.AddChild("burger");
	auto burgerComp = burger->AddComponent<BurgerComponent>();
	burgerComp->AddObserver(Player2scoreComponent);
	burgerComp->AddObserver(Player1scoreComponent);

	std::cout << "Controls:" << std::endl;
	std::cout << "\t\t[A] - Player Dies\t\t- Unique" << std::endl;
	std::cout << "\t\t[B] - Enemy Dies\t\t- Unique" << std::endl;
	std::cout << "\t\t[Y] - Enemy Revives\t\t- Unique" << std::endl;
	std::cout << "\t\t[X] - Burger drops\t\t- Shared" << std::endl;
	// Instantiate Controls:
	//p1
	InputManager::GetInstance().AddInputCommand<MoveLeftCommand>
		('a', ControllerButton::DPAD_LEFT, ActivationState::BTN_HOLD, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<MoveRightCommand>
		('d', ControllerButton::DPAD_RIGHT, ActivationState::BTN_HOLD, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<MoveUpCommand>
		('w', ControllerButton::DPAD_UP, ActivationState::BTN_HOLD, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<MoveDownCommand>
		('s', ControllerButton::DPAD_DOWN, ActivationState::BTN_HOLD, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<StopMovementCommand>
		('a', ControllerButton::DPAD_LEFT, ActivationState::BTN_UP, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<StopMovementCommand>
		('d', ControllerButton::DPAD_RIGHT, ActivationState::BTN_UP, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<StopMovementCommand>
		('w', ControllerButton::DPAD_UP, ActivationState::BTN_UP, peterPepper1, InputManager::PlayerIndex::P1);
	InputManager::GetInstance().AddInputCommand<StopMovementCommand>
		('s', ControllerButton::DPAD_DOWN, ActivationState::BTN_UP, peterPepper1, InputManager::PlayerIndex::P1);

	//p2
	InputManager::GetInstance().AddInputCommand<PlayerDieCommand>
		(ControllerButton::ButtonA, ActivationState::BTN_HOLD,peterPepper2, InputManager::PlayerIndex::P2);
	InputManager::GetInstance().AddInputCommand<EnemyKillCommand>
		(ControllerButton::ButtonB, ActivationState::BTN_DOWN,enemy2, InputManager::PlayerIndex::P2);
	InputManager::GetInstance().AddInputCommand<ReviveEnemyCommand>
		(ControllerButton::ButtonY, ActivationState::BTN_DOWN,enemy2, InputManager::PlayerIndex::P2);
	//Shared
	InputManager::GetInstance().AddInputCommand<BurgerDropCommand>
		(ControllerButton::ButtonX, ActivationState::BTN_DOWN, burger, InputManager::PlayerIndex::ALL);

}