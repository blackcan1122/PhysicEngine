#pragma once
#include "Core.h"

class GameInstance
{

private:
	GameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen);
	~GameInstance() = default;

	static GameInstance* Instance;

protected:

	/*
	*****************************
	* Window and Start Parameter
	*****************************
	*/

	int m_ScreenWidth;
	int m_ScreenHeight;
	int m_TargetFps;
	bool m_Fullscreen;


	/*
	*****************************
	* Methods
	*****************************
	*/

	static void CreateWindow();
	static void GameLoop();

public:

	GameInstance(const GameInstance&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;

	static void InitGameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen);
	static GameInstance* GetInstance();


};