/*
1. How do you safely use of a dynamic cast?
	dynamic_cast: Safely converts pointers and references to classes up, down, and sideways along the inheritance hierarchy.run-time check
	static_cast: Converts between types using a combination of implicit and user-defined conversions. only compile time check

	If the cast fails and new_type is a pointer type, it returns a null pointer of that type. 
	If the cast fails and new_type is a reference type, it throws an exception that matches a handler of type std::bad_cast.

	It will be a safe dynamic cast as long as the argument to dynamic_cast is a valid pointer (including NULL). If you pass a dangling pointer or a value that is garbage, 
	then the call to dynamic_cast is not guaranteed to be safe. In fact, the best case scenario is that the run time system throws an exception and you can deal with it. 
	The worst case scenario is that it is undefined behavior. 

	dynamic_cast will also fail if either base class is not polymorphic (the presence of virtual functions is NOT optional)
	
2. Why would you catch the most general exception in the end?

	catch any exception via catch(…), so that if any un-foresee exception occurs, they will print the errors and optionally terminate the programm 
	instead of programm crash.   

	Swallowing critical exceptions will cause your program to do either of two things –  to fail in unexpected ways downstream or prevent the program from fulfilling it’s purpose. 
	Sometimes programmers will catch any exception via catch(…) and then swallow them . This is usually done for exceptions that the programmer did not foresee happening. 
	However, this can lead to downstream failure – sometimes with no obvious reason for the failure since the stacktrace disappears with the swallowed exception.

	Therefore, to avoid two exceptions being active at the same time, destructors must not throw exceptions.
	Always throw an exception by value and catch by reference or const reference if possible.

3. Why dynamic cast is not applicable for inheritance having no virtual functions?

	For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table), then are not polymorphic. 
	Because dynamic_cast can only downcast polymorphic types, so sayeth the Standard. You can make your class polymoprphic by adding a virtual destructor to the base class

4. Explain two scenarios where errno is not a good idea for error handling?

	errno, perror(). and strerror()
	The C programming language provides perror() and strerror() functions which can be used to display the text message associated with errno.
	The perror() function displays the string you pass to it, followed by a colon, a space, and then the textual representation of the current errno value.
	The strerror() function, which returns a pointer to the textual representation of the current errno value. 

static_cast vs dynamic_cast: https://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast
							 https://docs.microsoft.com/en-us/cpp/cpp/type-conversions-and-type-safety-modern-cpp?view=vs-2019 
*/

/*
2.1. What is the output output at line 22? Justify.
2.2. What is the diﬀerence in the output at line 22 if both Left and Right virtually inherit Top? Justify.
2.3. How does the object layout diﬀer in case of virtual inheritance?
2.4. Assume that class Top deﬁnes a method foo(). How many dereferences are required for calling the method through object bot. Why?
2.5. What is the value of lb->k and rb->k. Explain
*/

#include <iostream>

class Top {
public:
	int a = 1;
	int k = 1;
	//virtual ~Top() {}
};
//class Left :virtual public Top {
class Left : public Top {
public:
	int b = 2;
	int k = 2;
};
//class Right :virtual public Top {
class Right : public Top {
public:
	int c = 3;
	int k = 3;
};
class Bottom : public Left, public Right {
	//class Bottom :  public Left,  public Right {
public:
	int d = 4;
	int k = 4;
};
int main() {
	Bottom* bot = new Bottom();
	Top* lb = (Left*)bot;
	//Top* lb = static_cast<Left*>(bot);

	Top* rb = (Right*)bot;
	//Top* rb = static_cast<Right*>(bot);

	std::cout << sizeof(Bottom) << std::endl; //(Bottom) 40            //virtual 44 (one more v-ptr in the v table, so 4 byte more)
	std::cout << sizeof(Left) << std::endl;   //16 (Left, Top::Left)   //virtual 20
	std::cout << sizeof(Right) << std::endl;  //16 (Right,Top::Right)  //virtual 20
	std::cout << sizeof(Top) << std::endl;    //8 (Top)

	std::cout << sizeof(bot) << std::endl;    //4
	std::cout << sizeof(lb) << std::endl;     //4
	std::cout << sizeof(rb) << std::endl;     //4
	std::cout << sizeof(int) << std::endl;    //4

	std::cout << bot->k << std::endl;         //4
	std::cout << lb->k << std::endl;          //1 lb as Top pointer with the top perspective has the folloing k: 1, 2 (invisible), 4 (invisible). 
	std::cout << rb->k << std::endl;          //1 rb as Top pointer with the top perspective has the folloing k: 1, 3 (invisible), 4 (invisible). 

	std::cout << (char*) & (bot->b) - (char*)bot << std::endl; //24
	std::cout << (char*) & (bot->c) - (char*)bot << std::endl; //36
	std::cout << (char*) & (bot->k) - (char*)bot << std::endl; //8
}
