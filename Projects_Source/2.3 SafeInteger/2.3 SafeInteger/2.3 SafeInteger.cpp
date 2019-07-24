// 2.3 SafeInteger.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include "SafeInt.hpp"
#include <iostream>

int main()
{
	SafeInt<unsigned char> i(4);
	SafeInt<unsigned char> j(2);

    std::cout << "i: " << i << std::endl;
	std::cout << "--i: " << i << std::endl;
	std::cout << "i + j: " << i + j<< std::endl;
	std::cout << "i - j: " << i - j << std::endl;
	std::cout << "++i: " << i << std::endl;
	std::cout << "i * j: " << i*j << std::endl;
	std::cout << "i / j: " << i/j << std::endl;
	std::cout << "(i == j):" << (i == j) << std::endl;
	std::cout << "(i != j): " << (i != j) << std::endl;
	std::cout << "(i > j): " << (i > j) << std::endl;
	std::cout << "(i < j): " << (i < j) << std::endl;
	std::cout << "(i >= j): " << (i >= j) << std::endl;
	std::cout << "(i <= j): " << (i <= j) << std::endl;
	std::cout << "sizeof(): " << sizeof(i) << std::endl;
}


