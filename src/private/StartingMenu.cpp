#include "StartingMenu.h"

StartMenu::StartMenu(float tick)
{
	std::cout << tick << std::endl;
	m_DeltaTime = tick;

}

void StartMenu::Update()
{

	ClearBackground(GREEN);
}

void StartMenu::SetName(std::string NewName)
{
	Name = "Main Menu";
}

std::string StartMenu::GetName()
{
	return Name;
}


