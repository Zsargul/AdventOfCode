#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

constexpr int getClosingScore(char ch);
constexpr char getPartner(char ch);
constexpr bool isOpener(char ch);
constexpr int getScore(char ch);
constexpr bool isValid(char ch);

int main() {
	std::ifstream is("input.txt");

	std::vector<std::string> lines;
	std::string tmpLine;
	while (std::getline(is, tmpLine)) {
		lines.push_back(tmpLine);
	}
	is.close();

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
	}

	// std::cout << score << std::endl;

	std::vector<size_t> scores;
	for (auto line : lines) {
		std::vector<char> chStack;
		bool isCorrupt = false;
		for (auto ch : line) {
			if (!isValid(ch))
				continue;

			if (isOpener(ch)) {
				chStack.push_back(ch);
				continue;
			}
			if (chStack.back() == getPartner(ch)) {
				chStack.pop_back();
				continue;	
			}
			isCorrupt = true;
			break;
		}
		if(!isCorrupt) {
			size_t totalScore = 0;
			while (chStack.size() != 0) {
				totalScore = totalScore * 5 + getClosingScore(getPartner(chStack.back()));
				chStack.pop_back();
			}
			std::cout << totalScore << std::endl;
			scores.push_back(totalScore);
		}
	}

	std::sort(std::begin(scores), std::end(scores));

	int length = scores.size();
	std::cout << scores[length / 2] << std::endl;


	return 0;
}

constexpr int getClosingScore(char ch) {
	switch (ch) {
		case ')': return 1;
			  break;
		case ']': return 2;
			  break;
		case '}': return 3;
			  break;
		case '>': return 4;
			  break;
		default:
			  assert(false);
			  return 0;
			  break;
	}
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
