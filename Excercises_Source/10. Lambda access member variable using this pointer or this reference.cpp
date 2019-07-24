#include <iostream>     // std::cout
#include <vector>       // std::vector

// [&result, *this] works 
// [&]              works 
// [&, *this]       works
// [&result, this]  works

//Initializer list: This type is used to access the values in a C++ initialization list, which is a list of elements of type const T.
// like begin, end 
//auto il = { 10, 20, 30 }; 

//std::list is a container that supports constant time insertionand removal of elements from anywhere in the container. 
//like push_back, push_front, pop_from, swap, clear, insert
//Initialisierung:     std::list<int> l = { 7, 5, 16, 8 };


class LambdaTest {
public:
	LambdaTest(std::initializer_list<int> il) : v(il) {} // v is a vector; il is an initializer list

	int sum(int result) {
		auto func = [&result, *this]() {        // Definition of Lambda Function      
			for (auto el : v/*   this->v; (*this).v    */) {                 // using attribute v        
				result += el; //must use &result, otherwise it gives "Der Ausdruck muss ein änderbarer lvalue sein".
			}
			return result;
		};
		return func();  // Aufruf  
	}
private:
	std::vector<int> v;
};

int main() {
	LambdaTest test{ -1, 0, 1, 2, 3, 4 };
	std::cout << test.sum(10) << '\n';      // Offset 10 
}

//Output 19