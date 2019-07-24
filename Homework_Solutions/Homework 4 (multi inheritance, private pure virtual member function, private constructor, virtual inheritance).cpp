/*
1.1. Why is multiple inheritance considered bad practice in Software Engineering ?
	- ambiguity, complexity and layout of the physical objects in memory.
	- The common problem with multiple inheritance is the "diamond problem".
	- the code will be complicated and a series of bugs will go unacknowledged

	The Diamond of Dread
	Usually, you have a class A, then B and C both inherit from A. And (don't ask me why) someone then decides that D must inherit both from B and C.

	- How much of a mistake it was from the beginning (In both cases, D should not have inherited from both B and C), because this was bad architecture (in fact, C should not have existed at all...)
	--How much maintainers were paying for that, because in C++, the parent class A was present twice in its grandchild class D, and thus, updating one parent field A::field meant either updating it twice (through B::field and C::field), or having something go silently wrong and crash, later (new a pointer in B::field, and delete C::field...)
	Using the keyword virtual in C++ to qualify the inheritance avoids the double layout described above if this is not what you want, but anyway, in my experience, you're probably doing something wrong...

	In Object hierarchy, you should try to keep the hierarchy as a Tree (a node has ONE parent), not as a graph.

1.2. What could be one use case for a private pure virtual member function ? 

	A pure virtual function is a virtual function which is set to 0 i.e.declared abstract.
	A pure virtual function is used to declare a interface without implementation. 
	Private pure virtual function: It’s allowed and can be used to implement the template method design pattern.
	class Foo {
		private:
		virtual void func() = 0;
	};

1.3. Can a constructor be declared private ? If so, then mention the scenario where it would be beneﬁcial.

	One use of private constructor is to serve singleton classes. A singleton class is one which limits the number of objects creation to one. 


1.4. What are the beneﬁts of virtual inheritance ?
	++ At the most basic level, virtual inheritance deduplicates bases: if some base is inherited through multiple paths in the inheritance graph, non-virtual inheritance means multiple instances of that base in the memory footprint of the most-derived object. If the base is a virtual base on every inheritance path, there is only one instance of that base in the most-derived object.
	++ avoid diamond inheritance , such as found in iostreams (std::iostream inherits from both std::istream and from std::ostream, and those two both inherit from std::ios, virtually)
	++ Perhaps more commonly, they are used to break up super-bases; in single-inheritance languages, the base class sometimes carries data and behavior that is not needed in most of its derived classes. In C++, this behavior can be moved to another base, and only the derived classes that actually need it would co-inherit from it. Virtually, to avoid multiple instances of the base.

	-- Virtual inheritance causes troubles with object initialization and copying.
	-- Troubles with type conversions may also be a source of bugs. 
	 
Subobject & Static Lookup
2.1. Draw the Class hierarchy.
2.2. Give the subobject graphand object layout for the class hierarchy.
2.3. Perform the Static lookup for e.m().Show all the steps of this lookup.
	
	Def(E, m()) = Defs{[E,A],[E,B],[E, E.D.C],[E,S]}

	lookup(E,D) = _|_, no result, since cannot compare [E,A],[E,B]

2.4. Compare your result with your C++ compilerand mention the diﬀerences.*/

class S { /*virtual*/ int m() = 0; }; //Der reine Spezifizier ("=0") ist nur in virtuellen Funktionen zulässig 
class A : virtual S { int m() { return 10; } };
class B : virtual S { int m() { return 15; } };
class C : virtual S, virtual B { int m() { return 20; } };
class D : C { };
class E : virtual A, virtual B, D { }; //with virtual at line 1: Das Überschreiben von Funktion "S::m" (virtuell) ist mehrdeutig
main() {
	E e;
	int x = e.m(5); //E::m ist mehrdeutig 
}

//There are a few scenarios for having private constructors:
//Restricting object creation for all but friends; in this case all constructors have to be private

class A
{
private:
	A() {}
public:
	// other accessible methods
	friend class B;
};

class B
{
public:
	A* Create_A() { return new A; }  // creation rights only with `B`
};

/*Restricting certain type of constructor(i.e.copy constructor, default constructor).e.g.std::fstream doesn't allow copying by such inaccessible constructor

To have a common delegate constructor, which is not supposed to be exposed to the outer world :*/

class A
{
private:
	int x_;
	A(const int x) : x_(x) {} // common delegate; but within limits of `A`
public:
	A(const B& b) : A(b.x_) {}
	A(const C& c) : A(c.foo()) {}
};

//For singleton patterns when the singleton class is not inheritible(if it's inheritible then use a protected constructor)

	class A
{
public:
	A();
	A(int);
private:
	A(const A&);  // Neither others nor `friend` can use this
	// A(const A&) = delete;  // C++11 equivalent `private` doesn't matter
};

//Clarification: In case of singletons, a typical way is to have a public: static getInstance() method within the class, which can access the private constructor.
//	Eventually it creates and supplies object to the outer world.

	class Singleton
{
public:
	static Singleton& getInstance() {
		Singleton object; // invokes the `private` constructor
		return object;
	}
private:
	Singleton() {}  // make `protected` for further inheritance
	Singleton(const Singleton&);  // inaccessible
	Singleton& operator=(const Singleton&);  // inaccessible
};