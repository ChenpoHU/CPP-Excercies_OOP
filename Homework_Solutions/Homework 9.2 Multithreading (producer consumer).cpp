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

/*2 Producer - Consumer
In this question, you are supposed to extend the producer - consumer problem(using Monitor) with the following functionalities :
1. Allow the critical section buﬀer to store more than one integer values.Length of buﬀer is provided through constructor.
2. Producer should quit after ﬁlling 10 entries to buﬀer.Modify buﬀer such that it displays the time when buﬀer is full.*/

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
	Ablage(unsigned int platz)
		: beendet(false), inhalt(std::vector<int>(platz)), anzahl(0),
		lesePos(-1), schreibPos(0) {}  // -1 als Startwert

	int get() {
		std::unique_lock<std::mutex> lock(monitorMutex);
		while (anzahl == 0) {  // leer
			cond.wait(lock);
			if (beendet) {
				throw "get()-wait beendet";
			}
		}
		--anzahl;
		cond.notify_all();
		lesePos = (lesePos + 1) % inhalt.size();
		return inhalt[lesePos];
	}
	void put(int wert) {
		std::unique_lock<std::mutex> lock(monitorMutex);
		while (anzahl == inhalt.size()) {  // voll
			cond.wait(lock);
			if (beendet) {
				throw "put()-wait beendet";
			}
		}
		inhalt[schreibPos] = wert;
		++anzahl;
		schreibPos = (schreibPos + 1) % inhalt.size();
		cond.notify_all();
	}
	void beenden() {  // Alle waits zwangsläufig beenden
		beendet = true;
		cond.notify_all();
	}

private:
	bool beendet;
	std::vector<int> inhalt;
	unsigned int anzahl;
	// Aufbau als Ringpuffer (FIFO)
	int lesePos;     // letzte gelesene Pos (nicht unsigned, s.o.)
	int schreibPos;  // nächste zu schreibende Pos
	std::mutex monitorMutex;
	std::condition_variable cond;
};

class Producer {
public:
	Producer(Ablage& a, int i) : ablage(a), id(i), zufall(100) {}
	void operator()() {
		for (int i = 0; i < 5; ++i) {
			int wert = id * 10 + i;
			std::this_thread::sleep_for(std::chrono::milliseconds(100 + zufall()));

			try {
				ablage.put(wert);
				std::lock_guard<std::mutex> lock(ausgabeMutex);
				std::cout << "Producer Nr. " << id << "  legt ab: " << wert
					<< std::endl;
			}
			catch (...) {
				;  // nichts tun, Producer ist beendet
			}
		}
		std::lock_guard<std::mutex> lock(ausgabeMutex);
		std::cout << "Producer " << id << " beendet sich." << std::endl;
	}

private:
	Ablage& ablage;
	int id;
	Random zufall;
};


class Consumer {
public:
	Consumer(Ablage& a, int i) : ablage(a), id(i) {}
	void operator()() {
		try {
			while (true) {
				int wert = ablage.get();
				std::lock_guard<std::mutex> lock(ausgabeMutex);
				std::cout << "Consumer " << id << " hat " << wert << " geholt."
					<< std::endl;
			}
		}
		catch (...) {
			std::lock_guard<std::mutex> lock(ausgabeMutex);
			std::cout << "Consumer " << id << " beendet sich." << std::endl;
		}
	}

private:
	Ablage& ablage;
	int id;
};


using namespace std;
int main() {
	Ablage ablage(10);
	Producer p1(ablage, 1);
	Producer p2(ablage, 2);
	Consumer c1(ablage, 1);
	Consumer c2(ablage, 2);
	// Threads starten:
	thread tp1(p1);
	thread tp2(p2);
	this_thread::sleep_for(chrono::milliseconds(400));
	thread tc1(c1);
	thread tc2(c2);
	// Ende der Producer abwarten:
	tp1.join();
	tp2.join();
	// warten, bis alle Objekte konsumiert worden sind
	this_thread::sleep_for(chrono::seconds(2));
	ablage.beenden();  // get-waits beenden
	tc1.join();        // Ende des Consumers 1 abwarten
	tc2.join();        // Ende des Consumers 2 abwarten
}


/*
Producer Nr. 1  legt ab: 10
Producer Nr. 2  legt ab: 20
Producer Nr. 1  legt ab: 11
Producer Nr. 2  legt ab: 21
Consumer 1 hat 10 geholt.
Consumer 1 hat 11 geholt.
Consumer 1 hat 21 geholt.
Consumer 2 hat 20 geholt.
Producer Nr. 1  legt ab: 12
Consumer 2 hat 12 geholt.
Producer Nr. 2  legt ab: 22
Consumer 1 hat 22 geholt.
Consumer 2 hat 13 geholt.
Producer Nr. 1  legt ab: 13
Producer Nr. 2  legt ab: 23
Consumer 2 hat 23 geholt.
Producer Nr. 1  legt ab: 14
Producer 1 beendet sich.
Consumer 2 hat 14 geholt.
Producer Nr. 2  legt ab: 24
Producer 2 beendet sich.
Consumer 2 hat 24 geholt.
Consumer 2 beendet sich.
Consumer 1 beendet sich.
*/