#pragma once
#include "Core.h"
#include "Event.hpp"

class GravityEvent : public Event
{
public:
	GravityEvent() = default;

	std::string GetName() const override;
	void GetDispatcher(EventDispatcher* CurrentDispatcher);

	float Gravity;


};