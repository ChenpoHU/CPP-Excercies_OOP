class Top {
public:
	virtual ~Top() {}; // at least one virtual to make it polymorpher, to make dynamic_cast work. 
	int a;
};
class Left : virtual public Top { //without virtual inheritance: Die Basisklasse "Top" ist mehrdeutig. 
public:
	int b;
};
class Right : virtual public Top {
public:
	int c;
};
class Bottom : public Left, public Right {
public:
	int d;
};
class AnotherBottom : public Left, public Right {
public:
	int e;
	int f;
};



int main() {
	Bottom* bottom1 = new Bottom();

	Sinus(Sinus::Modus::Grad)(45);

	//•memory layout of Right itself is completely different 
	//•can thus no longer access a “real” Right object in the same way as an upcasted Bottom object 
	//•no other(simple) layout for Bottom will work
	Right* right = bottom1;
	AnotherBottom* bottom2 = new AnotherBottom();
	Top* top1 = bottom1; // only works when it use the virtual inheritance 
	//without virtual: merdeutige Konvertierung von "Bottom*" in "Top*".
	Top* top2 = bottom2; // only works when it use the virtual inheritance 
	Left* left = dynamic_cast<Left*>(top1); //only works with virtual ~Top() {};
	delete bottom1;
	//delete bottom1; by doubled delete: Ausnahme ausgelöst bei 0x00A22431 in CPPExcercise.exe: 0xC0000005: Zugriffsverletzung beim Lesen an Position 0xDDDDDDE1.
	delete bottom2;
}


//Left* left = static_cast<Left*>(top1); 
//::der Zeiger auf die Basisklasse "Top" kann nicht in den Zeiger auf die abgeleitete Klasse "Left" konvertiert werden. Die Basisklasse ist virtuell. 
//:: Konvertierung von "Top*" in "Left*" nicht möglich; implizite Konvertierung einer virtuellen Basisklasse. 

//Left* left = dynamic_cast<Left*>(top1); 
//::with out a virtual in parent: "Top" ist kein polymorpher Typ. 
//::with out a virtual in parent: Der Operand einer dynamic_cast zur Laufzeit muss einen polymorphen Klassentyp aufweisen.

