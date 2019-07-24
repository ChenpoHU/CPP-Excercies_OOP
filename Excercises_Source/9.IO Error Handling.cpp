#include <iostream>
#include <fstream>

int main() {
	std::ios::iostate status;
	while (true) {  // Schleifenabbruch mit break    
		int i;
		std::cout << "Zahl (Ctrl+D oder Ctrl+Z = Ende):";
		std::cin >> i;
		status = std::cin.rdstate();    // Ausgabe der Statusbits    
		std::cout << "status = " << status << '\n';
		std::cout << "good() = " << std::cin.good() << '\n';
		std::cout << "eof()  = " << std::cin.eof() << '\n'; //end of file, only possible when there is a file 
		std::cout << "fail() = " << std::cin.fail() << '\n';
		std::cout << "bad()  = " << std::cin.bad() << '\n';
		if (std::cin.eof()) {
			break;  // Abbruch    
		}    // Fehlerbehandlung bzw. Ausgabe    
		if (status) {
			std::cin.clear();  // Fehlerbits zurücksetzen      
			std::cin.get();    // ggf. fehlerhaftes Zeichen entfernen    
		}
		else
			std::cout << "*** " << i << '\n';
	}
}


/*
Output:
Zahl(Ctrl + D oder Ctrl + Z = Ende) : 67348
status = 0
good() = 1
eof() = 0
fail() = 0
bad() = 0
* **67348
Zahl(Ctrl + D oder Ctrl + Z = Ende) :3456467587699809
status = 2
good() = 0
eof() = 0
fail() = 1
bad() = 0
*/

