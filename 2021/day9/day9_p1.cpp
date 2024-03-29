#include <iostream>
#include <fstream>
#include <vector>

const int invalid = -1; // Assigned to an adjacent position when said position does not exist

bool isCenterLowest(int center, int up, int down, int left, int right);

int main() {

	std::ifstream is("input.txt");

	std::vector< std::vector<int> > lavaMap;	
	std::string numbers_as_string;
	
	std::string tmpLine;
	while (std::getline(is, numbers_as_string)) {
		std::vector<int> tmpRow;
		tmpLine = numbers_as_string;
	
		// Convert line into separate digits
		int tmpNum;
		for (int i = 0; i < tmpLine.length(); i++) {
			tmpNum = (int)tmpLine[i] - 48;
			tmpRow.push_back(tmpNum);
		}
		lavaMap.push_back(tmpRow);
	}

	/*
	for (auto line : lavaMap) {
		for (auto number : line) {
			std::cout << number;
		}
		std::cout << std::endl;
	}
	*/

	const int horiz_length = lavaMap[0].size();
	const int vert_length = lavaMap.size();

	int riskLevel, riskSum = 0;
	int center, up, down, left, right;
	for (int y = 0; y < vert_length; y++) { // Rows
		for (int x = 0; x < horiz_length; x++) { // Columns
			center = lavaMap[y][x];
			if (y == 0) { // First row
				up = invalid;
				if (x == 0) { // Top left corner
					left = invalid;	
					right = lavaMap[y][x+1];
				} else if (x == horiz_length-1) { // Top right corner
					left = lavaMap[y][x-1];
					right = invalid;
				} else { // Top middle
					left = lavaMap[y][x-1];
					right = lavaMap[y][x+1];
				}
				down = lavaMap[y+1][x];
			} else if (y == vert_length-1) { // Last row
				down = invalid;
				if (x == 0) { // Bottom left corner
					left = invalid;
					right = lavaMap[y][x+1];
				} else if (x == horiz_length-1) { // Bottom right corner
					left = lavaMap[y][x-1];
					right = invalid;
				} else { // Bottom center
					left = lavaMap[y][x-1];
					right = lavaMap[y][x+1];
				}
				up = lavaMap[y-1][x];
			} else { // Somewhere in the middle
				if (x == 0) { // Left edge
					left = invalid;
					right = lavaMap[y][x+1];
				} else if (x == horiz_length-1) { // Right edge
					left = lavaMap[y][x-1];
					right = invalid;
				} else { // Middle
					left = lavaMap[y][x-1];
					right = lavaMap[y][x+1];
				}
				up = lavaMap[y-1][x];
				down = lavaMap[y+1][x];
			}
			if (isCenterLowest(center, up, down, left, right)) {
				riskLevel = center+1;
				riskSum += riskLevel;
			}
		}
	}

	std::cout << "Sum: " << riskSum << std::endl;
	return 0;
}

bool isCenterLowest(int center, int up, int down, int left, int right) {
	int adjacents[4] = {up, down, left, right};

	for (int i = 0; i < 4; i++) {
		if (adjacents[i] == invalid) {
			continue;
		} else if (center >= adjacents[i]) {
			return false;
		}
	}

	return true;
}
