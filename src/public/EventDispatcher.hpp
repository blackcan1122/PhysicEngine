#pragma once
#include "Core.h"

class EventDispatcher 
{
public:
	using EventCallback = std::function<void(std::shared_ptr<Event>)>;

	void AddListener(const std::string& EventName, EventCallback Callback);

	void Dispatch(std::shared_ptr<Event> EventToDispatch);

private:
	std::unordered_map<std::string, std::vector<EventCallback>> m_Listener;
};