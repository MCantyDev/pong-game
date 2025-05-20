#include "Observer/Observable.h"

#include "drawables/Paddle.h"

template <typename T>
void Observable<T>::addObserver(Observer<T> *observer)
{
	observers.push_back(observer);
}

template <typename T>
void Observable<T>::removeObserver(Observer<T> *observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

template <typename T>
void Observable<T>::notifyObservers(T data)
{
	for (Observer<T> *observer : observers)
	{
		observer->update(data);
	}
}

template class Observable<PaddleSide>;