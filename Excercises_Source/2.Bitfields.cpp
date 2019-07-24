#include <iostream>
struct BitFieldStruct {
	unsigned int a : 4;
	unsigned int b : 3;
};

int main() {
	BitFieldStruct x;
	x.a = 06;
	x.b = x.a | 3; // | bitwise OR, || logical OR ; & bitwise AND, && logicalwise AND
	std::cout << x.a << '\n' << std::endl;// converted to unsigned and then displayed	
	std::cout << x.b << '\n' << std::endl;// converted to unsigned and then displayed
}

//  0 1 1   is 3 
//  1 1 0   is 6     bitwise OR of 3 and 6 is:
//  1 1 1   is 7

//may save space but cost time in comparison to byte alignment 

//      bitwise    logical
// OR      |          ||
//AND      &          &&
//XOR      ^          !=
//NEG      ~           !          
