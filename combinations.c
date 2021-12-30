#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

/* This function prints a particular set of size k.
 * All elements in array B, that have the bit field set to 1
 * are printed. Others are ignored
 */
void printSet(int B[], int n) {
	int i;
	int addCommaFlag = 0;

	printf("{");
	for (i = 1; i <= n; i++) {
		if (B[i] == 1) {
			if (addCommaFlag == 0) {
				printf("%d", i);
				addCommaFlag = 1;
			}
			else {
				printf(", %d", i);
			}
		}
	}
	printf("}\n");
}

/* This function generates the combinations for given values of n and k.
 * It uses the provided recursive algorithm.
 */
void printSubsets(int B[], int n, int k, int i) {
	if (k > n - i + 1) {
		return;
	}

	if (k == 0) {
		printSet(B, n);
		return;
	}

	B[i] = 1;
	printSubsets(B, n, k-1, i+1);
	B[i] = 0;
	printSubsets(B, n, k, i+1);
}

void usageError(char *progName) {
	printf("Usage: %s n k (n and k are ints satisfying 0<=k<=n<=100)\n", progName);
}

int main(int argc, char *argv[]) {
	int B[MAX_SIZE + 1];
	int i;
	int n, k;
	float nf, kf;
	int inputErrorFlag = 0;

	/* Initialize B to all 0s */
	for (i = 0; i < MAX_SIZE+1; i++) {
		B[i] = 0;
	}

	/* The program takes exactly three inputs */
	if (argc != 3) {
		usageError(argv[0]);
		inputErrorFlag = 1;
		exit(1);
	}

	/* The second and third inputs should be integers */
	n = atoi(argv[1]);
	k = atoi(argv[2]);

	nf = atof(argv[1]);
	kf = atof(argv[2]);

	/* Ensure that the inputs meet the requirements */
	if (n == 0 || k == 0 || n > 100 || k > n || n != nf || k != kf) {
		usageError(argv[0]);
		inputErrorFlag = 1;
	}

	if (inputErrorFlag == 0) {
		printSubsets(B, n, k, 1);
	}
}
