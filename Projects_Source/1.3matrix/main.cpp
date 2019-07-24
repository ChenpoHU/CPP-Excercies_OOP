//Your code goes here
#include "matrix.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	Matrix m(2, 2);
	m.values[0] = 1;
	m.values[1] = 2;
	m.values[2] = 3;
	m.values[3] = 4;
	cout << "A" << endl;
	m.debugPrint();
	cout << "B" << endl;
	return 0;
}
