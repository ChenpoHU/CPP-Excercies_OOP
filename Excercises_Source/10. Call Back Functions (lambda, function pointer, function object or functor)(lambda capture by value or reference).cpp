#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

//&less will make less the function pointer
bool less(int a, int b) { return a < b; };

//operator
struct IntComparator {
	bool operator()/*can become a functor, an instance, which is used as a function*/(int a, int b) { return a < b; }
};

int main() {
	std::vector<int> a = { 15,1,9,43,1,43,19,84,73 };
	IntComparator c; /*constructor for initialization: or IntComparator c();*/
	std::sort(a.begin(), a.end(), c);//functor c is called here 
	//line 15 and 16 can be replaced here: 
	std::sort(a.begin(), a.end(), IntComparator()); //IntComparator() in sort is a functor; use () to initialize IntComparator. Without () is IntComparator just a type.
	//IntComparator()() first () will be initialization, second () will be a call/invocation. But it´s not intented to be used here. 
	std::sort(a.begin(), a.end(), &less); //here is not an invocation (function call/run), it is a function pointer instead with &.

	std::sort(a.begin(), a.end(), [](auto a, auto b) {return a < b; });	//lambda = function pointer using the captured variable/local variable
																		//lambda provides a cleaner, lightweight interface to pass functions inline.
	for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	int int_var = 42;
	auto lambda_func = [&]() { //Shortcut [&] to capture all variables in scope by reference or [&int_var] here
		std::cout << "This lambda has a copy of int_var:" << int_var << std::endl; 
	};
	//a function pointer is hided here in the [](){}(). 
	//[](){}: is the construtor and initialization, can only be auto 
	//The last () is the invocation, which can be seen in for loop lambda_func()
	for (int i = 1; i <= 3; ++i) {
		++int_var;
		lambda_func();//Invocation of a lambda function
	}
}

/*
Capture by values with line 23 as [int_var] or [=]: Shortcut [=] to captures all local variables in current scope
Capture can be viewed as local scoping, but uses a constant copy of variable.
 1 1 9 15 19 43 43 73 84
This lambda has a copy of int_var:42
This lambda has a copy of int_var:42
This lambda has a copy of int_var:42
*/


/*
Capture by references with line 23 as [&int_var] or [&]:Shortcut [&] to capture all local variables by reference
 1 1 9 15 19 43 43 73 84
This lambda has a copy of int_var:43
This lambda has a copy of int_var:44
This lambda has a copy of int_var:45
*/