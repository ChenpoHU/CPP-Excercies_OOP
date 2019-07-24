#include <iostream>

//void add_7(int& y); //reference of int
void add_7(int& x) {
	x += 7;//Modified the original actual parameter
}
int main() {
	int i{ 0 };
	std::cout << i << " = old value of i\n" << std::endl;
	add_7(i);//syntax same as call by value
	std::cout << i << " = new value of i after add_7\n" << std::endl;
}