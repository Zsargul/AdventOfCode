#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

// Macros for brevity in some function calls/declarations
#define SCANNED_VECTOR  std::vector< std::vector<int> > &scanned 
#define LAVAMAP 	std::vector< std::vector<int> > &lavaMap

const int invalid = -1; // Assigned to an adjacent position when said position does not exist
const int alreadyScanned = 1; // For marking scanned coordinates

bool isCenterLowest(int center, int up, int down, int left, int right);
void markScanned(SCANNED_VECTOR, int y, int x);
int isScanned(SCANNED_VECTOR, int y, int x);
int scan(const int vert_length, const int horiz_length, SCANNED_VECTOR, LAVAMAP, int y, int x);
int coordExists(const int vert_length, const int horiz_length, int y, int x);

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

	// std::cout << "Sum: " << riskSum << std::endl;

	// Vector to hold already scanned coordinates. 
	// -1 >> Not yet scanned
	// 1 >> Scanned
	std::vector< std::vector<int> > scanned(vert_length, std::vector<int>(horiz_length, -1));
	
	// Vector for holding basin sizes
	std::vector<int> basins;

	// Scan every basin and it's size
	for(int y = 0; y < vert_length; y++) {
		for(int x = 0; x < horiz_length; x++) {
			int basinSize = scan(vert_length, horiz_length, scanned, lavaMap, y, x);
			if (basinSize == 0) {
				continue;
			} else {
				basins.push_back(basinSize);
			}
		}
	}

	// Find 3 largest basins
	int topThree[3] = {0};
	for (int i = 0; i < basins.size(); i++) {
		int size = basins[i];
		if (size > topThree[0]) {
			topThree[2] = topThree[1];
			topThree[1] = topThree[0];
			topThree[0] = size;
		} else if (size > topThree[1]) {
			topThree[2] = topThree[1];
			topThree[1] = size;
		} else if (size > topThree[2]) {
			topThree[2] = size;
		}
	}

	int product = 1;
	for (int i = 0; i < 3; i++) {
		product *= topThree[i];
	}
	std::cout << product << std::endl;

	return 0;
}


// Remember to pass in scanned vector by reference in all scan-related functions
int scan(const int vert_length, const int horiz_length, SCANNED_VECTOR, LAVAMAP, int y, int x) {
	// Check if coordinate exists
	if (!coordExists(vert_length, horiz_length, y, x)) {	
		return 0;
	} else if (isScanned(scanned, y, x) || lavaMap[y][x] == 9) {
		return 0; // Coordinate is already scanned, is equal to 9
	}

	int scanReturn = 1;
	markScanned(scanned, y, x);
	
	scanReturn += scan(vert_length, horiz_length, scanned, lavaMap, y-1, x); // Up
	scanReturn += scan(vert_length, horiz_length, scanned, lavaMap, y, x+1); // Right
	scanReturn += scan(vert_length, horiz_length, scanned, lavaMap, y+1, x); // Down
	scanReturn += scan(vert_length, horiz_length, scanned, lavaMap, y, x-1); // :eft
	return scanReturn;
}

int coordExists(const int vert_length, const int horiz_length, int y, int x) {
	if (y < 0 || y >= vert_length || x < 0 || x >= horiz_length) {
		return 0; // Doesn't exist
	} else {
		return 1; // Exists
	}
}

int isScanned(SCANNED_VECTOR, int y, int x) {
	if (scanned[y][x] == 1)
		return 1;
	else
		return 0;
}

void markScanned(SCANNED_VECTOR, int y, int x) {
	scanned[y][x] = alreadyScanned;
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
