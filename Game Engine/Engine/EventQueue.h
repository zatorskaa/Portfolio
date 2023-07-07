#pragma once

#include "Common.h"
#include "Event.h"

class EventQueue
{
public:
	//constructor
	EventQueue() { InitialiseFunctionMaps(); }

	//functions
	void popEvent(Event* _event);
	void InitialiseFunctionMaps();

	std::vector<Event*> events; //all created events

	std::unordered_map<SubsystemType, std::unordered_map<EventType, void(*)(Event*)>*> functionMap;
	std::vector< std::unordered_map<EventType, void(*)(Event*)>*> functionMaps;  //map of event types to event functions
};