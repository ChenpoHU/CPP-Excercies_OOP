#include <iostream> 
#include <string> 
#include <locale> 
#include <fstream> // is_signed 
using namespace std;

//char probably has 8 bits, wchar probably 16 bits 

int main() {
	locale dt("de_DE.UTF-8");
	cout << "dt.name()= " << dt.name() << '\n';  // Ausgabe mit cout stört nachfolgende cout-Ausgaben (GNU C++ // 4.x)
	locale::global(dt);  // dt fuer alles setzen  
	string ws("ÄÖÜäöüß");
	cout.imbue(dt);
	cout << "Ausgabe mit cout: " << ws << '\n';
	cout << "Länge=" << ws.length() << '\n';
	cout << "sizeof(char_t): " << sizeof(char) << '\n';
	ofstream datei("ausgabe.txt");
	datei << "Ausgabe in ofstream: " << ws << '\n';
	for (unsigned int i = 0; i < ws.length(); ++i) {
		datei << "Zeichen " << i << ": " << ws[i] << '\n';
	}
	for (auto& wc : ws) {
		wc = toupper(wc, dt);
	}
	cout << "nach toupper(): " << ws << '\n';
}

/*
Output
dt.name()= de_DE.UTF-8
Ausgabe mit cout: ÄÖÜäöüß
Länge=14
sizeof(char_t): 1
nach toupper(): ÄÖÜÄÖÜß
*/
