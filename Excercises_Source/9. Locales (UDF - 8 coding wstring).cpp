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
	wstring ws(L"ÄÖÜäöüß");
	wcout.imbue(dt);
	wcout << "Ausgabe mit cout: " << ws << '\n';
	wcout << L"Länge=" << ws.length() << '\n';
	wcout << "sizeof(char_t): " << sizeof(wchar_t) << '\n';
	wofstream wdatei("ausgabe.txt");
	wdatei << "Ausgabe in ofstream: " << ws << '\n';
	for (unsigned int i = 0; i < ws.length(); ++i) {
		wdatei << "Zeichen " << i << ": " << ws[i] << '\n';
	}
	for (auto& wc : ws) {
		wc = toupper(wc, dt);
	}
	wcout << "nach toupper(): " << ws << '\n';
}

/*
Output
dt.name()= de_DE.UTF-8
Ausgabe mit cout: ÄÖÜäöüß
Länge=7
sizeof(char_t): 2
nach toupper(): ÄÖÜÄÖÜß
*/