#include <iostream>
#include <cstddef> 
#include <algorithm>
#include <iterator>
//#include<list>

template <typename T>
class Liste {
public:   //Adds an element to top of list  
	void push_front(const T& value) {
		anfang = new ListElement(value, anfang);
	}
private:
	struct ListElement {
		T daten;
		ListElement* naechstes;
		ListElement(const T& value, ListElement* p) : daten{ value }, naechstes{ p } {      }
	};

	ListElement* anfang{ nullptr };

public:  class Iterator { //declared in scope of List  
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
};

int main() {
	Liste<int> einContainer;  // Container definition
	// Container mit beliebigen Werten füllen (hier: gerade Zahlen)
	for (int i = 0; i < 100; ++i) {
		einContainer.push_front(2 * i);
	}

//	std::list<int> list;
//	list.pop_front();

	int zahl{ 0 };
	while (zahl != -1) {
		std::cout << " gesuchte Zahl eingeben (-1 = Ende):";
		std::cin >> zahl;
		if (zahl != -1) { // weitermachen? 
						  // std::find() benutzen 
			auto position = std::find(einContainer.begin(), // Container-Methode 
				einContainer.end(), // Container-Methode 
				zahl);
			if (position == einContainer.end()) {
				std::cout << " nicht gefunden!\n";
			}
			else {
				std::cout << *position // Dereferenzierung des Iterators 
					<< " gefunden!\n";
			}
		}
	}

	std::cout << "Liste ausgeben:\n";
	for (auto iter = einContainer.begin(); iter != einContainer.end(); ++iter) { //here uses iterator ++ operator 
		std::cout << *iter << '\n';  //here uses pointer iterator 
	}
}

