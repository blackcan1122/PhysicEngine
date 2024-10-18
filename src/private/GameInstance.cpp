#include "GameInstance.h"
#include "StateMachine.h"
#include "GameMode.h"
#include "PongGameMod.h"
#include "StartingMenu.h"
#include "SandboxMode.h"

// Definition of the static member
GameInstance* GameInstance::Instance = nullptr;

GameInstance::GameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen)
	: m_ScreenWidth(ScreenWidth), m_ScreenHeight(Screenheight), m_TargetFps(TargetFps), m_Fullscreen(Fullscreen)
{
	std::cout << "GameInstance was Initialized" << std::endl;
}


void GameInstance::InitGameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen)
{
	if (Instance != nullptr)
	{
		std::cerr << "GameInstance was already initialized" << std::endl;
		return;
	}

	Instance = new GameInstance(ScreenWidth, Screenheight, TargetFps, Fullscreen);
	CreateWindow();
	GameLoop();
}

GameInstance* GameInstance::GetInstance()
{
	if (Instance != nullptr)
	{
		return Instance;
	}
	std::cerr << "GameInstance was not Created, please Call InitGameInstance first" << std::endl;
}


void GameInstance::CreateWindow()
{
	if (Instance->m_Fullscreen)
	{
		SetConfigFlags(FLAG_FULLSCREEN_MODE);
	}

	InitWindow(Instance->m_ScreenWidth, Instance->m_ScreenHeight, "GameWindow");
	SetTargetFPS(Instance->m_TargetFps);
}

void GameInstance::GameLoop()
{
	StateMachine ActiveStateMachine;
	ActiveStateMachine.RegisterState("Menu", []() {return new StartMenu(10); });
	ActiveStateMachine.RegisterState("Sandbox", []() {return new SandboxMode(); });
	ActiveStateMachine.RegisterState("Pong", []() {return new PongGameMod(); });

	ActiveStateMachine.ChangeState("Menu");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		if (IsKeyPressed(KEY_A))
		{
			ActiveStateMachine.ChangeState("Menu");
		}
		if (IsKeyPressed(KEY_S))
		{
			ActiveStateMachine.ChangeState("Sandbox");
		}
		if (IsKeyPressed(KEY_D))
		{
			ActiveStateMachine.ChangeState("Pong");
		}
		ActiveStateMachine.UpdateGameMode();
		EndDrawing();
	}
}
