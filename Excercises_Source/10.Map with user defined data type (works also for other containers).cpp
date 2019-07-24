#include <iostream>
#include <map>

class Int {
private:
	int x;
public:
	Int(int y) : x(y) { }
	int get() const {
		return x;
	}
};
struct IntCompare {
	bool operator()(Int a, Int b) const {
		return a.get() < b.get();
	}
};

int main() {
	std::map<int, int, IntCompare> mymap;
	int a(5);
	int b(6);
	mymap.insert(std::make_pair(a, 5));
	mymap.insert({ b,6 });
}