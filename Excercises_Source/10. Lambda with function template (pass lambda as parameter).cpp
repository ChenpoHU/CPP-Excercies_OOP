#include <iostream>     // std::cout
#include <vector>       // std::vector

template <typename T, typename Funktor>
void vectorProcess(const std::vector<T>& v, const Funktor& funktor) {
	for (const auto& el : v) {
		funktor(el);
	}
}

int main() {

	std::vector<double> v{ -11.0, 3.2, 4.1, -7.0, 8.0, 1.5, 2.7, -4.4 };

	double sum = 0.0;
	vectorProcess(v, [&sum](auto el) { sum += el; }); //a vector process object with a vector and a sum functor/lambda
	std::cout << "Sum = " << sum << '\n'; //Ouput: Sum = -2.9

	sum = 0.0;
	double threshold = -1.2;
	vectorProcess(v, [=, &sum](auto el) { if (el > threshold) { sum += el; }}); //capture el and threshold by value, capture sum by reference
	std::cout << "Sum of all values > " << threshold << " = " << sum << '\n'; //Output:Sum of all values > -1.2 = 19.5
}