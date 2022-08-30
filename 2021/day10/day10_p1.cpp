#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::ifstream is("input.txt");

	std::vector<char> openers = {'(', '[', '{', '<'};
	std::vector<char> closers = {')', ']', '}', '>'};

	std::vector<std::string> lines;
	std::string tmpLine;
	while (std::getline(is, tmpLine)) {
		lines.push_back(tmpLine);
	}

	is.close();
	return 0;
}
