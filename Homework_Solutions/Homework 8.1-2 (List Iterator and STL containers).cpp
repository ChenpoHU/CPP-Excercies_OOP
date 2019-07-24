#include <iostream>
#include <cstddef> 
#include <algorithm>
#include <iterator>


template <typename T>
class Liste {
public:
	Liste() = default;	//this enables the standard constructor, which is used in main Liste<int> einContainner.
	//Adds an element to top of list  
	void push_front(const T& value) {
		anfang = new ListElement(value, anfang);
	}

private:
	struct ListElement {
		T daten;
		ListElement* naechstes;
		ListElement(const T& value, ListElement* p) : daten{ value }, naechstes{ p } {      } //ListElement* p are the pointers between the elements (chained list)
	};
	//define the first pointer which point from the list object to the first element 
	//the other pointers are pointed from one element to another. The last element pointed to null (nullptr)
	ListElement* anfang{ nullptr };

public:  class Iterator { //declared in scope of List  
	friend class Liste;//Without this, the error "kein Zugriff auf private Member, dessen Deklaration in der Liste<int>::Iterator-Klasse erfolgte. 
public:
	// required by find() interface:    
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using pointer = T *;
	using reference = T &;
	using difference_type = ptrdiff_t;

	Iterator(ListElement* init = nullptr) : aktuellesElement{ init } {
	}
	T& operator*() {
		// Dereference      
		return aktuellesElement->daten;
	}
	const T& operator*() const {
		// Dereference      
		return aktuellesElement->daten;
	}
	Iterator& operator++() {   // Prefix      
		if (aktuellesElement) {// not reached end yet?
			aktuellesElement = aktuellesElement->naechstes;
		}
		return *this;
	}
	Iterator operator++(int) {  // Postfix     
		Iterator temp{ *this };
		++* this;
		return temp;
	}
	bool operator==(const Iterator& x) const { return aktuellesElement == x.aktuellesElement; }
	bool operator!=(const Iterator& x) const { return aktuellesElement != x.aktuellesElement; }

private:
	ListElement* aktuellesElement;  // Reference to current element  
};   // iterator scope end                              

		 Iterator begin() const { return Iterator(anfang); }
		 Iterator end() const { return Iterator(); }

		 Liste(const Liste& liste) {  // Kopierkonstruktor
			 if (liste.anfang) {
				 Iterator i{ liste.begin() };
				 push_front(*i++);  // erstes Element anlegen, anfang ist danach
									// != nullptr
				 ListElement* letztes{ anfang };
				 while (i != liste.end()) {
					 // Elemente am Ende einfügen, damit die
					 // Reihenfolge erhalten bleibt
					 letztes->naechstes = new ListElement(*i++, nullptr);
					 letztes = letztes->naechstes;
				 }
			 }
		 }

		 Liste& operator=(Liste temp) {  // Zuweisungsoperator
			 std::swap(temp.anfang, anfang);
			 return *this;
		 }

		 //Homework 8 1.1
		 //or use void pop_front() { erase(begin()); }
		 void pop_front() {
			 if (!anfang) //or anfang == nullptr
				 throw std::underflow_error("no elements left");
			 ListElement* zweites = anfang->naechstes; // *anfang.
			 delete anfang;
			 anfang = zweites;
		 }

		 //Homwork 8.1.2 
		 //Implement a method Iterator erase(Iterator p) which removes the element at position p.
		 Iterator erase(Iterator p) {
			 if (empty()) {
				 return Iterator();  // leere Liste
			 }
			 ListElement* zuLoeschen{ p.aktuellesElement };
			 // Vorgänger suchen
			 ListElement* vorgaenger{ anfang };
			 if (zuLoeschen != anfang) {
				 while (vorgaenger->naechstes != zuLoeschen) {
					 vorgaenger = vorgaenger->naechstes;
				 }
				 // Zeiger verbiegen
				 vorgaenger->naechstes = zuLoeschen->naechstes;
			 }
			 else {                           // am Anfang löschen
				 anfang = zuLoeschen->naechstes;  // Zeiger verbiegen
			 }
			 Iterator nachfolger{ ++p };
			 delete zuLoeschen;
			 return nachfolger;
		 }


		 //Homwork 8.1.4 
		 //Write a destructor for Liste class. It should do a safe destruction of list and leave no memory footprint if the variable goes out of scope.
		 void clear() {
			 while (!(anfang == nullptr)) { //or !empty()
				 pop_front();
			 }
		 }
		 bool empty() const {
			 return anfang == nullptr;
		 }
		 virtual ~Liste() {  // Destruktor
			 clear();
		 }

		 size_t size() const {
			 size_t anzahl{ 0 };
			 ListElement* temp{ anfang };
			 while (temp) {
				 ++anzahl;
				 temp = temp->naechstes;
			 }
			 return anzahl;
		 }

};

using namespace std;

int main() {
	Liste<int> einContainer;  // Container definieren

	// Container mit beliebigen Werten füllen (hier: gerade Zahlen)
	for (int i = 0; i < 100; ++i) {
		einContainer.push_front(2 * i);
	}

	int zahl{ 0 };
	while (zahl != -1) {
		cout << " gesuchte Zahl eingeben (-1 = Ende):";
		cin >> zahl;
		if (zahl != -1) {  // weitermachen?
		  // std::find() benutzen
			auto position = find(einContainer.begin(),  // Container-Methoden
				einContainer.end(), zahl);
			if (position == einContainer.end()) {
				cout << " nicht gefunden!\n";
			}
			else {
				cout << *position  // Dereferenzierung des Iterators
					<< " gefunden!\n";
			}
		}
	}
	// Liste kopieren
	Liste<int> kopie(einContainer);
	cout << "Kopie: \n";
	while (!kopie.empty()) {
		cout << *kopie.begin() << " size()=" << kopie.size() << '\n';
		kopie.pop_front();
	}
	// Liste zuweisen
	kopie = einContainer;
	cout << "zugewiesene Kopie:\n";
	while (!kopie.empty()) {
		cout << *kopie.begin() << " size()=" << kopie.size() << '\n';
		kopie.pop_front();
	}
	// Test von erase
	zahl = 6;
	auto position = find(einContainer.begin(),  // Container-Methoden
		einContainer.end(), zahl);
	auto next = einContainer.erase(position);
	cout << "Wert nach dem gelöschten: " << *next << '\n';
}

/*
2. STL
2.1. Consider the STL containers vector, list, map, array, forward list. Mention which of the containers support each of these operators : ++, --, [].
	vector: ++ -- []
	array: ++ -- []
	map: ++ -- [] : assoziative array
	list: ++ --
	forward_list: ++

2.2. Why you can not sort a std::set with std::sort?
	std::sort requires random access iterators while std::set provides only bidirectional iterators.
	Generally speaking, any try to sort a std::set contradicts to the design of this container, because it stores its elements in the sorted order.
	std::set is an associative container that contains a sorted set of unique objects of type Key.

2.3. Mention the most appropriate class of container you would use for the following scenarios:
(a) Count number of characters in a string
	array (knows the size of the string)
(b) Require fast insertion and deletion at end, but no traversal and requires less memory
	stack (end, less mem)
(c) Pick the highest bidder from a bidding queue for an auction site
	map(key and value) or set (only key)
(d) We want to store some date but order of data is not important and duplicates are not allowed.
	unordered set (only multi-set have man duplicates)
*/

/*
 gesuchte Zahl eingeben (-1 = Ende):-1
Kopie:
198 size()=100
196 size()=99
194 size()=98
192 size()=97
190 size()=96
188 size()=95
186 size()=94
184 size()=93
182 size()=92
180 size()=91
178 size()=90
176 size()=89
174 size()=88
172 size()=87
170 size()=86
168 size()=85
166 size()=84
164 size()=83
162 size()=82
160 size()=81
158 size()=80
156 size()=79
154 size()=78
152 size()=77
150 size()=76
148 size()=75
146 size()=74
144 size()=73
142 size()=72
140 size()=71
138 size()=70
136 size()=69
134 size()=68
132 size()=67
130 size()=66
128 size()=65
126 size()=64
124 size()=63
122 size()=62
120 size()=61
118 size()=60
116 size()=59
114 size()=58
112 size()=57
110 size()=56
108 size()=55
106 size()=54
104 size()=53
102 size()=52
100 size()=51
98 size()=50
96 size()=49
94 size()=48
92 size()=47
90 size()=46
88 size()=45
86 size()=44
84 size()=43
82 size()=42
80 size()=41
78 size()=40
76 size()=39
74 size()=38
72 size()=37
70 size()=36
68 size()=35
66 size()=34
64 size()=33
62 size()=32
60 size()=31
58 size()=30
56 size()=29
54 size()=28
52 size()=27
50 size()=26
48 size()=25
46 size()=24
44 size()=23
42 size()=22
40 size()=21
38 size()=20
36 size()=19
34 size()=18
32 size()=17
30 size()=16
28 size()=15
26 size()=14
24 size()=13
22 size()=12
20 size()=11
18 size()=10
16 size()=9
14 size()=8
12 size()=7
10 size()=6
8 size()=5
6 size()=4
4 size()=3
2 size()=2
0 size()=1
zugewiesene Kopie:
198 size()=100
196 size()=99
194 size()=98
192 size()=97
190 size()=96
188 size()=95
186 size()=94
184 size()=93
182 size()=92
180 size()=91
178 size()=90
176 size()=89
174 size()=88
172 size()=87
170 size()=86
168 size()=85
166 size()=84
164 size()=83
162 size()=82
160 size()=81
158 size()=80
156 size()=79
154 size()=78
152 size()=77
150 size()=76
148 size()=75
146 size()=74
144 size()=73
142 size()=72
140 size()=71
138 size()=70
136 size()=69
134 size()=68
132 size()=67
130 size()=66
128 size()=65
126 size()=64
124 size()=63
122 size()=62
120 size()=61
118 size()=60
116 size()=59
114 size()=58
112 size()=57
110 size()=56
108 size()=55
106 size()=54
104 size()=53
102 size()=52
100 size()=51
98 size()=50
96 size()=49
94 size()=48
92 size()=47
90 size()=46
88 size()=45
86 size()=44
84 size()=43
82 size()=42
80 size()=41
78 size()=40
76 size()=39
74 size()=38
72 size()=37
70 size()=36
68 size()=35
66 size()=34
64 size()=33
62 size()=32
60 size()=31
58 size()=30
56 size()=29
54 size()=28
52 size()=27
50 size()=26
48 size()=25
46 size()=24
44 size()=23
42 size()=22
40 size()=21
38 size()=20
36 size()=19
34 size()=18
32 size()=17
30 size()=16
28 size()=15
26 size()=14
24 size()=13
22 size()=12
20 size()=11
18 size()=10
16 size()=9
14 size()=8
12 size()=7
10 size()=6
8 size()=5
6 size()=4
4 size()=3
2 size()=2
0 size()=1
Wert nach dem gel÷schten: 4
*/