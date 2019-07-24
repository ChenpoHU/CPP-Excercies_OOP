#include <chrono> 
#include <thread> 
#include <iostream> 

//4 threads in total, t1, t2, t3 and main()

using namespace std;
void f(int t) {
	this_thread::sleep_for(chrono::seconds(t)); // siehe oben 
	cout << "Thread " << this_thread::get_id() << " : Funktion beendet! Laufzeit = " << t << " s\n";
}
int main() {
	thread t1(f, 4);
	thread t2(f, 6);
	thread t3(f, 2);
	cout << "t1.get_id(): " << t1.get_id() << '\n';
	cout << "t2.get_id(): " << t2.get_id() << '\n';
	cout << "t3.get_id(): " << t3.get_id() << endl;
	//join
	t1.join(); // warten auf Beendigung of thread t1, which is 4s
	cout << "t1.join() ok" << endl;
	t2.join(); // warten auf Beendigung 
	cout << "t2.join() ok" << endl;
	t3.join(); // warten auf Beendigung 
	cout << "t3.join() ok\n" << "t1.get_id(): " << t1.get_id() << "\nmain() ist beendet\n";

	/*
	t.detach() blockiert den Aufrufer nicht:
	Der Aufruf kommt sofort zurück mit dem Ergebnis, dass t im Zustand repräsentiert keinen Thread ist. Der ehemals zugeordnete Thread läuft
	währenddessen weiter, bis er regulär beendet oder zwangsweise abgebrochen wird, wenn nämlich main() sich vorher beendet.
	Also: Besser join() statt detach() verwenden.
	*/

	/*	//detach
		t1.detach();
		cout << "t1.detach(): " << t1.get_id() << '\n';
		t3.detach();
		cout << "t3.detach(): " << t3.get_id() << '\n';
		t2.join();  // warten auf Beendigung des langlebigsten Threads
		cout << "main() ist beendet\n";

	*/

}

/*
join:
t1.get_id(): 19268
t2.get_id(): 3388
t3.get_id(): 9560
Thread 9560 : Funktion beendet! Laufzeit = 2 s
Thread 19268 : Funktion beendet! Laufzeit = 4 s
t1.join() ok
Thread 3388 : Funktion beendet! Laufzeit = 6 s
t2.join() ok
t3.join() ok
t1.get_id(): 0 thread::id of a non-executing thread: »non-executing thread« besagt, dass t1 zwar noch als Objekt existiert, aber keinen Thread mehr repräsentiert.
main() ist beendet
*/

/*
Tipp
Always wait for termination of started threads in main!
–otherwise end of main also abruptly terminates started threads!
–make sure all started threads terminate.
*/

/*
detach:
t1.get_id() : 25988
t2.get_id() : 10064
t3.get_id() : 19732
t1.detach() : 0 means thread::id of a non-executing thread:
t3.detach() : 0 means thread::id of a non-executing thread:
Thread 19732 : Funktion beendet!Laufzeit = 2 s
Thread 25988 : Funktion beendet!Laufzeit = 4 s
Thread 10064 : Funktion beendet!Laufzeit = 6 s
main() ist beendet
*/

