#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @class Observer
 * @brief Template abstract class for the Observer in the Observer Pattern.
 *
 * This templated abstract class defines the update method that all observers must implement.
 * It allows objects to be notified of changes in subject state with data of type T.
 *
 * @tparam T The type of data passed during the update notification.
 */
template <typename T>
class Observer
{
public:
	/**
	 * @brief Pure virtual method to be implemented by observers.
	 * @param data The data passed by the subject when notifying observers.
	 */
	virtual void update(T data) = 0;
};

#endif // OBSERVER_H