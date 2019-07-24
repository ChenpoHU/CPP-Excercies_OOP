#include <iostream>
#include <algorithm> 
#include <cassert>

using std::cout;
using std::endl;

void rotate(int& a, int& b, int& c) {//delarition; parameter
	/*int d = a;
	a = b;
	b = c;
	c = d;*/

	std::swap(b, c);
	std::swap(c, a);

	/*int* ptr[] = {&a, &b, &c};
	std::swap(*ptr[1], *ptr[2]);
	std::swap(*ptr[2], *ptr[0]);*/

	/*int* ptr[] = { &a, &b, &c };
	for(int i = 0; i < 2; ++i)
		std::swap(*ptr[i+1], *ptr[(i+2)%3]);*/
}

//Do NOT modify the main function
int main() {
	int a = 6, b = 7, c = 9;
	cout << "Before rotate: a=" << a << " b=" << b << " c=" << c << endl;
	rotate(a, b, c);
	cout << "After  rotate: a=" << a << " b=" << b << " c=" << c << endl;
	assert((a == 7 && b == 9 && c == 6) || (a == 9 && b == 6 && c == 7));
	cout << "successfully passed the test case" << endl;
}