/*
2 Pair
Deﬁne a class Pair<T,U> that stores a pair of elements (t,u). First elements is referred as fst and second elements as snd. 
Declare an operator Pair& operator=(const Pair&) which copies the parameter. Are objects of Pair immutable? Why?

template<class T1, class T2> 
struct pair { 
	using first_type = T1;
	using second_type = T2; 
	T1 first; 
	T2 second; 
	explicit constexpr pair(const T1& x, const T2& y); 
	pair& operator=(const pair& p); 
	template<class U1, class U2> pair& operator=(const pair<U1, U2>& p); 
	void swap(pair& p) noexcept; 
	// ... 
}


3 Theory
1. Why there is a need of type checking while overloading = operator on Lecture 9, Slide 6? Explain.

	Wenn die Operation ObjektDerBasisklasse = ObjektDerUnterklasse; als Fehler betrachtet wird, 
	muss in den assign()-Methoden die Übereinstimmung der Typen mit typeid geprüft werden.

2. Why polymorphic classes require static_cast in copy assignment operator?

	Weil der Parameter vom Typ der obersten Basisklasse ist, wird er mit static_cast in den aktuellen Typ umgewandelt, 
	um dem Compiler Zugriff auf die lokalen Argumente des Parameters zu ermöglichen.

3. What could happen if one forgets to close ﬁlestream? Explain.

	- so that the operating system is notified and its resources become available again. myfile.close();
	- Once this member function is called, the stream object can be re-used to open another file, and the file is available again to be opened by other processes.
	In case that an object is destroyed while still associated with an open file, the destructor automatically calls the member function close.

4. How diﬀerent is reading and writing to a ﬁle when ios::bin option is set?

	ios::binary This causes the file to be accessed as a binary file. 
	File streams opened in binary mode perform input and output operations independently of any format considerations. 
	Non-binary files are known as text files, and some translations may occur due to formatting of some special characters 
	(like newline and carriage return characters).

5. What is the diﬀerence between ios::app and ios::ate?

	ios::ate	Set the initial position at the end of the file. If this flag is not set to any value, the initial position is the beginning of the file.

	ios::app	All output operations are performed at the end of the file, appending the content at the end of the file. 
	            This flag can only be used in streams open for output-only operations.

6. How would you append to a ﬁle from 9th last character?
	
	Randomly Reading File Content Using seekg(9)

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream IFileObject("D:\\ExampleFile.txt");
	if (!IFileObject)
	{
		cout << "File cannot be opened" << endl;
		exit(1);
	}
	string lineread;

	IFileObject.seekg(9); // move to 9th character
	// print the remaining line
	getline(IFileObject, lineread);
	cout << lineread << endl;

	getchar(); // Just To Prevent Screen from Disappearing
	cin.get(); // Just To Prevent Screen from Disappearing
}


*/