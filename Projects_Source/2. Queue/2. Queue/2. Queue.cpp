// 2. Queue.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "CircularBuffer.hpp"

int main()
{
	CircularBuffer<char, 5> queue;
	queue.enqueue('A');
	queue.enqueue('B');
	queue.enqueue('C');
	std::cout << queue << std::endl;
	std::cout << queue.exists('A') << std::endl;
	std::cout << queue.dequeue() << std::endl;
	std::cout << queue.exists('A') << std::endl;
	std::cout << queue << std::endl;

	// auto other = reinterpret_cast<Queue<int, 5>&>(queue);
	auto other = static_cast<CircularBuffer<int, 5>>(queue);
	std::cout << other << std::endl;
	// auto other = dynamic_cast<Queue<int, 5>*>(&queue);

}
