/*
1 Theory
1.1. Check the documentation of std::unique_ptr.Is it similar to something discussed in class ? If yes, then what it is.

	std::shared_ptr (m pointer - 1 object). 
	unique_ptr (1 pointer - 1 object) and shared_ptr both belong the smart pointer. 

	std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
	The object is disposed of using the associated deleter when either of the following happens:
	- the managing unique_ptr object is destroyed
	- the managing unique_ptr object is assigned another pointer via operator= or reset().

	std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. Several shared_ptr pointers/objects may own the same object. 
	The object is destroyed and its memory deallocated when either of the following happens:
	- the last remaining shared_ptr owning the object is destroyed;
	- the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().

1.2. Why are widow objects dangerous ?
	Memory leakage and widow objects occurs in C++ when programmers allocates memory by using new keyword and forgets (or not able to because of exception) to deallocate the memory by 
	using delete() function or delete[] operator.

	If a program has memory leaks, then its memory usage is satirically increasing since all systems have limited amount of memory and memory is costly. 

1.3. Why are smart pointers preferred over new initialization ?

	Using smart pointers, we can make pointers to work in way that we don’t need to explicitly call delete to manage the memory manually. 
	Smart pointer is a wrapper class over a pointer with destructor and overloaded operator like * and -> overloaded. 
	The objects of smart pointer class look like pointer, but can do many things that a normal pointer can’t like automatic destruction (yes, we don’t have to explicitly use delete), reference counting and more.

1.4. What are the diﬀerent ways of using callback functions in C++ that you have studied ? Which one would you prefer ? Support your argument with valid reasoning.
	– Function Object (Functor) 
	– Function Pointer 
	- Lambda Expression

	I prefer lambda expression, since Constructs a closure: an unnamed function object capable of capturing variables in scope. 

	Why callback: 
	Most of the time we are creating programs and applications that operate in a synchronous manner. 
	In other words, some of our operations are started only after the preceding ones have completed. Often when we request data from other sources, such as an external API, 
	we don’t always know when our data will be served back. In these instances we want to wait for the response, but we don’t always want our entire application grinding to 
	a halt while our data is being fetched. These situations are where callback functions come in handy.

*/

//1.2
void myfunc()
{
	Photo a(1, 2);
	Photo* pt = new Photo(2, 3);
	throw runtime_error("to test the exception"); //exception 
	delete pt;
}
//compileand run under valgrind.you will get a leak - delete pt; is never reached.

//1.3
#include<iostream> 
using namespace std;

// A generic smart pointer class 
template <class T>
class SmartPtr
{
	T* ptr;  // Actual pointer 
public:
	// Constructor 
	explicit SmartPtr(T* p = NULL) { ptr = p; }

	// Destructor 
	virtual ~SmartPtr() { delete(ptr); }

	// Overloading dereferncing operator 
	T& operator * () { return *ptr; }

	// Overloding arrow operator so that members of T can be accessed 
	// like a pointer (useful if T represents a class or struct or  
	// union type) 
	T* operator -> () { return ptr; }
};

int main()
{
	SmartPtr<int> ptr(new int());
	*ptr = 20;
	cout << *ptr;
	// We don't need to call delete ptr: when the object  
	// ptr goes out of scope, destructor for it is automatically 
	// called and destructor does delete ptr. 
	return 0;
}