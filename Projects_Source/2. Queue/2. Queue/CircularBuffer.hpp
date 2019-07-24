#pragma once
#include "queue.hpp"

template<typename T, unsigned int length> class CircularBuffer; // declare CircularBuffer for ostream to use it 

template<typename T, unsigned int length>
std::ostream& operator<<(std::ostream& stream, const CircularBuffer<T, length>& queue); // declare operator<< for CircularBuffer to befriend it 

template<typename T, unsigned int length> //define a datatype T for elements in the queue 
class CircularBuffer : public Queue<T, length> {
	unsigned int begin; // new instance variable 

	friend std::ostream& operator<< <T, length>(std::ostream& stream, const CircularBuffer<T, length>& queue);
	template<typename, unsigned int> friend class CircularBuffer;
	typedef Queue<T, length> Super;

public:
	~CircularBuffer() {}
	CircularBuffer() :Super(), begin(0) {} //constructor must have the same name as the class

	template<typename dstT>
	operator CircularBuffer<dstT, length>() {
		CircularBuffer<dstT, length> result;
		result.count = Super::count;
		for(unsigned int i = 0; i < Super::count; ++i)
			result.elements[i] = static_cast<dstT>(Super::elements[i]);
		return result;
	}

	void enqueue(T element) {
		if(Super::count == length)
			throw std::overflow_error("too many elements");
		Super::elements[(begin + Super::count++) % length] = element;
		/*if(begin + Super::count >= length)
			elements[begin + Super::count++ - length] = element;
		else
			elements[begin + Super::count++] = element;*/
	}

	T dequeue() {
		if(Super::count == 0)
			throw std::underflow_error("no elements left");
		T element = Super::elements[begin++];
		begin %= length;
		--Super::count;
		return element;
	}

	bool exists(T element) {
		for(unsigned int i = begin; i < begin + Super::count; ++i)
			if(Super::elements[i % length] == element)
				return true;
		return false;
	}
};

template<typename T, unsigned int length>
std::ostream& operator<<(std::ostream & stream, const CircularBuffer<T, length> & circularBuffer) {
	for(unsigned int i = circularBuffer.begin; i < circularBuffer.begin + circularBuffer.count; ++i) {
		if(i > circularBuffer.begin)
			stream << ' '; // insert space between elements
		stream << circularBuffer.elements[i % length];
	}
	return stream;
}