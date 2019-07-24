#pragma once
#include <exception>
#include <iostream>

template<typename T, unsigned int length> class Queue; // declare Queue for ostream to use it 

template<typename T, unsigned int length>
std::ostream& operator<<(std::ostream& stream, const Queue<T, length>& queue); // declare operator<< for Queue to befriend it 

template<typename T, unsigned int length> //define a datatype T for elements in the queue 
class Queue {
protected:
	T elements[length]; //[] = pointer + sizeof()
	unsigned int count;
	friend std::ostream& operator<< <T, length>(std::ostream& stream, const Queue<T, length>& queue);
	template<typename, unsigned int> friend class Queue;

public:
	~Queue() {}
	Queue() :count(0) {} //constructor must have the same name as the class
	
	template<typename dstT>
	operator Queue<dstT, length>() {
		Queue<dstT, length> result;
		result.count = count;
		for(unsigned int i = 0; i < count; ++i)
			result.elements[i] = static_cast<dstT>(elements[i]);
		return result;
	}

	void enqueue(T element) {
		if(count == length)
			throw std::overflow_error("too many elements");
		elements[count++] = element; // insert an element at index count; post increment count by one  
	}

	T dequeue() {
		if(count == 0)
			throw std::underflow_error("no elements left");
		T element = elements[0];
		for(unsigned int i = 1; i < count; ++i) // if i == 0, underflow_error
			elements[i-1] = elements[i];
		--count; // pre decrement
		return element;
	}

	bool exists(T element) {
		for(unsigned int i = 0; i < count; ++i)
			if(elements[i] == element)
				return true;
		return false;
	}
};

template<typename T, unsigned int length>
std::ostream& operator<<(std::ostream& stream, const Queue<T, length>& queue) {
	for(unsigned int i = 0; i < queue.count; ++i) {
		if(i > 0)
			stream << ' '; // insert space between elements
		stream << queue.elements[i];
	}
	return stream;
}