/*1. Explain the diﬀerence between call - by - value and call - by - reference, citing an example.

	Call by value	                                                         | Call by reference
	A copy of value is passed to the function	                             | An address of value is passed to the function
	Changes made inside the function is not reflected on other functions     | Changes made inside the function is reflected outside the function also
	Actual and formal arguments will be created in different memory location | Actual and formal arguments will be created in same memory location
*/

//call by reference
#include <iostream>

template<typename T>
void swap(T& a, T& b) {
	const T temp = a; // * is added before a and b from line 14 - 16 automatically
	a = b;
	b = temp;
}

template<typename T>
void swap(T* x, T* y)
{
	const T temp = *x;
	*x = *y;
	*y = temp;
}
int main()
{
	int x = 500, y = 100;
	swap(x, y);   // passing value to function swap(T& a, T& b), & is added before a and b when calling the swap (T& a, T& b)
	std::cout << "Value of x is: " << x << std::endl;
	swap(&x, &y); // swap(T* x, T* y)
	std::cout << "Value of y is: " << y << std::endl;
	return 0;
}
//call by value
#include <iostream>  
using namespace std;
void change(int data) //can be fixed by add & here. with it, 5, whitout it, 3
{
	data = 5;
}
int main()
{
	int data = 3;
	change(data);
	cout << "Value of the data is: " << data << endl;
	return 0;
}

/*
2. What is a heap memory ? Why it is used ?
	
	stack overflow: Stack overflow happens when all the memory in the stack has been allocated -- in that case, further allocations begin overflowing into other sections of memory.

	Heap: The heap segment (also known as the “free store”) keeps track of memory used for dynamic memory allocation with new and delete.

	widowed objects or:
	memory leak: 
	The delete operator does not actually delete anything. It simply returns the memory being pointed to back to the operating system.
	The operating system is then free to reassign that memory to another application (or to this application again later).

	dangling pointers: double delete will lead to undefined behavior. 

	The memory that a program uses is typically divided into a few different areas, called segments:
	The code segment (also called a text segment), where the compiled program sits in memory. The code segment is typically read-only.
	The bss segment (also called the uninitialized data segment), where zero-initialized global and static variables are stored.
	The data segment (also called the initialized data segment), where initialized global and static variables are stored.
	The heap, where dynamically allocated variables are allocated from.
	The call stack, where function parameters, local variables, and other function-related information are stored.
	
	*/
#include <iostream>

int main()
{
	int *ptr = new int; // dynamically allocate an integer
	*ptr = 7; // put a value in that memory location

	delete ptr; // return the memory to the operating system.  ptr is now a dangling pointer.

	std::cout << *ptr; // Dereferencing a dangling pointer will cause undefined behavior
	delete ptr; // trying to deallocate the memory again will also lead to undefined behavior.

	return 0;
}

/*
3. How are pointers diﬀerent from reference ?

	Pointers: A pointer is a variable that holds memory address of another variable. A pointer needs to be dereferenced with * operator to access the memory location it points to.
	References : A reference variable is an alias, that is, another name for an already existing variable. A reference, like a pointer is also implemented by storing the address of an object.
	
(1).Initalisation: A pointer can be initalised in this way:*/
	int a = 10;
	int *p = &a; 
	//or
	int* p;
	p = &a;
	//we can declareand initalise pointer at same step or in multiple line.
	//reference:
	int a=10;
	int &p=a;  
	//but 
	int& p;
	p = a;  /*incorrect
(2)Reassignment: A pointer can be re - assigned, a reference not.*/
	int a = 5;
	int b = 6;
	int* p;
	p = &a;
	p = &b;/*
(3)Memory Address : A pointer has its own memory addressand size on the stack whereas a reference shares the same memory address(with the original variable) but also takes up some space on the stack.

(4)NULL value: Pointer can be assigned NULL directly, whereas reference cannot. The constraints associated with references (no NULL, no reassignment) ensure that the underlying operations do not run into exception situation.

(5)Indirection: You can have pointers to pointers offering extra levels of indirection. Whereas references only offer one level of indirection.I.e,
	In Pointers,*/
	int a = 10;
	int *p;
	int **q;  //it is valid.
	p = &a;
	q = &p;

	//Whereas in refrences,

	int &p = a;
	int &&q = p; /*it is reference to reference, so it is an error.

(6)Arithmetic operations: Various arithmetic operations can be performed on pointers whereas there is no such thing called Reference Arithmetic.

*/


/*
4. Consider the program given below.What would be the expected value of* p ?
	When there were no type converting error, it should give 127 out, but there is a c style converting from int (4 byte) to char* (1 byte). First byte of x(endian specific) is interpreted as character. 
*/
#include <iostream>
int main() {
	int x = 127;
	char* p = (char*)& x; //only the first character of a int 127 will be available, but 127 has no ascii value. char* means p is char*, x is a type char. 
	std::cout << *p << std::endl;       // *p: First byte of x (endian specific) interpreted as character. p is a pointer (has a value of an address, the aadress point to the value of x), *p is the dereference of p pointer, which should give 127 out, when all is correct. 
	std::cout << (void*)p << std::endl; // 009BFB6C p is interpreted as pointer not as string (void pointer casting) 
	printf("%p\n", p);                  // 009BFB6C p is interpreted as pointe (format)
	std::cout << p << std::endl;        // p: interpreted as string (const char*) by cout
	printf("%s\n", p);                  // p interpreted as string (format)
}

/*
5 Why public interfaces of a class should be as small as possible ? Explain.
	
	It´s relevant to the encapsulation. The bigger the public interfaces, the more potential bugs can be produced when using these public interfaces. 

6. Is C++ a typesafe language ? Explain.

Type safety means that the compiler can check whether you're using the right types. C++ has a static and strict type system. 
“Static” means that types are already known at compile time. 
Of course, C++ also offers techniques for late bindings during runtime. But these programming techniques will only extend the static type system by additional dynamic features. 
“Strict” on the other hand means, to check the type compatibility. For example, you cannot sum up an integer and a string variable or you cannot pass a const variable to a function expecting a non-const variable. 
Most of these compatibility checks can be done during compile time as the type system is static. Of course, if dynamic features are used the compatibility check is moved to runtime.

7. For safe memory management, delete this can be used in destructor to delete the object, when it automatically goes out of scope. Explain, citing an example, where this would go wrong and why ? 
	
	dangling pointers: double delete will lead to undefined behavior.

2 Debug */

#include <iostream> 
#include <vector> 
using namespace std;
//original
//vector<int>& a() {//one & is a pointer that acts as a value, can only make a shodow copy, no real copy can be made.
//correct after remove the & 
vector<int> a() {
	vector<int> t{ 1,2,3 }; //local variable t stored on the stack
	return t;               //local variable t poped out from stack/deleted, since return t is invocted/executed
}
int main()
{
	vector<int> x = a();//2 after remove & at line 6, a real copy is made here, instead of a shadow copy. x = t;
	cout << x.at(1) << endl;
}
/*
1. The above program compiles with a warning stating that a() returns a local variable. Why does this program throws the warning ?
2. Fix the above program such that it returns the vector tand compiles without the warning.
*/
