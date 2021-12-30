#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void placeQueen(int** B, int n, int i, int j)
{
	B[i][j] = 1;
	B[i][0] = j;

	for (int k = (i + 1); k < (n + 1); ++k) {
		B[k][j] -= 1;
	}
	
	for (int k = 1; (i + k) <= n; ++k) {
		if ((j - k) > 0) {
			B[i+k][j-k] -= 1;
		}
		if ((j + k) <= n) {
			B[i+k][j+k] -= 1;
		}
	}
}


void removeQueen(int** B, int n, int i, int j)
{
	B[i][j] = 0;
	B[i][0] = 0;

	for (int k = (i + 1); k < (n + 1); ++k) {
		B[k][j] += 1;
	}

	for (int k = 1; (i + k) <= n; ++k) {
		if ((j - k) > 0) {
			B[i+k][j-k] += 1;
		}
		if ((j + k) <= n) {
			B[i+k][j+k] += 1;
		}
	}
}


void printBoard(int** B, int n)
{
	printf("(");
	
	for (int i = 0; i < n; ++i) {
		int qLoc = B[i][0];

		if (i == (n - 1)) {
			printf("%d)\n", qLoc);
		}
		else {
			printf("%d, ", qLoc);
		}
	}
}


int findSolutions(int **B, int n, int i, char* mode)
{
	int accSum = 0;

	if (i > n) {
		if (strcmp(mode, "-v") == 0) {
			printBoard(B, n);
		}
		return 1;
	}
	else {
		for (int j = 1; j < (n + 1); ++j) {
			if (B[i][j] == 0) {
				placeQueen(B, n, i, j);
				accSum += findSolutions(B, n, i + 1, mode);
				removeQueen(B, n, i, j);
			}
		}
	}

	return accSum;
}


void usage()
{
	printf("Usage: Queens [-v] number\n");
	printf("Option: -v verbose output, print all solutions\n");
}


void main(int argc, char** argv)
{
	int n;
	float nf;
	int **B;
	int numSol;
	char mode[20];

	if ((argc == 2) || (argc == 3)) {
		strcpy(mode, "");
		if (argc == 3) {
			strcpy(mode, "-v");
			if (strcmp(argv[1], "-v") != 0) {
				usage();
				exit(1);
			}
		}
                if (sscanf(argv[argc-1], "%d", &n) == 0) {
			usage();
			exit(1);
		}
                sscanf(argv[argc-1], "%f", &nf);

		if (n != nf) {
			usage();
			exit(1);
		}
	}
	else {
		usage();
		exit(1);
	}

	B = (int **) malloc((n+1) * sizeof(int *));
	for (int i = 0; i < n+1; ++i) {
		B[i] = (int *) malloc((n+1) * sizeof(int));
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < (n + 1); ++j) {
			B[i][j] = 0;
		}
	}

	numSol = findSolutions(B, n, 1, mode);
	printf("%d-Queens has %d solutions\n", n, numSol);

	for (int i = 0; i < n+1; i++) {
		free(B[i]);
	}
	free(B);
}

