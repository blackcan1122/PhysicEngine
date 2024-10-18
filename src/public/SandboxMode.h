#pragma once
#include "Core.h"
#include "GameMode.h"
#include "BaseRectangle.h"
#include "BaseCircle.h"
#include "Tickable.h"
#include "Physic.hpp"
#include "EventDispatcher.hpp"

class SandboxMode : public GameMode
{
public:
	SandboxMode();
	~SandboxMode() override;

	void Update() override;
	void SetName(std::string NewName) override;
	std::string GetName() override;

protected:
	float m_DeltaTime = 0;

private:
	std::string Name;

	std::vector<std::shared_ptr<BaseRectangle>> RuntimeRectangles;
	std::vector<std::shared_ptr<BaseCircle>> RuntimeCircles;

	std::shared_ptr<BaseRectangle> MyRectangle;
	std::shared_ptr<BaseRectangle> MyRectangle2;

	bool helper = false;
	int AmountOfBalls = 1;

	// Creating PhysicEngineObject
	PhysicEngine PhysicEngineObj;

	EventDispatcher Dispatcher;
};