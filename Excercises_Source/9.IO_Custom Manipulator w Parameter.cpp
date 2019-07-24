//prints 25 newlines and then End

#include <iostream>

class Leerzeilen {
public:
	Leerzeilen(int i = 1) : anzahl{ i } { // Constructor: Create one empty new line 
	}

	std::ostream& operator()(std::ostream& os) const {
		for (int i = 0; i < anzahl; ++i) {
			os << '\n'; //create i new line
			//os << i; // add by myself 
		}
		os.flush();
		return os;
	}
private:
	int anzahl;
};

inline std::ostream& operator<<(std::ostream& os, const Leerzeilen& leerz) {
	return leerz(os); //functor call: leerz is an instanz, the () is the () operator. Functor: object that can act as a function
}

int main() {
	std::cout << // here calls the << operator. Only int, double, float has the << operator. To print the other type out, we have to write the << operator for them or cast the data types 
		Leerzeilen(25) /*constructor call! */ << "end\n";
}