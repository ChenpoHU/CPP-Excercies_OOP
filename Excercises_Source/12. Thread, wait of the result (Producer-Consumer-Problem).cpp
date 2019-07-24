#include <chrono> 
#include <iostream> 
#include <Thread>
#include <condition_variable> 
#include <mutex> 

//this is the random class 
#include <cstddef> 
#include <limits> 
#include <random>
class Random {
public:
	explicit Random(int min, int max) : verteilung(min, max) { }
	explicit Random(int max = std::numeric_limits<int>::max()) : verteilung(0, max) { }
	void setSeed(std::size_t newseed) { generator.seed(newseed); }
	int operator()() { // gibt eine Pseudo-Zufallszahl zwischen min und max zurück 
		return verteilung(generator);
	}
private:
	std::mt19937 generator;
	std::uniform_int_distribution<> verteilung; // <>: Vorgabe ist int 
};

/*
Auf den ersten Blick scheint es, dass ein mit get() wartender Consumer das Lock blockiert, sodass auch kein Producer Zugriff hat –
schließlich beziehen sie sich beide auf dieselbe Mutex-Variable.
Tatsächlich ist es nicht so, weil wait() eine wichtige Eigenschaft hat: Beim Aufruf von wait() wird implizit monitorMutex.unlock() aufgerufen,
also die Sperre gelöst! Dann geht der Thread in den Zustand »wartend«.
Nach einem notify() wird implizit monitorMutex.lock() aufgerufen, also das Lock angefordert.
Erst wenn dies gelingt, also kein anderer Thread das Lock besitzt, kehrt wait() zurück. Beide Vorgänge laufen atomar ab.
Damit wird erreicht, dass ein wartender Thread das Objekt nicht gänzlich blockiert, und dass nach wait() kein anderer Thread im Objekt aktiv ist.

*/
inline std::mutex ausgabeMutex;
class Ablage {
public:
	int get() {
		std::unique_lock<std::mutex> lock(monitorMutex);
		while (!belegt) {
			cond.wait(lock); //•wait() implicitly releases mutex •return from wait implicitly locks again
			if (beendet) {
				throw "get()-wait beendet";
			}
		}
		belegt = false;
		cond.notify_one();
		return inhalt;
	}
	void put(int wert) {
		std::unique_lock<std::mutex> lock(monitorMutex);
		while (belegt) {
			cond.wait(lock);
			if (beendet) {
				throw "put()-wait beendet";
			}
		}
		belegt = true;
		inhalt = wert;
		cond.notify_one();
	} void beenden() { // Alle wait()-Aufrufe zwangsläufig beenden 
		beendet = true;
		cond.notify_all();
	}
private:
	bool belegt{ false };
	bool beendet{ false };
	int inhalt;
	std::mutex monitorMutex;
	std::condition_variable cond;
};

class Producer {
public:
	Producer(Ablage& a, int i) : ablage(a), id{ i } {
	}

	void operator()() {
		for (int i = 0; i < 5; ++i) {
			int wert{ id * 10 + i };
			std::this_thread::sleep_for(std::chrono::milliseconds(200 + zufall()));
			try {
				ablage.put(wert);
				std::lock_guard<std::mutex> lock(ausgabeMutex); // in Ablage.h definiert 
				std::cout << "Producer Nr. " << id << " legt ab: " << wert << std::endl;
			}
			catch (...) {
				break; // Producer ist beendet 
			}

		}
		std::lock_guard<std::mutex> lock(ausgabeMutex);
		std::cout << "Producer " << id << " beendet sich." << std::endl;
	}
private:
	Ablage& ablage;
	int id;
	Random zufall{ 500 };
};

class Consumer {
public:
	Consumer(Ablage& a) : ablage(a) {
	}
	void operator()() {
		try {
			while (true) { // Abbruch mit Exception 
				int wert = ablage.get(); // Exception-Quelle 
				std::lock_guard<std::mutex> lock(ausgabeMutex);
				std::cout << "Consumer hat " << wert << " geholt." << std::endl;
			}
		}
		catch (...) {
			std::lock_guard<std::mutex> lock(ausgabeMutex);
			std::cout << "Consumer beendet sich." << std::endl;
		}
	}
private:
	Ablage& ablage;
};


using namespace std;
int main() {
	Ablage ablage;
	Producer p1(ablage, 1);
	Producer p2(ablage, 2);
	Consumer c(ablage);
	// Threads starten: 
	thread tp1(std::ref(p1));
	thread tp2(std::ref(p2));
	thread tc(std::ref(c));
	// Ende der Producer abwarten: 
	tp1.join();
	tp2.join();
	// Warten, bis alles abgeholt ist. Hier wird eine Zeitlang gewartet, weil der Consumer 
	// nicht wissen kann, wie lange noch etwas abgelegt werden könnte. 
	this_thread::sleep_for(chrono::seconds(2));
	ablage.beenden(); // wartende get()-Aufrufe beenden 
	tc.join(); // Ende des Consumers abwarten
}


/*
Producer Nr. 1 legt ab: 10
Consumer hat 10 geholt.
Consumer hat 20 geholt.
Producer Nr. 2 legt ab: 20
Producer Nr. 1 legt ab: 11
Consumer hat 11 geholt.
Consumer hat 21 geholt.
Producer Nr. 2 legt ab: 21
Consumer hat 22 geholt.
Consumer hat 12 geholt.
Producer Nr. 2 legt ab: 22
Producer Nr. 1 legt ab: 12
Consumer hat 13 geholt.
Producer Nr. 1 legt ab: 13
Producer Nr. 2 legt ab: 23
Consumer hat 23 geholt.
Producer Nr. 2 legt ab: 24
Consumer hat 24 geholt.
Consumer hat 14 geholt.
Producer 2 beendet sich.
Producer Nr. 1 legt ab: 14
Producer 1 beendet sich.
Consumer beendet sich.
*/