#include "Physic.hpp"
#include "Tickable.h"
#include <cmath>

void PhysicEngine::Tick(float Deltatime)
{
	ApplyGravity(Deltatime);
}

void PhysicEngine::SetIsControllable(bool Status)
{
}

bool PhysicEngine::GetGravityAffected()
{
	return false;
}

void PhysicEngine::SetPosition(Vector2 NewPos)
{
	return;
}

void PhysicEngine::CalculateGravity(float Gravity, float Deltatime)
{
}


void PhysicEngine::CollectAllObjectsForGravity()
{
	GravityAffected.clear();

	std::vector<Tickable*> TickablesObj = TickableFactory::GetTickables();

	for (const auto& Object : TickablesObj)
	{
		if (Object == this)
		{
			//std::cout << "Own Reference" << std::endl;
			continue;
		}
		// Somehow all objects except self reference land here
		if (Object->GetGravityAffected() == false)
		{
			//std::cout << Object->GetGravityAffected() << std::endl;
			//std::cout << "Not Gravity" << std::endl;
			continue;
		}
		GravityAffected.push_back(Object);
	}
}

void PhysicEngine::CleanUp()
{
	GravityAffected.clear();
}

void PhysicEngine::ApplyGravity(float Deltatime)
{
	for (auto& GravityObjects : GravityAffected)
	{
		GravityObjects->CalculateGravity(Gravity.y, Deltatime);
	}

	
}