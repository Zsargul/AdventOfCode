#include <stdio.h>

#define INLENGTH 2000

// Function for checking if the next measurement is an
// increase or decrease
int increasechq(int curr, int next) { 
	if (curr < next) {
		return 1;
	} else {
		return 0;
	}
}

int main() {
	// Scanning puzzle input
	FILE *input = fopen("input.txt", "r");
	int i=0;
	int j;

	int larger_count = 0;

	int depths[INLENGTH];
	int depth;

	while(fscanf(input, "%d", &depth) != EOF) {
		depths[i] = depth;
		i++;
	}

	fclose(input);

	// Iterating measurements and checking for increase/decrease
	j=1;	
	for (i=0;i<INLENGTH;i++) {
		if(j>=INLENGTH) {
			break;
		}

		if (increasechq(depths[i], depths[j])) {
			larger_count++;
		}
		j++;
	}
	
	printf("Measurements larger than previous measurement: %d\n", larger_count);

	return 0;
	
}
