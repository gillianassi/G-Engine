#pragma once
#include "Event.h"
#include <set>

namespace dae
{
	class BaseComponent;
}
class Observer;
class Observable
{
public:
	Observable() :
		m_pObservers() {}
	virtual ~Observable() = default;
	Observable(const Observable& other) = delete;
	Observable(Observable&& other) = delete;
	Observable& operator=(const Observable& other) = delete;
	Observable& operator=(Observable&& other) = delete;

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	virtual void Notify(dae::BaseComponent* component, Event event);

private:
	std::set<Observer*> m_pObservers;
};

