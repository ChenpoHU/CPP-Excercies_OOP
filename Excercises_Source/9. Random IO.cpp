#include <iostream>
#include <fstream>

//Expression like filestream.close() can only exist in a function, for example main 
int main() {
	std::fstream filestream("fstream2.dat", std::ios::out | std::ios::trunc);
	filestream.close();  // leere Datei existiert jetzt   
						 // Datei zum Lesen und Schreiben öffnen   
	filestream.open("fstream2.dat", std::ios::in | std::ios::out);
	// schreiben   
	for (int i = 0; i < 20; ++i) {
		filestream << i << ' ';  // kein EOF direkt nach der letzten Zahl   
	}
	filestream << '\n';
	// lesen   
	filestream.seekg(0);  //seek: jump to the index 0; seek: jump to position in input/output stream either absolute or relative to positio
	// Anfang suchen   
	while (filestream.good()) {
		int i;            // Hilfsvariable     
		filestream >> i;  // lesen     
		if (filestream.good()) {
			std::cout << i << ' ';  // Kontrollausgabe     
		}
		else {
			std::cout << "\nDateiende erreicht (oder Lesefehler)";
		}
	}   std::cout << '\n';
	filestream.clear();   // EOF-Status löschen   
	filestream.seekp(5);  // Position 5 suchen   
	filestream << "neuer Text ";  // ab Pos. 5 überschreiben   
	filestream.seekg(0);          // Anfang suchen   
	char buf[100];
	filestream.getline(buf, 100);  // Zeile lesen   
	std::cout << buf << '\n';           // Kontrollausgabe
}

/*
Output:
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
Dateiende erreicht (oder Lesefehler)
0 1 2neuer Text 8 9 10 11 12 13 14 15 16 17 18 19
*/

/*
when comment out the //filestream.seekg(0); at line 30
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
Dateiende erreicht(oder Lesefehler)
6 7 8 9 10 11 12 13 14 15 16 17 18 19
*/