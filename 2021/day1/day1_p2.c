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
	int windows[INLENGTH];
	int windows_c=0;

	int larger_count = 0;

	int depths[INLENGTH];
	int depth;

	while(fscanf(input, "%d", &depth) != EOF) {
		depths[i] = depth;
		i++;
	}

	fclose(input);

	// Creating a new array with sliding windows
	for(i=0; i<INLENGTH-2; i++) {
		windows[i] = (depths[i] + depths[i+1] + depths[i+2]);	
		windows_c++;
	}

	// Iterating windows and checking for increase/decrease
	j=1;	
	for (i=0;i<INLENGTH;i++) {
		if(j>=INLENGTH) {
			break;
		}

		if (increasechq(windows[i], windows[j])) {
			larger_count++;
		}
		j++;
	}
	
	printf("Windows larger than previous window: %d\n", larger_count);

	return 0;
	
}
