#include <cstddef> 
#include <iostream> 
#include <limits> //Has limits information 
using namespace std;
int main() {
	cout << "Limits for Integer Types : " << '\n'; // = Newline, alternate use std::endl  
	cout << "int Minimum = " << numeric_limits<int>::min() << '\n';
	cout << "int Maximum = " << numeric_limits<int>::max() << '\n';
	cout << "long Minimum = " << numeric_limits<long>::min() << '\n';
	cout << "long Maximum = " << numeric_limits<long>::max() << '\n';
	cout << "long long Minimum = " << numeric_limits<long long>::min() << '\n';
	cout << "long long Maximum = " << numeric_limits<long long>::max() << '\n';
	cout << "unsigned - Maxima(Minimum is 0) : \n"; //new line  
	cout << "unsigned int = " << numeric_limits<unsigned int>::max() << '\n';
	cout << "unsigned long = " << numeric_limits<unsigned long>::max() << '\n';
	cout << "unsigned long long = " << numeric_limits<unsigned long long>::max() << '\n';
	cout << "# Bytes:\n";  
	cout << "int       " << sizeof(int) << '\n';  
	cout << "long      "<< sizeof(long) << '\n';  
	cout << "long long " << sizeof(long long) << '\n';
	cout << "size_t    " << sizeof(size_t) << '\n';
}
/*Limits for Integer Types :
int Minimum = -2147483648
int Maximum = 2147483647
long Minimum = -2147483648
long Maximum = 2147483647
long long Minimum = -9223372036854775808
long long Maximum = 9223372036854775807
unsigned - Maxima(Minimum is 0) :
	unsigned int = 4294967295
	unsigned long = 4294967295
	unsigned long long = 18446744073709551615
	# Bytes :
	int       4
	long      4
	long long 8
	size_t    4*/