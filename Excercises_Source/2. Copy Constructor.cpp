#include<iostream> 
using namespace std;

/*
What is a copy constructor?
A copy constructor is a member function which initializes an object using another object of the same class. A copy constructor has the following general function prototype:

	ClassName (const ClassName &old_obj);

*/

class Point
{
private:
	int x, y;
public:
	Point(int x1, int y1) { x = x1; y = y1; }

	// Copy constructor 
	Point(const Point& p2) : x(p2.x), y(p2.y) { } //or return *this; when no parameters to be copied. 

	int getX() { return x; }
	int getY() { return y; }
};

int main()
{
	Point p1(10, 15); // Normal constructor is called here 
	Point p2 = p1; // Copy constructor is called here 

	// Let us access values assigned by constructors 
	cout << "p1.x = " << p1.getX() << ", p1.y = " << p1.getY();
	cout << "\np2.x = " << p2.getX() << ", p2.y = " << p2.getY();

	return 0;
}

/*
p1.x = 10, p1.y = 15
p2.x = 10, p2.y = 15
*/

#include<iostream> 
#include<cstring> 
using namespace std;

class String
{
private:
	char* s;
	int size;
public:
	String(const char* str = NULL); // constructor 
	~String() { delete[] s; }// destructor 
	String(const String&); // copy constructor 
	void print() { cout << s << endl; } // Function to print string 
	void change(const char*);  // Function to change 
};

String::String(const char* str)
{
	size = strlen(str);
	s = new char[size + 1];
	strcpy(s, str);
}

void String::change(const char* str)
{
	delete[] s;
	size = strlen(str);
	s = new char[size + 1];
	strcpy(s, str);
}

String::String(const String& old_str)
{
	size = old_str.size;
	s = new char[size + 1];
	strcpy(s, old_str.s);
}

int main()
{
	String str1("GeeksQuiz");
	String str2 = str1;

	str1.print(); // GeeksQuiz
	str2.print(); // GeeksQuiz

	str2.change("GeeksforGeeks");

	str1.print(); // GeeksQuiz
	str2.print(); //GeeksforGeeks
	return 0;
}


MyClass t1, t2;
MyClass t3 = t1;  // ----> calls copy constructor
t2 = t1;          // ----> calls assignment operator

/*
Copy constructor is called when a new object is created from an existing object, as a copy of the existing object. 
Assignment operator is called when an already initialized object is assigned a new value from another existing object. 
*/