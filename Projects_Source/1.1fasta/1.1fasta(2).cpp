//1.1 fasta need to be corrected 
/*
#include <iostream>
#include <fstream> 
#include <string>
#include <stdio.h>

int main() {
	FILE* fd;
	freopen_s(&fd, "C:/Users/chenp/Desktop/00_CS_Master_Kurse_SS2018/OOP C++/project1/question1/fasta-files/file2.fasta", "rb", stdin);

	unsigned int countOfCharacter[256] = {};
	bool allowedCharacters[256] = {};
	allowedCharacters['\n'] = true;
	allowedCharacters['*'] = true;
	allowedCharacters['-'] = true;
	char c;
	for (c = 'A'; c <= 'Z'; c++)
		allowedCharacters[c] = true;

	unsigned int i = 0;
	do {
		c = getchar();
		++i;
	} while (c != '\n');
	unsigned int firstLineLength = i + 1;
	unsigned int lastLineBreak = firstLineLength;
	do {
		c = getchar();
		++countOfCharacter[c];
		if (c == '\n') {
			if (i - lastLineBreak > 80) {
				std::cout << "Line too long: " << (i - lastLineBreak) << std::endl;
				return 1;
			}
			lastLineBreak = i;
		}
		++i;
	} while (c != EOF);

	i -= firstLineLength + countOfCharacter['\n'];
	std::cout << "length: " << i << std::endl;
	countOfCharacter['\n'] = 0;
	std::cout.precision(4);
	for (c = 0; c < 127; c++)
		if (countOfCharacter[c]) {
			std::cout << c << " " << countOfCharacter[c] << " " << 100.0F * countOfCharacter[c] / i << std::endl;
			if (!allowedCharacters[c]) {
				std::cout << "Forbidden character: " << c << std::endl;
				return 1;
			}
		}

	fclose(fd);
	return 0;
}
*/