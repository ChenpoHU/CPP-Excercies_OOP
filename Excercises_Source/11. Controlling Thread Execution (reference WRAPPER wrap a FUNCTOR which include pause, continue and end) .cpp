#include <condition_variable> 
#include <chrono>
#include <mutex>
#include <thread> 
#include <iostream>

/*
2 threads here: thread t for functor and thread main()
It must be call by reference (using reference_wrapper), to make thread t and thread main() access the same RAM address.
*/

/*
Benötigt wird eine Referenz, über die alle Methoden des Funktors f erreichbar sind.
Deshalb gibt es eine Hüllklasse (englisch wrapper) CallWrapper, die eine Referenz auf den Funktor enthält.

Worker here is the FUNKTOR: an instance, which is used as a function.
*/

template<class Callee> // Callee = Klasse des aufzurufenden Funktors 
class CallWrapper {
public:
	CallWrapper(Callee& c) : callee(c) {}
	void operator()() {
		callee(); // = callee.operator()(): first () is the name of the operator, second () is the parameter list. 
	}
private:
	Callee& callee;
};

class Worker {
public:
	Worker() = default;

	void operator()() {
		while (!beendet) {
			std::cout << "Worker bei der Arbeit!" << std::endl;
			pauseOderNicht();
			std::this_thread::sleep_for(std::chrono::milliseconds(950)); //0r 1100, or 1200 instead of std::chrono::seconds(1)  
		}
		std::cout << "Worker macht Feierabend!" << std::endl;
	}

	void warten() {
		std::lock_guard<std::mutex> lock(mtxPause);
		pause = true;
	}
	void weiter() {
		std::lock_guard<std::mutex> lock(mtxPause); // 
		pause = false;
		cond.notify_one(); // 
	}
	void beenden() {
		beendet = true;
		cond.notify_one(); // ... falls im Zustand pausierend 
	}
	bool istBeendet() const {
		return beendet;
	}

private:
	bool pause{ false };
	bool beendet{ false };
	std::mutex mtxPause;
	std::condition_variable cond;

	void pauseOderNicht() {
		std::mutex mtx;
		std::unique_lock<std::mutex> lock(mtx);
		while (pause && !beendet) {
			std::cout << "Worker pausiert!" << std::endl;
			cond.wait(lock);
			std::cout << "Worker macht weiter!" << std::endl;
		}
	}
};

using namespace std;
int main() {
	Worker worker;
	CallWrapper<Worker> aufrufer(worker);
	//same std::reference_wrapper<Worker> aufrufer(worker); Weil C++ stellt die Klasse std::reference_wrapper zur Verfügung, die dasselbe wie die Klasse CallWrapper leistet.

	thread t(aufrufer);	// It must be call by reference (using reference_wrapper), to make thread t and thread main() access the same RAM address. Otherwise a copy will be created when call by value, which means thread t and thread main() cannot access the same address of the variable in RAM.
	int stunde{ 8 };
	while (!worker.istBeendet()) {
		this_thread::sleep_for(chrono::seconds(1));
		cout << ++stunde << " Uhr: ";
		switch (stunde) {
		case 10: worker.warten(); // Pause 
			break;
		case 13: worker.weiter(); // Fortsetzung 
			break;
		case 16: worker.beenden(); // Ende 
			t.join(); // Ende abwarten 
			break;
		default: if (stunde > 16) {
			throw "Fehler!";
		}
		}
	}
}

/*
Use std::this_thread::sleep_for(std::chrono::seconds(1)); in the worker operator()
Worker bei der Arbeit!
9 Uhr: Worker bei der Arbeit!
10 Uhr: Worker bei der Arbeit!
Worker pausiert!
11 Uhr: 12 Uhr: 13 Uhr: Worker macht weiter!
14 Uhr: Worker bei der Arbeit!
Worker bei der Arbeit!15 Uhr:
Worker bei der Arbeit!16
 Uhr: Worker macht Feierabend!
*/

/*
Der Begriff data race bedeutet, dass ein Programm mit Threads sich unterschiedlich verhält, je nachdem, welcher Thread gerade etwas schneller ist, abhängig von den race conditions.
Dieses Verhalten lässt sich im obigen Beispiel beobachten: In main() wird eine Sekunde gewartet,
im parallel laufenden Thread der Klasse Worker aber auch (siehe Worker.h oben, Methode operator()()).
Nun kann es sein (und bei nur einer CPU muss es so sein), dass diese Anweisungen nicht exakt zum selben Zeitpunkt stattfinden.
Es ist daher möglich, dass mal das eine, mal das andere Warten zuerst beendet ist.
Ersetzen Sie zum Ändern der race condition in der Methode Worker::operator()() die Zeile
	std::this_thread::sleep_for(std::chrono::seconds(1));
durch
	std::this_thread::sleep_for(std::chrono::milliseconds(950));
(bzw. 1100 statt 950).
*/

/*
use: std::this_thread::sleep_for(std::chrono::milliseconds(950)); in the worker operator()
Worker bei der Arbeit!
Worker bei der Arbeit!
9 Uhr: Worker bei der Arbeit!
10 Uhr: Worker bei der Arbeit!
Worker pausiert!
11 Uhr: 12 Uhr: 13 Uhr: Worker macht weiter!
Worker bei der Arbeit!
14 Uhr: Worker bei der Arbeit!
15 Uhr: Worker bei der Arbeit!
16 Uhr: Worker macht Feierabend!
*/

