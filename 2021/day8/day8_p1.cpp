#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <algorithm>

/*
 * 1	-	2 segments *
 * 2	-	5 segments
 * 3	-	5 segments
 * 4	-	4 segments *
 * 5	-	5 segments
 * 6	-	6 segments 
 * 7	- 	3 segments *
 * 8	-	7 segments *
 * 9	-	6 segments
 * 0	-	6 segments
 */

int main() {
	// Get input and split it into two vectors
	std::ifstream is("input.txt");
	std::vector<std::string> entryVector;

	std::string line;
	std::string outputs;

	while (std::getline(is, line, '\n')) {
		entryVector.push_back(line);
	}	

	std::vector<std::string> signalVector;
	std::vector<std::string> outputVector;

	for (auto entry : entryVector) {
		char *str = new char[entry.length() + 1];
		strcpy(str, entry.c_str());
		char *token = strtok(str, "|");
		int counter = 1;

		while (token != NULL) {
			if (counter == 1)
				signalVector.push_back(token);
			else if (counter == 2)
				outputVector.push_back(token);
				token = strtok(NULL, "|");
			counter++;
		}
		delete [] str;
	}

	int length;
	if (signalVector.size() != outputVector.size()) {
		std::cout << "SignalVector and OutputVector and not the same size" << std::endl;
		exit(0);
	} else {
		length = signalVector.size();
	}

	/*
	for (int i = 0; i < length; i++) {
		std::cout << "SignalVec: " << signalVector[i] << std::endl;
		std::cout << "OutputVev: " << outputVector[i] << std::endl;
	}
	*/

	std::vector<std::string> digitVector;
	std::string tmp;
	for (int j = 0; j < length; j++) {
		std::string s = outputVector[j];
		std::stringstream ss(s);
		while(std::getline(ss, tmp, ' ')) {
			digitVector.push_back(tmp);
		}
	}
	
	// Strip empty spaces
	std::string ws = "";
	digitVector.erase(std::remove(digitVector.begin(), digitVector.end(), ws), digitVector.end());

	int l;
	int count;
	for (auto digit : digitVector) {
	 	l = digit.length();
		
		/*
		 * One : 2
		 * Four : 4
		 * Seven : 3
		 * Eight : 7
		 */
		if (l == 2 || l == 4 || l == 3 || l == 7) 
			count++;
	}
	std::cout << count << std::endl;
}
