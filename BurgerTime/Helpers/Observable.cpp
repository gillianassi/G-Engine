#include "BurgerTimePCH.h"
#include "Observable.h"
#include "Observer.h"

void Observable::AddObserver(Observer* observer)
{
	m_pObservers.insert(observer);
}

void Observable::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(observer);
}

void Observable::Notify(dae::BaseComponent* component, Event event)
{
	for (Observer* observer : m_pObservers)
	{
		observer->OnNotify(component, event);
	}
}
