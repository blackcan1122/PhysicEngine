#pragma once
#include <memory>
#include "Tickable.h"
#include "Event.hpp"

class CollisionEvent : public Event
{
public:
	CollisionEvent() = default;

	std::string GetName() const override;
	bool m_HasCollisionHappend;
	float CurrentDeltaTime;
	std::shared_ptr<Tickable> Rect1 = nullptr;
	std::shared_ptr<Tickable> Rect2 = nullptr;

};