#include <iostream>
#include <algorithm>

/*
1 Numbered Objects
Find a implementation for Numbered Objects.Numbered Objects assigns a unique number to each created object.Read the implementation in ﬁle numberedObj.tarand implement the following.
1.1. Constructor, which assigns a unique number to numbered object
*/

class NumberedObj {
public:
	//1.1.Constructor, which assigns a unique number to numbered object
	NumberedObj() :serialNr(nextSerialNr++) {
		++instanceCount;
	}

	//1.2. Explicit Copy Constructor
	NumberedObj(const NumberedObj& other) :NumberedObj() {}

	//1.3. Overload the = operator
	NumberedObj& operator=(NumberedObj& other) {  // Zuweisungsoperator
		return *this;
	}

	//1.4. Destructor
	~NumberedObj() {
		--instanceCount;
	}

	unsigned long serialNumber() const { return serialNr; }
	static int num() { return instanceCount; }
private:
	static int instanceCount; // delarition 
	static unsigned long nextSerialNr;
	const unsigned long serialNr;
};

int NumberedObj::instanceCount = 0; //reserve memory and initialisation
unsigned long NumberedObj::nextSerialNr = 0;

using namespace std;

int main() {

	NumberedObj numberedObj;
	NumberedObj numberedObj1;
	std::cout << numberedObj.serialNumber() << std::endl;
	std::cout << numberedObj1.serialNumber() << std::endl;

}
