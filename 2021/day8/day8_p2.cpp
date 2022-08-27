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

bool arePerm(std::string str1, std::string str2);

int decode(const std::string& signals, const std::string& outputs);

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
	std::string ws = " ";
	outputVector.erase(std::remove(outputVector.begin(), outputVector.end(), ws), outputVector.end());
	signalVector.erase(std::remove(signalVector.begin(), signalVector.end(), ws), signalVector.end());

	int total = 0;
	for (int i = 0; i < length; i++) {
		total +=decode(signalVector[i], outputVector[i]);
	}
	std::cout << total << std::endl;
}

int decode(const std::string& signals, const std::string& outputs) {
	std::vector<std::string> signalSection;
	std::vector<std::string> outputSection;

	std::stringstream sig(signals);
	std::stringstream out(outputs);

	/* Split input strings into vectors */
	std::string tmp;
	while(std::getline(sig, tmp, ' ')) {
		signalSection.push_back(tmp);
	}	
	while(std::getline(out, tmp, ' ')) {
		outputSection.push_back(tmp);	
	}

	std::string ws = "";
	outputSection.erase(std::remove(outputSection.begin(), outputSection.end(), ws), outputSection.end());
	signalSection.erase(std::remove(signalSection.begin(), signalSection.end(), ws), signalSection.end());
	
	//          2    4     3      7
	std::string one, four, seven, eight; 
	std::string two, three, five, six, nine, zero;
	//          5    5      5     6    6     6
	
	char top, bottom, tleft, tright, bleft, bright, mid;

	// Find one, four, seven and eight
	for(auto signal : signalSection) {
		switch (signal.length()) {
			case 2:
				one = signal;
				break;
			case 4:
				four = signal;
				break;
			case 3:
				seven = signal;
				break;
			case 7:
				eight = signal;
				break;
			default:
				break;
		}
	}

	// Get top bar from the rendering of 7
	for (int i = 0; i < 3; i++) {
		if ((seven[i] != one[0]) && (seven[i] != one[1])) {
			top = seven[i];
		}
	}

	// Find three
	for (auto signal : signalSection) {
		if (signal.length() == 5 && signal.find(top) != std::string::npos) {
			// Leaves us with Five, Three, or Two
			if (signal.find(one[0]) != std::string::npos && signal.find(one[1]) != std::string::npos) {
				three = signal;
			}
		}
	}

	// Find nine
	for (auto signal : signalSection) {
		if (signal.length() == 6) {
			if (
			signal.find(three[0]) != std::string::npos &&
			signal.find(three[1]) != std::string::npos &&
			signal.find(three[2]) != std::string::npos &&
			signal.find(three[3]) != std::string::npos &&
			signal.find(three[4]) != std::string::npos) {
				nine = signal;
			}
		}	
	}

	// Find Top left bar from the rendering of 9
	for (int i = 0; i < 6; i++) {
		if (three.find(nine[i]) == std::string::npos) {
			tleft = nine[i];
		}
	}

	// Find five
	for (auto signal : signalSection) {
		if (signal.length() == 5 && signal.find(tleft) != std::string::npos) {
			five = signal;
		}		
	}

	// Find two
	for (auto signal : signalSection) {
		if (signal.length() == 5 && signal != five && signal != three) {
			two = signal;
		}
	}

	// Find middle bar
	for (int i = 0; i < 4; i++) {
		if (four[i] != tleft && four[i] != one[0] && four[i] != one[1]) {
			mid = four[i];
		}
	}

	// Find six
	for (auto signal : signalSection) {
		if (signal.length() == 6 && signal != nine && signal.find(mid) != std::string::npos) {
			six = signal;
		}
	}
	// Find zero
	for (auto signal : signalSection) {
		if (signal.length() == 6 && signal != nine && signal != six) {
			zero = signal;
		}
	}


	// Find top right bar using rendering of 2
	for (int i = 0; i < 5; i++) {
		if (two[i] == one[0] || two[i] == one[1]) {
			tright = two[i];
		}
	}

	// Find bottom right bar using rendering of 5
	for (int i = 0; i < 5; i++) {
		if (five[i] == one[0] || five[i] == one[1]) {
			bright = five[i];
		}
	}

	// Find bottom using rendering of 3
	for (int i = 0; i < 5; i++) {
		if (
		three[i] != top &&
		three[i] != mid &&
		three[i] != tright &&
		three[i] != bright) {
			bottom = three[i];
		}
	}

	for (int i = 0; i < 5; i++) {
		if (
		two[i] != top &&
		two[i] != bottom &&
		two[i] != tright &&
		two[i] != mid) {
			bleft = two[i];
		}
	}

	/*
	std::cout << "Nine: " << nine << std::endl;
	std::cout << "Eight: " << eight << std::endl;
	std::cout << "Seven: " << seven << std::endl;
	std::cout << "Six: " << six << std::endl;
	std::cout << "Five: " << five << std::endl;
	std::cout << "Four: " << four << std::endl;
	std::cout << "Three: " << three << std::endl;
	std::cout << "Two: " << two << std::endl;
	std::cout << "One: " << one << std::endl;
	std::cout << "Zero: " << zero << std::endl;

	std::cout << "Top: " << top << std::endl;
	std::cout << "Bot: " << bottom << std::endl;
	std::cout << "Mid: " << mid << std::endl;
	std::cout << "Tleft: " << tleft << std::endl;
	std::cout << "Tright: " << tright << std::endl;
	std::cout << "Bleft: " << bleft << std::endl;
	std::cout << "Bright: " << bright << std::endl;
	*/


	int digitOutputs[4];
	for (int i = 0; i < 4; i++) {
		switch (outputSection[i].length()) {
			case 2:
				digitOutputs[i] = 1;
				break;
			case 3:
				digitOutputs[i] = 7;
				break;
			case 4:
				digitOutputs[i] = 4;
				break;
			case 7:
				digitOutputs[i] = 8;
			        break;	
			case 5:
				if (arePerm(outputSection[i], five)) {
					digitOutputs[i] = 5;	
				} else if (arePerm(outputSection[i], three)) {
					digitOutputs[i] = 3;
				} else {
					digitOutputs[i] = 2;
				}
				break;
			case 6:
				if (arePerm(outputSection[i], zero)) {
					digitOutputs[i] = 0;
				} else if (arePerm(outputSection[i], six)) {
					digitOutputs[i] = 6;
				} else {
					digitOutputs[i] = 9;
				}
				break;
			default:
				std::cout << "Something went wrong!" << std::endl;
				exit(0);
		}
	}

	int outputSum = 0;
	int multiplier = 1;
	for (int i = 3; i >= 0; i--) {
		outputSum += digitOutputs[i] * multiplier;
		multiplier *= 10;
	}

	return outputSum;
}

bool arePerm(std::string str1, std::string str2) {
	int n1 = str1.length();
	int n2 = str2.length();

	if (n1 != n2)
		return false;

	std::sort(str1.begin(), str1.end());
	std::sort(str2.begin(), str2.end());

	for (int i = 0; i < n1; i++) {
		if (str1[i] != str2[i])
			return false;
	}

	return true;
}
