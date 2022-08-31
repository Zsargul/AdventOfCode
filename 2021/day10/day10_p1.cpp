#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int isComplete(std::vector<char> openers, std::vector<char> closers, std::string line);
int isOpener(std::vector<char> openers, char character);
int isCloser(std::vector<char> closers, char character);

int main() {
	std::ifstream is("input.txt");

	std::vector<char> openers = {'(', '[', '{', '<'};
	std::vector<char> closers = {')', ']', '}', '>'};

	std::vector<std::string> lines;
	std::string tmpLine;
	while (std::getline(is, tmpLine)) {
		lines.push_back(tmpLine);
	}

	for (auto line : lines) {
		if (isComplete(openers, closers, line, 0)) {

		}
	}

	is.close();
	return 0;
}

int correctSyntax(std::vector<char> openers, std::vector<char> closers, std::string line, int charIndex) {
	char partner;
	if (isOpener(openers, line[charIndex])) {
		partner = getPartner(closers, line[charIndex]);	
	} else if (isCloser(closers, line[charIndex])) {
		
	} else {
		std::cout << "Error: in function correctSyntax()" << std::endl;
	}
}

char getPartner(std::vector<char> characters, char character) {
	int index;
	switch (character) {
		case '(':
		case ')':
			index = 0;
			break;
		case '[':
		case ']':
			index = 1;
			break;
		case '{':
		case '}':
			index = 2;
			break;
		case '<':
		case '>':
			index = 3;
			break;
		default:
			std::cout << "Error: character \"" << character << "\" is not a valid opener/closer" << std::endl;
			exit(1);
			break;
	}
	return characters[index];
}

int isComplete(std::vector<char> openers, std::vector<char> closers, std::string line) {

	int openerCount = 0;
	int closerCount = 0;
	for (int i = 0; i < line.length(); i++) {
		if (isOpener(openers, line[i])) {
			openerCount++;
		} else if (isCloser(closers, line[i])) {
			closerCount++;
		} else {
			std::cout << "Invalid character encountered in string: " << line << std::endl;
			exit(1);
		}
	}

	if (openerCount > closerCount) {
		return 0; // Entry is incomplete
	} else if (closerCount == openerCount) {
		return 1; // Entry is complete (but may still be syntactically incorrect)	
	} else if (closerCount > openerCount) {
		std::cout << "More closers than openers?!" << std::endl;
		return 0; // Entry is incomplete
	}
}

int isOpener(std::vector<char> openers, char character) {
	for (int i = 0; i < 4; i++) {
		if (character == openers[i])
			return 1;
	}
	return 0;
}

int isCloser(std::vector<char> closers, char character) {
	for (int i = 0; i < 4; i++) {
		if (character == closers[i])
			return 1;
	}
	return 0;
}
