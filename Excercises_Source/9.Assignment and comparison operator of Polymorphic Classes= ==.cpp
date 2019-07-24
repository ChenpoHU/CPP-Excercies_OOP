#include <algorithm> //swap()
#include <iostream>
#include <cassert>
#include <typeinfo>

class A {
public:
	A(int a_) : a{ a_ } {}
	virtual ~A() = default;

	virtual A& assign(const A& rhs) {
		std::cout << "virtual A& A::assign(const A&)\n";
		if (typeid(*this) != typeid(rhs)) {     // siehe Text unten      
			throw std::bad_typeid();
		}
		A temp(rhs);
		swap(temp);
		return *this;
	}

	A& operator=(const A& rhs) {
		std::cout << "A& operator=(const A& rhs)\n";
		return assign(rhs);
	}

	virtual void ausgabe() const { //const method. read only access to member variables; the a can not be changed, but other global variables and parameters can be changed.
		// not constexpr, constexpr means that the expressions is realy dependent to the compiler time, not to the execution time. 
		std::cout << "A.a = " << a << ' ';
	}

	void swap(A& rhs) {
		std::swap(a, rhs.a);
	}

	virtual bool operator==(const A& arg) const {
		return typeid(*this) == typeid(arg)     // siehe Text unten           
			&& a == arg.a;
	}


private:
	int a;
};

class B : public A {
public:
	B(int a_, int b_) : A(a_), b{ b_ } {}
	virtual B& assign(const A& rhs) {
		std::cout << "virtual B& B::assign=(const A&)\n";
		if (typeid(*this) != typeid(rhs)) {
			throw std::bad_typeid();
		}
		B temp(static_cast<const B&>(rhs));
		swap(temp);
		return *this;
	}

	B& operator=(const B& rhs) {
		std::cout << "B& operator=(const B& rhs) \n";
		return assign(rhs);
	}
	void swap(B& rhs) {
		A::swap(rhs);
		std::swap(b, rhs.b);
	}

	virtual void ausgabe() const {//const method. read only access to member variables; the a and b can not be changed, but other global variables and parameters can be changed.
		A::ausgabe();
		std::cout << "B.b = " << b << ' ';
	}

	bool operator==(const A& arg) const {
		return A::operator==(arg) && b == static_cast<const B&>(arg).b;
	}
private: int b;
};

class C : public B {
public:
	C(int a_, int b_, int c_)
		: B(a_, b_), // Oberklassenkonstruktor 
		c{ c_ } { // lokale Daten 
	}
	virtual C& assign(const A& rhs) {
		std::cout << "virtual C& C::assign=(const A&)\n";
		if (typeid(*this) != typeid(rhs)) {
			throw std::bad_typeid();
		}
		C temp(static_cast<const C&>(rhs));
		swap(temp);
		return *this;
	}
	C& operator=(const C& rhs) { // rhs is read only ; this is not const reference or const pointer: (C* const rhs) means that the * address cannot be changed.
		std::cout << "C& operator=(const C& rhs)\n";
		return assign(rhs);
	}
	virtual void ausgabe() const {//const method. read only access to member variables; the a, b and c can not be changed, but other global variables and parameters can be changed.
		B::ausgabe();
		std::cout << "C.c = " << c << ' ';
	}
	void swap(C& rhs) {
		B::swap(rhs); // Oberklassendaten 
		std::swap(c, rhs.c); // lokale Daten 
	}

	bool operator==(const A& arg) const {
		return B::operator==(arg) && c == static_cast<const C&>(arg).c;
	}
private:
	int c;
};

using namespace std;
int main() {
	cout << "\nTest 1\n";
	// Klasse A 
	A a1(1);
	A a2(2); 
	a1.ausgabe();
	cout << '\n';
	a1 = a2; 
	cout << "a1 nach Zuweisung a1=a2:\n";
	a1.ausgabe(); 
	cout << '\n';
	assert(a1 == a2);

	cout << "\nTest 2\n";
	// Klasse B 
	B b1(1, 2);
	B b2(3, 4);
	b1.ausgabe();
	cout << '\n';
	b1 = b2; 
	cout << "b1 nach Zuweisung b1=b2:\n";
	b1.ausgabe();
	cout << '\n';
	assert(b1 == b2);

	cout << "\nTest 3 polymorphe Zuweisung\n";
	B b3(5, 6);
	A& ar = b1; // Oberklassenreferenz   //ar is the name of the address of b1
	ar = b3; //assign- operator called, b3 is assigned to ar or b1 //content of b3 is copied to ar.

	//pointer version: b1 ist von b3 überschreiben. 
	//A* ar = &b1;
	//*ar = b3;
	//same as b1 = b3;

	cout << "ar nach Zuweisung ar=b3:\n";
	ar.ausgabe();
	cout << '\n';
	assert(ar == b3);

	cout << "\nTest 4\n"; // Klasse C 
	C c1(1, 2, 3);
	C c2(4, 5, 6);
	c1.ausgabe();
	cout << '\n';
	c1 = c2;
	cout << "c1 nach Zuweisung c1=c2:\n";
	c1.ausgabe();
	cout << '\n';
	assert(c1 == c2);

	cout << "\nTest 5 : polymorphe Zuweisung A& = C\n";
	C c3(7, 8, 9);
	A & arc = c2; // Oberklassenreferenz 
	arc = c3;
	cout << "arc nach Zuweisung arc=c3:\n";
	arc.ausgabe();
	cout << '\n';
	assert(arc == c3);

	cout << "\nTest 6 : polymorphe Zuweisung B& = C\n";
	B & brc(c2); // Oberklassenreferenz 
	brc = c3;
	cout << "brc nach Zuweisung brc=c3:\n";
	brc.ausgabe();
	cout << '\n';
	assert(brc == c3);

	cout << "\nTest 7 : falscher Typ: b1 = c3\n"; // Typfehler 
	try {
		b1 = c3;
	}
	catch (const bad_typeid & e) {
		cerr << "Falscher Typ! Exception: " << e.what() << '\n';
	}

	cout << "\nTest 8 : falscher Typ: a1 = c3\n";
	try {
		a1 = c3;
	}
	catch (const bad_typeid & e) {
		cerr << "Falscher Typ! Exception: " << e.what() << '\n';
	}
	cout << "Test-Ende\n";
}