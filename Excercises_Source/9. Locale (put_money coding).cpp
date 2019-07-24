#include <iomanip> //showbase
#include <iostream> //imbue; locale; putmoney; cout 
#include <string>

int main() {
	std::cout << std::showbase; // Basis anzeigen, hier Währungsymbol anzeigen 
	long double money_d = 12345; // Betrag in Cent 
	std::cout.imbue(std::locale("de_DE.utf8")); // siehe Kapitel 30 
	std::cout << std::put_money(money_d) << '\n'; // 123,45 e 
	std::cout << std::put_money(money_d, true) << '\n'; // 123,45 EUR 
	std::string money_str = "12345"; // Betrag in Cent 
	std::cout.imbue(std::locale("en_US.utf8")); // siehe Kapitel 30 
	std::cout << std::put_money(money_str) << '\n'; // $123.45 
	std::cout << std::put_money(money_str, true) << '\n'; // USD 123.45 
}

/*
Ouput:
123,45 Γé¼
EUR123,45
$123.45
USD123.45
*/

/*
imbue is inherited by std::ostringstream from std::ios_base and it sets the locale of the stream to the specified locale.
This affects the way the stream prints (and reads) certain things; for instance, setting a French locale will cause the decimal point.
*/