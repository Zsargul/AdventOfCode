#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::ifstream is("input.txt");

	std::vector<int> numbers;
	std::string number_as_string;

	while (std::getline(is, number_as_string, ',')) {
		numbers.push_back(std::stoi(number_as_string));
	}

	int minPos = *std::min_element(numbers.begin(), numbers.end());
	int maxPos = *std::max_element(numbers.begin(), numbers.end());

	int leastFuelUsed = 100000000;
	int idealPos = 0;
	int positions = numbers.size();
	int crabSub;
	int currPos;
	int diff;

	for (int i = minPos; i < maxPos; i++) {
		currPos = i;
		int fuelUsed = 0;
		diff = 0;

		for (int j = 0; j < positions; j++) {

			crabSub = numbers[j];
			if (crabSub >= i) {
				diff = (crabSub - i);
			} else {
				diff = (i - crabSub);
			}

			fuelUsed += ( ((diff * (diff+1)) / 2) );
		}

		if (leastFuelUsed > fuelUsed) {
			leastFuelUsed = fuelUsed;
			idealPos = currPos;
		}
	}

	std::cout << leastFuelUsed << ", " << idealPos << std::endl;	
	return 0;
}
