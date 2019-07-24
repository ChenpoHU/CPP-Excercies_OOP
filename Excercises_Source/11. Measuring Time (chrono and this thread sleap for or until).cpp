#include <chrono> 
#include <thread>
#include <iostream>

using namespace std;
using namespace std::chrono;
int main() {
	seconds fastEinTag = hours(23) + minutes(59) + seconds(59);
	// alternativ: seconds fastEinTag = 23h + 59min + 59s;
	cout << "23h 59m 59s sind " << fastEinTag.count() << " Sekunden\n";
	auto anfang = system_clock::now();
	cout << "Rechnung läuft ..." << endl;
	double summe{ 0.0 }; // do something  
	for (long i = 0; i < 20'0000'000L; ++i)
		summe += i / 1'000'000.0;
	// Ausgabe, damit die Schleife nicht wegoptimiert wird  
	cout << "Ergebnis = " << summe << '\n';
	// Rechnung beendet, Dauer ausgeben
	nanoseconds ns = system_clock::now() - anfang;
	cout << "Dauer [ns] = " << ns.count()
		<< "\nDauer [us] = " << duration_cast<microseconds>(ns).count()
		<< "\nDauer [ms] = " << duration_cast<milliseconds>(ns).count()
		<< "\nDauer [s]  = " << duration_cast<seconds>(ns).count() << '\n';
	cout << "150 ms warten ..." << endl;
	this_thread::sleep_for(milliseconds(150));
	cout << "noch einmal warten bis (jetzt + 2 Sekunden) ..." << endl;
	auto dann = system_clock::now() + seconds(2);
	this_thread::sleep_until(dann);
}

/*
23h 59m 59s sind 86399 Sekunden
Rechnung lΣuft ...
Ergebnis = 2e+10
Dauer [ns] = 1614932600
Dauer [us] = 1614932
Dauer [ms] = 1614
Dauer [s]  = 1
150 ms warten ...
noch einmal warten bis (jetzt + 2 Sekunden) ...
*/