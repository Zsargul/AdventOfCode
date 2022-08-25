#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	// Input stream from input file
	std::ifstream is("input.txt");

	// Vector for holding input numbers
	std::vector<int> numbers;

	std::string number_as_string;

	// Get numbers (as strings) from the input stream split by commas
	while (std::getline(is, number_as_string, ',')) {
		// Add new element to end of vector
		numbers.push_back(std::stoi(number_as_string));
	}

	// Get min and max values
	int minPos = *std::min_element(numbers.begin(), numbers.end());
	int maxPos = *std::max_element(numbers.begin(), numbers.end());

	int leastFuelUsed = 1000000;
	int idealPos = 0;
	int positions = numbers.size();
	int crabSub;
	int currPos;

	// For every possible position we can move to...
	for (int i = minPos; i < maxPos; i++) {
		currPos = i;	
		int fuelUsed = 0;

		// For every crab submarine position
		for (int j = 0; j < positions; j++) {

			// Get difference
			crabSub = numbers[j];
			if (crabSub >= i) {
				fuelUsed += (crabSub - i);
			} else {
				fuelUsed += (i - crabSub);	
			}
		}

		if (leastFuelUsed > fuelUsed) {
			leastFuelUsed = fuelUsed;
			idealPos = currPos;
		}
	}

	std::cout << leastFuelUsed << ", " << idealPos << std::endl;
	return 0;
}
