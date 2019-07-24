#include <iostream>
#include <string>

//Funktionsprototype, 2nd parameter with default 
void displayPrice(const double price, const std::string& currency = "EURO");//const reference of std::string 

int main() {
	displayPrice(12.35); // call with default parameter used 
	displayPrice(99.99, "US-Dollar");
}

void displayPrice(const double price, const std::string& currency) {
	std::cout << price << ' ' << currency << '\n' << std::endl;
}
