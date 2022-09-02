#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

constexpr char getPartner(char ch);
constexpr bool isOpener(char ch);
constexpr int getScore(char ch);
constexpr bool isValid(char ch);

int main() {
	std::ifstream is("input.txt");

	std::vector<std::string> uncorruptLines;
	std::vector<std::string> lines;
	std::string tmpLine;
	while (std::getline(is, tmpLine)) {
		lines.push_back(tmpLine);
	}

	std::vector<char> charStack;
	int score = 0;
	for (auto line : lines) {
		int invalid = 0;
		for (auto character : line) {
			if (!isValid(character))
				continue;

			if (isOpener(character)) {
				charStack.push_back(character);	
				continue;
			}

			if (charStack.back() == getPartner(character)) {
				charStack.pop_back();
				continue;
			}

			score += getScore(character);
			invalid = 1;
			break;
		}
		if (invalid != 1) {
			uncorruptLines.push_back(line);	
		}
	}

	std::cout << score << std::endl;

	is.close();
	return 0;
}

constexpr bool isValid(char ch) {
	if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '<' || ch == '>' ) {
		return true;	
	}
	return false;
}

constexpr int getScore(char ch) {
	switch (ch) {
		case ')': return 3;
			  break;
		case ']': return 57;
			  break;
		case '}': return 1197;
			  break;
		case '>': return 25137;
			  break;
		default:
			  assert(false);
			  return 0;
			  break;
	}
}

constexpr bool isOpener(char ch) {
	return ch == '(' or ch == '[' or ch == '{' or ch == '<';
}

constexpr char getPartner(char ch) {
	switch(ch) {
		case '{': return '}';
			  break;
		case '}': return '{';
			  break;
		case '[': return ']';
			  break;
		case ']': return '[';
			  break;
		case '(': return ')';
			  break;
		case ')': return '(';
			  break;
		case '<': return '>';
			  break;
		case '>': return '<';
			  break;
		default: 
			  assert(false);
			  return '\0';
			  break;
	}
}
