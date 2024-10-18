#pragma once
#include "Core.h"

class GameMode
{
public:
	GameMode();
	virtual ~GameMode() = default;

	virtual void Update();
	virtual void SetName(std::string Name);
	virtual std::string GetName();

protected:
	float m_DeltaTime = 0;

private:
	std::string Name;
};