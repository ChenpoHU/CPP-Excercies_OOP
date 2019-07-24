//The program below is supposed to print ”Yes” if the two inputs are equal, ”No” otherwise. 
#include <iostream> 
using namespace std; 
int main() { 
	int a, b; 
	cin >> a >> b; 
	if (a == b) //original (a = b)
		cout << "Yes" << endl; 
	else 
		cout << "No" << endl; 
}

/*
1.1. For what values of a and b would the program print ”Yes” ? Explain.
   if b is no 0, since the code a=b is that b is assigned to a.
1.2. Does the program satisfy the intended behaviour ? Explain.If not, modify the program such that it produces the intended result.
	no, a == b

2.1. What is a reference variable ? How is it diﬀerent from a pointer variable ?

	Pointers: A pointer is a variable that holds memory address of another variable. 
		A pointer needs to be dereferenced with * operator to access the memory location it points to.
	References : A reference variable is an alias, that is, another name for an already existing variable. 
		A reference, like a pointer is also implemented by storing the address of an object.

(1).Initalisation: A pointer can be initalised in this way:*/
int a = 10;
int* p = &a;
//or
int* p;
p = &a;
//we can declareand initalise pointer at same step or in multiple line.
//reference:
int a = 10;
int& p = a;
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
int* p;
int** q;  //it is valid.
p = &a;
q = &p;

//Whereas in refrences,

int& p = a;
int&& q = p; /*it is reference to reference, so it is an error.

(6)Arithmetic operations: Various arithmetic operations can be performed on pointers whereas there is no such thing called Reference Arithmetic.


2.2. What’s the diﬀerence between C - style strings and C++ style - strings ?

	A C-string, which consists of an array of char terminated by the null character '\0', and which therefore is different from an ordinary array of characters. 
	There is a whole library of functions for dealing with strings represented in this form. Its header file is <cstring>.

	A C++ string object, which is an instance of a "class" data type whose actual internal representation you need not know or care about, 
	as long as you know what you can and can't do with variables (and constants) having this data type. 
	There is a library of C++ string functions as well, available by including the <string> header file.*/

C-strings  (#include <cstring>)         C++ strings  (#include <string>)
===============================         ================================
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Declaring a C-string variable           Declaring a C++ string object
-----------------------------           -----------------------------
char str[10];                           string str;

Initializing a C-string variable        Initializing a C++ string object
--------------------------------        --------------------------------
char str1[11] = "Call home!";           string str1("Call home!");
char str2[] = "Send money!";            string str2 = "Send money!";
char str3[] = {'O', 'K', '\0'};         string str3("OK");
Last line above has same effect as:
char str3[] = "OK";
										string str4(10, 'x');

Assigning to a C-string variable        Assigning to a C++ string object
--------------------------------        --------------------------------
Can't do it, i.e., can't do this:       string str;
				                        str = "Hello";
				                        str = otherString;

Concatenating two C-strings             Concatenating two C++ string objects
---------------------------             ------------------------------------
strcat(str1, str2);                     str1 += str2;
strcpy(str, strcat(str1, str2));        str = str1 + str2;

Copying a C-string variable             Copying a C++ string object
---------------------------             ---------------------------
char str[20];                           string str;
strcpy(str, "Hello!");                  str = "Hello";
strcpy(str, otherString);               str = otherString;

Accessing a single character            Accessing a single character
----------------------------            ----------------------------
str[index]                              str[index]
										str.at(index)
										str(index, count)

Comparing two C-strings                 Comparing two C++ string objects
-----------------------                 --------------------------------
if (strcmp(str1, str2) < 0)             if (str1 < str2)
	cout << "str1 comes 1st.";              cout << "str1 comes 1st.";
if (strcmp(str1, str2) == 0)            if (str1 == str2)
	cout << "Equal strings.";               cout << "Equal strings.";
if (strcmp(str1, str2) > 0)             if (str1 > str2)
	cout << "str2 comes 1st.";              cout << "str2 comes 1st.";

Finding the length of a C-string        Finding the length of a C++ string object
--------------------------------        -----------------------------------------
strlen(str)                             str.length()

Output of a C-string variable           Output of a C++ string object
-----------------------------           -----------------------------
cout << str;                            cout << str;
cout << setw(width) << str;             cout << setw(width) << str;

/*
2.3. What is a namespace ?

A namespace is a declarative region that provides a scope to the identifiers (the names of types, functions, variables, etc) inside it. 

Namespaces are used to organize code into logical groups and to prevent name collisions that can occur especially when your code base includes multiple libraries. 
All identifiers at namespace scope are visible to one another without qualification. Identifiers outside the namespace can access the members by using the fully qualified name for each identifier, 
for example std::vector<std::string> vec;, or else by a using Declaration for a single identifier (using std::string), or a using Directive for all the identifiers in the namespace (using namespace std;). 
Code in header files should always use the fully qualified namespace name.

2.4. Consider the program fragment */auto a; cin >> a;/* .This will not compile with an error stating a not being initialized. Explain why this fragment is not allowed ?

*/auto a; 

is incorrect, for every variable, the type needs to be known at the declaration/compile time. Here it cannot be inferred (find a type), because there is no assignment.
auto happens at compile time (delcarition), User input happens at runtime.

/*
The type that actually gets used is determined by the value used to initialize the variable at compile time. 
It has nothing to do with the ability to determine the type of variable to use at runtime.
For example, if you write auto x = 0, the compiler sees that you're initializing the variable with an int and pretty much compiles it as if it was int x = 0.

std::string default_name = "";
auto name = default_name;

cin >> name;
*/