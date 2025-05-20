#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "Observer/Observer.h"

// Standard Library Include
#include <vector>
#include <algorithm>

/**
 * @class Observable
 * @brief Template class for the Subject in the Observer Pattern.
 *
 * This class maintains a list of observers and provides mechanisms to add, remove,
 * and notify them of changes. It allows objects (observers) to subscribe to changes
 * in the observable's state.
 *
 * @tparam T The type of data passed to observers upon notification.
 */
template <typename T>
class Observable
{
public:
	/**
	 * @brief Adds an observer to the list.
	 * @param observer Pointer to the observer to be added.
	 */
	void addObserver(Observer<T> *observer);

	/**
	 * @brief Removes an observer from the list.
	 * @param observer Pointer to the observer to be removed.
	 */
	void removeObserver(Observer<T> *observer);

	/**
	 * @brief Notifies all registered observers with the provided data.
	 * @param data The data to send to each observer.
	 */
	void notifyObservers(T data);

protected:
	std::vector<Observer<T> *> observers;
};

#endif // OBSERVABLE_H