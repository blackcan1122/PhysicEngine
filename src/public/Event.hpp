#pragma once
#include "Core.h"

class Event
{
protected:
	virtual ~Event() = default;
public:
	virtual std::string GetName() const = 0;
};