#include<iostream> 
using namespace std;
//*this can be used in 2 situations, here is the second one
//1) When local variable’s name is same as member’s name: this-> x = x;
//2) To return reference to the calling object

class Test
{
private:
	int x;
	int y;
public:
	Test(int x = 0, int y = 0) { this->x = x; this->y = y; }
	//When a reference to a local object is returned, the returned reference can be used to chain function calls on a single object.
	Test& setX(int a) { x = a; return *this; }//normally progamm like void setX(int a){x=a;}
	Test& setY(int b) { y = b; return *this; }
	void print() { cout << "x = " << x << " y = " << y << endl; }
};

int main()
{
	Test obj1(5, 5);

	// Chained function calls.  All calls modify the same object 
	// as the same object is returned by reference 
	obj1.setX(10).setY(20);

	obj1.print();
	return 0;
}

/*
x = 10 y = 20
*/

/*
If line 12 or 13 does not has &, then it won´t be correct, the output will be:
x = 10 y = 0
*/