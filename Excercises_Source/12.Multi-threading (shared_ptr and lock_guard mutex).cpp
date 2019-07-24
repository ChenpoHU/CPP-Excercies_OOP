#include <iostream>
#include <memory> //shared pointer
#include <thread>
#include <chrono>
#include <mutex>

struct Base
{
	int b;
	Base() { std::cout << "  Base::Base()\n"; }
	Base(int b) :b(b) { std::cout << "  Base::Base(int b)\n"; }//; 
	virtual ~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	int d;
	Derived() { std::cout << "  Derived::Derived()\n"; }
	Derived(int d) :d(d) { std::cout << "  Derived::Derived(int d)\n"; }
	virtual ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // a copy, thread-safe, even though the shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}

int main()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();
	std::cout << "Created a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n';

	std::thread t1(thr, p), t2(thr, p), t3(thr, p);

	p.reset(); // release ownership from main
	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << '\n'; //use_count returns the number of shared pointers that pointing to the same object. 

	t1.join(); t2.join(); t3.join();
	std::cout << "All threads completed, the last one deleted Derived\n";
}

/*
  Base::Base()
  Derived::Derived()
Created a shared Derived (as a pointer to Base)
  p.get() = 01490574, p.use_count() = 1
Shared ownership between 3 threads and released
ownership from main:
  p.get() = 00000000, p.use_count() = 0
local pointer in a thread:
  lp.get() = 01490574, lp.use_count() = 6
local pointer in a thread:
  lp.get() = 01490574, lp.use_count() = 4
local pointer in a thread:
  lp.get() = 01490574, lp.use_count() = 2
  Derived::~Derived()
  Base::~Base()
All threads completed, the last one deleted Derived
All threads completed, the last one deleted Derived
*/