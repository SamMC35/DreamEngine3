
#ifndef DREAM_COLLECTIONS_H
#define DREAM_COLLECTIONS_H
#include <list>

#include "menu_service.h"

template<typename T>
struct CircularList {
	std::list<T> data;

	typename std::list<T>::iterator next(typename std::list<T>::iterator it) {
		return (++it == data.end()) ? data.begin() : it;
	}

	typename std::list<T>::iterator prev(typename std::list<T>::iterator it) {
		return (it == data.begin()) ? --data.end() : --it;
	}

	typename std::list<T>::iterator begin() {
		return data.begin();
	}

	typename std::list<T>::iterator end() {
		return data.end();
	}


	T get(typename std::list<T>::iterator it) {
		return *it;
	}

	void add(T singleData) {
		data.push_back(singleData);
	}
};
#endif //DREAM_COLLECTIONS_H
