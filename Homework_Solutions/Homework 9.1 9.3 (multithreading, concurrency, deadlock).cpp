/*
1 Multithreading
1.1. A common variable counter is incremented from 10 threads 2500 times. The result is 23717. How is that possible?

Data race: A data race occurs when: two or more threads in a single process access the same memory location concurrently, and. 
at least one of the accesses is for writing, and. the threads are not using any exclusive locks to control their accesses to that memory.

1.2. How would you solve the above problem? Provide a short code example.

	atomic;
	std::lock_guard<std::mutex> lock(mtx);

1.3. Can multiple threads access a variable that is read-only safely without locking?

	yes

1.4. Which type of mutex would you use if you have multiple threads reading from the same value and only one writing to the value? Provide a short code example.

	std::lock_guard<std::mutex> lock(mtx);


1.5. How could you get two threads into a deadlock? Provide a small code example.

	A deadlock is a situation where each thread in a set of at least two threads is waiting for a resource (shared data is also considered a resource), 
	which is locked by another thread in the set. The result is that each thread in the set is waiting indefinitely for the resources to be released.
	*/
	void ueberweisen(std::string zielkontoIBAN, double betrag) { 
		lock(this); // eigenes Konto für andere sperren 
		Konto* pk = getKonto(zielkontoIBAN); 
		lock(pk); // Ziel-Konto für andere sperren 
		abheben(betrag); // eigentliche Transaktion 
		pk->einzahlen(betrag); 
		release(pk); 
		release(this); 
	}/*

Das Problem: Es könnte sein, dass gleichzeitig ein Betrag von dem anderen Konto k2 auf das Konto k1 überwiesen werden soll: */k2.ueberweisen(k1.getIBAN(), 20.95) /*
In diesem Fall könnten beide Threads gleichzeitig lock(this) ausführen – kein Problem, da es sich um verschiedene Objekte handelt. 
Aber dann bleiben sie aufeinander wartend in der Zeile lock(pk) hängen. In solchen Fällen kann eine Reihenfolge für alle vorgegeben werden.
Im Beispiel oben wäre es zweckmäßig, das Konto mit der jeweils kleineren IBAN zuerst zu sperren.

1.6. What is a critical section in a program? Give two examples of a critical section.

	11. sync of the critical sections 
	critical section, space/resources, in which the data is changed and multiple threads can access it, is called critical section. This leads to critical condition, which may leads 
	to data race. 




3 Concurrency
3.1 Concurrency 1
Consider a shared variable x = 0 which is used by three threads W,Y,Z deﬁned as per the pseudo code given below. What could be the possible value(s) of x? 
Trace the instructions executed for each value. (Assume that each instruction is executed atomically and compiler does no reordering of instructions within a thread).

global x = 0; 
W: { w = x; w = w + 1; x=w;} 
Y: { y = x; y = y + 1; x=y;} 
Z: { z = x; z = z + 1; x=z;}

x = [1,3]

3.2 Concurrency 2
Consider a C++ version of this program implemented using C++ atomic.*/

atomic<int> x = 0; 
	void w() { 
		w = x.load(); 
		w = w + 1; 
		x.store(w); 
	} 
	void y() { 
		y = x.load(); 
		y = y + 1; 
		x.store(y); 
	} 
	void z() { 
		z = x.load(); 
		z = z + 1; 
		x.store(z); 
	}

/*
1. What is/are the possible order(s) of thread execution that guarantee sequential consistency?

atomic<int> x = 0; -> w = x.load();  -> y = x.load(); -> y = y + 1; -> x.store(y); -> z = x.load(); -> w = w + 1; -> x.store(w); -> z = z + 1; -> x.store(z); 

sequential consistency:
the result of any execution is the same as-if
	1. the operations of all threads are executed in some sequential order
	2. the operations of each thread appear in this sequence in the order specified by their program

2. If each store and load is called with relaxed memory model, then what would be the possible values of x? Why?

[1,3] relaxed memory model 

• Each memory location has a total modification order (however, this order cannot be observed directly)
• Memory operations performed by the same thread on the same memory location are not reordered with respect to the modification order

3. What would be the value of x with release-acquire memory model? Why? How does it compare to relaxed memory model and sequential consistency?

3

release-acquire memory model
• a store-release operation synchronizes with all load-acquire operations reading the stored value.
• All Operations in the releasing thread preceding the store-release happen-before all operations following the load-acquire in the acquiring thread.

3.3 Deadlock
Consider the following program , which is supposed to print value of i in an increasing order.*/

#include <thread>
#include <mutex> 
#include <iostream>

	using namespace std;

	std::mutex m1, m2;
	int i = 0;
	void t1()
	{
		lock_guard<mutex> g1(m1);
		lock_guard<mutex> g2(m2);
		cout << " " << ++i << " ";
	}
	void t2()
	{
		lock_guard<mutex> g1(m2);
		lock_guard<mutex> g2(m1);
		cout << " " << ++i << " ";
	}
	int main() {
		thread t_1(t1);
		thread t_2(t2);
		while (i <= 1998) {
			t1();
			t2();
		}
		t_1.join();
		t_2.join();
	}

/*
1. What are the possible execution sequences of the program that leads to a deadlock? List any two and explain why.

lock_guard<mutex> g1(m1); -> lock_guard<mutex> g1(m2); -> lock_guard<mutex> g2(m2); -> lock_guard<mutex> g2(m1);
lock_guard<mutex> g1(m2); -> lock_guard<mutex> g1(m1); -> lock_guard<mutex> g2(m2); -> lock_guard<mutex> g2(m1);

2. Can deadlock be avoided if lock guard g2 is placed next to cout statement? Explain why.

no

3. If your answer to (2) is no, (otherwise you get the points for this question for free) then modify the program such that it doesn’t lead to a deadlock? 
Explain why. (You must use both mutexes)*/

#include <thread>
#include <mutex> 
#include <iostream>

	using namespace std;

	std::mutex m1, m2;
	int i = 0;
	void t()
	{
		unique_lock<mutex> g1(m1, std::defer_lock); //defer_lock delays the lock, the lock of which happens later here at std::lock(g1, g2);
		unique_lock<mutex> g2(m2, std::defer_lock);
		std::lock(g1, g2);
		cout << " " << ++i << " ";
		cout << " " << ++i << " ";
	}

	int main() {
		thread t_(t);
		while (i <= 1998) {
			t();
		}
		t_.join();
	}

/*
4. What is a healthy programming practice, in context or this question, to avoid deadlock?

lock a and b simultaneously (without deadlock), don't wait for another thread if there's a chance it's waiting for you.
Use an automated theorem prover for formal analysis / verification.

*/