#pragma once
#include "Event.h"


namespace dae
{
	class BaseComponent;
}

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;

	virtual void OnNotify(dae::BaseComponent* entity, Event event) = 0;
};

