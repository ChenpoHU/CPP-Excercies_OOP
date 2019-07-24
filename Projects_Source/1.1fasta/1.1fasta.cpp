//1.1 fasta

#include <iostream>
#include <fstream> 
#include <string>

int main() {
	std::ifstream is("C:/Users/chenp/Desktop/00_CS_Master_Kurse_SS2018/OOP C++/project1/question1/fasta-files/file2.fasta", std::ifstream::binary);
	// std::string line;

	if(is) {
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		unsigned int countOfCharacter[256] = {};
		bool allowedCharacters[256] = {};
		allowedCharacters['*'] = true;
		allowedCharacters['-'] = true;
		for (char c = 'A'; c <= 'Z'; c++)
			allowedCharacters[c] = true;

		unsigned int i = 0;
		for(; i < length; i++) {
			char c;
			is.get(c);
			if (c == '\n')
				break;
		}
		unsigned int lastLineBreak = i, firstLineLength = i;
		for(; i < length; i++) {
			char c;
			is.get(c);
			++countOfCharacter[c];
			if (c == '\n') {
				if (i - lastLineBreak > 80) {
					std::cout << "Line too long: " << (i - lastLineBreak) << std::endl;
					return 1;
				}
				lastLineBreak = i;
			}
		}

		length -= firstLineLength+countOfCharacter['\n'];
		std::cout << "length: " << length << std::endl;
		countOfCharacter['\n'] = 0;
		std::cout.precision(4);
		for (char c = 0; c < 127; c++)
			if (countOfCharacter[c]) {
				std::cout << c << " " << countOfCharacter[c] << " " << 100.0F * countOfCharacter[c] / length << std::endl;
				if (!allowedCharacters[c]) {
					std::cout << "Forbidden character: " << c << std::endl;
					return 1;
				}
			}
	}
	return 0;
}
