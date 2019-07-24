/*
1.1. Explain the diﬀerence between static binding and dynamic binding ?

Binding generally refers to a mapping of one thing to another. 
In the context of compiled languages, binding is the link between a function call and the function definition. 
When a function is called in C++, the program control binds to the memory address where that function is defined.
- There are two types of binding in C++: static (or early) binding and dynamic (or late) binding. This post provides an overview of the differences between the between static and dynamic binding in C++.
- The static binding happens at the compile-time and dynamic binding happens at the runtime. Hence, they are also called early and late binding respectively.
- In static binding, the function defination and the function call are linked during the compile-time whereas in dynamic binding the function calls are not resolved until runtime. So they are not bound until runtime.
- Static binding happens when all information needed to call a function is available at the compile-time. Dynamic binding happens when all information needed for a function call cannot be determined at compile-time.
- Static binding can be achieved using the normal function calls, function overloading and operator overloading;
  while dynamic binding can be achieved using the virtual functions.
- Since all information needed to call a function is available before runtime, static binding results in faster execution of a program. Unlike static binding, a function call is not resolved until runtime for later binding and this results in somewhat slower execution of code.
- The major advantage of dynamic binding is that it is flexible since a single function can handle different type of objects at runtime. This significantly reduces the size of the codebase and also makes the source code more readable.

1.2. Recall the four Principles of OOP from Lecture 2. Which of the property / properties are satisﬁed by Inheritance ?

both by OOP and inheritance:
–	Abstraction 
–	Encapsulation: In OOP, Encapsulation is defined as binding together the data and the functions that manipulates them.
–	Hierarchy 
–	Modularity

1.3. Consider a class Ellipse which models a ellipseand a class Circle which models a circle. Is is a good idea to make Circle a subclass of Ellipse ? Why.

	Yes, because circle is a special case of ellipse, which has one more restriction comparing to the ellipse class. 

1.4. What is an abstract class? Mention its uses.

- base class 
- at least one pure virtual function 

	Some concepts are abstract, like vehicles, which can be can base class in a programm. Only its sub-class can be concrete, like car. 

	An abstract class is a class that is designed to be specifically used as a base class, an abstract type which cannot be instantiated
	An abstract class contains at least one pure virtual function. 
	You declare a pure virtual function by using a pure specifier (= 0) in the declaration of a virtual member function in the class declaration.

1.5. What is a virtual method table ? Mention its uses.

	The virtual table is a lookup table of functions used to resolve function calls in a dynamic/late binding manner. 

1.6. Explain the execution of a function pointer ?

	When a function is called (via the () operator), execution jumps to the address of the function being called.Unlike normal pointers, a function pointer points to code, not data. Typically a function pointer stores the start of executable code.
	As opposed to referencing a data value, a function pointer points to executable code within memory. Dereferencing the function pointer yields the referenced function, which can be invoked and passed arguments just as in a normal function call. Such an invocation is also known as an "indirect" call, because the function is being invoked indirectly through a variable instead of directly through a fixed identifier or address.

	1.7. Why would you use a virtual destructor ?

- A virtual destructor is one that is declared as virtual in the base class and is used to ensure that destructors are called in the proper order. 
  It is to be remembered that destructors are called in the reverse order of inheritance. 
  If a base class pointer points to a derived class object and we some time later use the delete operator to delete the object, then the derived class destructor is not called.
  If the pointer is of type base, the base class destructor would be called but the derived class destructor would not be called at all. The result is memory leak. 
  In order to avoid this, we have to make the destructor virtual in the base class.

- A virtual function is a member function of a class, whose functionality can be over-ridden in its derived classes.

2 Virtual Function
Consider the program given in Listing ? ? and answer the following questions
2.1. What is output at line marked L1 ? Give an appropriate reason.

2.2. Draw the virtual method table for the program.
*/
#include <iostream> 
using namespace std;
class Base {
protected:
	int d;
	int x;
public:
	Base() = default;
	int value() const { return 10; }
	~Base() { cout << "Base deleted "; }
};
class Derived1 : public Base {
protected:
	int y;
public: Derived1() = default;
		int value() const { return 15; }
		~Derived1() { cout << "Derived1 deleted "; }
		int gety() const { return y; }
};

class Derived2 : public Base {

public: Derived2() = default;
		int value() const { return 17; }
		~Derived2() { cout << "Derived2 deleted "; }
};
int main() {
	Base* p = new Base();
	Base* p1 = new Derived1();
	Derived1* p2 = (Derived1*) new Base();
	cout << p2->gety() << endl;//-33686019
	Base* p3 = new Derived2();
	cout << p->value() << endl;  //10 reads the first value from the base perspective.
	cout << p1->value() << endl; //10 reads the first value from the base perspective.
	cout << p2->value() << endl; //L1 15 reads the first value from the Derived1 perspective.
	cout << p3->value() << endl; //10 reads the first value from the base perspective.
	delete p;
	delete p1;
	delete p2;
	delete p3;
}

//1.4.What is an abstract class ? Mention its uses.
// base class 
struct Abstract {
	virtual void f() = 0; // pure virtual
}; 

struct Concrete : Abstract {
	void f() override {} // non-pure virtual
	virtual void g();     // non-pure virtual
}; // "Concrete" is non-abstract

struct Abstract2 : Concrete {
	void g() override = 0; // pure virtual overrider
}; 

int main()
{
	// Abstract a; // Error: abstract class
	Concrete b; // OK
	Abstract& a = b; // OK to reference abstract base
	a.f(); // virtual dispatch to Concrete::f()
	// Abstract2 a2; // Error: abstract class (final overrider of g() is pure)
}


#include <iostream.h>
class base
{
public:
	virtual ~base() // !!
	{

	}
};

class derived : public base
{
public:
	~derived()
	{

	}

};

void main()
{

	base* ptr = new derived(); // if not virtual desctructor, the derived class destructor would not be called at all. The result is memory leak.
	// some code
	delete ptr;
}