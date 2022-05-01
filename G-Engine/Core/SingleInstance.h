#pragma once
#include <cassert>

template <typename T>
class SingleInstance
{
public:

	virtual ~SingleInstance() { instantiated = false; };

	SingleInstance(const SingleInstance& other) = delete;
	SingleInstance(SingleInstance&& other) = delete;
	SingleInstance& operator=(const SingleInstance& other) = delete;
	SingleInstance& operator=(SingleInstance&& other) = delete;

protected:
	SingleInstance() 
	{
		assert(!instantiated && "Error: Trying to create a second instance of a SingleInstance class");
		instantiated = true;
	};

private:
	static bool instantiated;
};

template <typename T>
bool SingleInstance<T>::instantiated = false;