#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer/Observer.h"

// Standard Library Include
#include <vector>
#include <algorithm>

template <typename T>
class Observable
{
public:
	void addObserver(Observer<T>* observer);
	void removeObserver(Observer<T>* observer);

	void notifyObservers(T data);

protected:
	std::vector<Observer<T>*> observers;
};

#endif // OBSERVABLE_H