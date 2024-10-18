#pragma once
#include "Core.h"
#include "GameMode.h"

class StartMenu : public GameMode
{
public:
	StartMenu(float tick);
	~StartMenu() override = default;

	void Update();
	void SetName(std::string NewName) override;
	std::string GetName() override;
protected:

	float m_DeltaTime;
	
private:

	std::string Name = "StartingMenu";
};