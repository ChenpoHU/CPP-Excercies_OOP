#include <iostream>     // std::cout
#include <algorithm>
#include <vector>       // std::vector

// function to sum. In fact, the details depend on the passed function 
// f. It would be e.g. possible to calculate the product of all elements instead of the sum. 
template <class Container, typename T, typename Function>
T result(Container& cont, T initvalue, Function f) {
	T result = initvalue;
	for (auto value : cont) {
		result = f(result, value);
	}  
	return result;
}

int main() {
	std::vector<double> v{ 3.1, 0.2, 22.0, 3.5, 8.99 };
	auto sum = result(v, 0.0, [](auto sum, auto w) { return sum + w; });

	// Initialize the mean with sum / v.size () in the lambda function  
	auto variance = result(v, 0.0, [mean = sum / v.size()](auto sum, auto w) {auto diff = w - mean;
	return sum + diff * diff; }) / v.size();
	//[CAPTURES](PARAMETER){}()
	//[CAPTURES: passed in initialisation/construction]: Construction is the initialisation of a class
	//(PARAMETER: passed in invocation/call)
	std::cout << "\nStandard Deviation = " << std::sqrt(variance) << '\n'; //Output: Standard Deviation = 7.7602

	// Variation with nested Lambda-Function for computing mean  
	auto variance2 = result(v, 0.0, [mean = result(v, 0.0, [](auto sum, auto w) { return sum + w; }) / v.size()](auto sum, auto w) {auto diff = w - mean; return sum + diff * diff; })
		/ v.size();
	std::cout << "\nStandard Deviation = " << std::sqrt(variance2) << '\n';
}