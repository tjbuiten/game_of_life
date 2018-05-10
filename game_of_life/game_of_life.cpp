// Includes
#include <stdlib.h>
#include <time.h>

// Function declaration
int countNeighboursTop(int* grid, const int* cells, int* x);
int countNeighboursMiddle(int* grid, const int* cells, int x, int* y);
int countNeighboursBottom(int* grid, const int* cells, int x);
int rules(int* grid, const int* cells, int neighbours, int x, int y);

// Start of the functional code
int main()
{
	// Variables
	const int cells = 500;
	int grid[cells][cells];
	int updatedRow[cells];
	int cellsQueue[2];
	int neighbours = 0;

	// Initiate the cells
	srand(time(NULL));
	for (int y = 0; y < cells; y++) {
		updatedRow[y] = 0;
		for (int x = 0; x < cells; x++)
			grid[x][y] = rand() % 2;
	}

	// The 'core' program
	while (true) {
		// CALCULATE THE VALUES FOR THE NEXT ITERATION
		// Calculate the first horizontal row
		for (int x = 0; x < cells; x++) {
			updatedRow[x] = rules((int*)grid, &cells, countNeighboursTop((int*)grid, &cells, &x), x, 0);
		}

		// Calculate the middle horizontal rows
		for (int y = 1; y < cells - 1; y++) {

			// Calculate the first two vertical cells
			cellsQueue[1] = rules((int*)grid, &cells, countNeighboursMiddle((int*)grid, &cells, 0, &y),
				0, y);
			cellsQueue[0] = rules((int*)grid, &cells, countNeighboursMiddle((int*)grid, &cells, 1, &y), 1, y);

			// Calculate the remaining vertical cells
			for (int x = 2; x < cells - 1; x++) {
				grid[x - 2][y - 1] = updatedRow[x - 2];
				updatedRow[x - 2] = cellsQueue[1];
				cellsQueue[1] = cellsQueue[0];
				cellsQueue[0] = rules((int*)grid, &cells, countNeighboursMiddle((int*)grid, &cells, x, &y), x, y);
			}

			// Flush the last values
			grid[cells - 2][y - 1] = updatedRow[cells - 2];
			grid[cells - 1][y - 1] = updatedRow[cells - 1];
			updatedRow[cells - 2] = cellsQueue[1];
			updatedRow[cells - 1] = cellsQueue[0];
		}

		// Calculate the last horizontal row
		// Calculate the first two cells
		cellsQueue[1] = rules((int*)grid, &cells, countNeighboursBottom((int*)grid, &cells, 0),
			0, cells - 1);
		cellsQueue[0] = rules((int*)grid, &cells, countNeighboursBottom((int*)grid, &cells, 1), 1, cells - 1);

		// Calculate the other cells
		for (int x = 2; x < cells; x++) {
			grid[x - 2][cells - 1] = cellsQueue[1];
			cellsQueue[1] = cellsQueue[0];
			cellsQueue[0] = rules((int*)grid, &cells, countNeighboursBottom((int*)grid, &cells, x), x, cells - 1);
		}

		// Flush the last values
		grid[cells - 2][cells - 1] = cellsQueue[1];
		grid[cells - 1][cells - 1] = cellsQueue[0];
	}

	// End of the program
	return 0;
}

// Count neighbours for the top row
int countNeighboursTop(int* grid, const int* cells, int* x) {
	int neighbours = 0;

	// Left corner
	if (x == 0) {
		neighbours += *(grid + (*cells - 1) * *cells + (*cells - 1)) + *(grid + (*cells - 1) * *cells) + *(grid + (*cells - 1) * *cells + (*x + 1));
		neighbours += *(grid + (*cells - 1)) + *(grid + (*x + 1));
		neighbours += *(grid + 1 * *cells + (*cells - 1)) + *(grid + 1 * *cells) + *(grid + 1 * *cells + (*x + 1));
	}

	// Right corner
	else if (*x == *cells - 1) {
		neighbours += *(grid + (*cells - 1) * *cells + (*x - 1)) + *(grid + (*cells - 1) * *cells + *x) + *(grid + (*cells - 1) * *cells);
		neighbours += *(grid + (*x - 1)) + *grid;
		neighbours += *(grid + *cells + (*x - 1)) + *(grid + *cells + *x) + *(grid + *cells);
	}

	// Middle
	else {
		neighbours += *(grid + (*cells - 1) * *cells + (*x - 1)) + *(grid + (*cells - 1) * *cells + (*x)) + *(grid + (*cells - 1) * *cells + (*x + 1));
		neighbours += *(grid + (*x - 1)) + *(grid + (*x + 1));
		neighbours += *(grid + *cells + (*x - 1)) + *(grid + *cells + *x) + *(grid + *cells + (*x + 1));
	}

	return neighbours;
}

// Count neighbours for the middle rows
int countNeighboursMiddle(int* grid, const int* cells, int x, int* y) {
	int neighbours = 0;

	// Left side
	if (x == 0) {
		neighbours += *(grid + (*y - 1) * *cells + (*cells - 1)) + *(grid + (*y - 1) * *cells + x) + *(grid + (*y - 1) * *cells + (x + 1));
		neighbours += *(grid + *y * *cells + (*cells - 1)) + *(grid + *y * *cells + (x + 1));
		neighbours += *(grid + (*y + 1) * *cells + (*cells - 1)) + *(grid + (*y + 1) * *cells + x) + *(grid + (*y + 1) * *cells + (x + 1));
	}

	// Right side
	if (x == *cells - 1) {
		neighbours += *(grid + (*y - 1) * *cells + (x - 1)) + *(grid + (*y - 1) * *cells + x) + *(grid + (*y - 1) * *cells);
		neighbours += *(grid + *y * *cells + (x - 1)) + *(grid + *y * *cells + (x + 1));
		neighbours += *(grid + (*y + 1) * *cells + (x - 1)) + *(grid + (*y + 1) * *cells + x) + *(grid + (*y + 1) * *cells + (x + 1));
	}

	// Middle
	else {
		neighbours += *(grid + (*y + 1) * *cells + (x - 1)) + *(grid + (*y + 1) * *cells + x) + *(grid + (*y + 1) * *cells + (x + 1));
		neighbours += *(grid + *y * *cells + (x - 1)) + *(grid + *y * *cells + (x + 1));
		neighbours += *(grid + (*y - 1) * *cells + (x - 1)) + *(grid + (*y - 1) * *cells + x) + *(grid + (*y - 1) * *cells + (x + 1));
	}

	return neighbours;
}

// Count neighbours for the bottom row
int countNeighboursBottom(int* grid, const int* cells, int x) {
	int neighbours = 0;

	// Left corner
	if (x == 0) {
		neighbours += *(grid + (*cells - 2) * *cells + (*cells - 1)) + *(grid + (*cells - 2) * *cells + x) + *(grid + (*cells - 2) * *cells + (x + 1));
		neighbours += *(grid + (*cells - 1) * *cells + (*cells - 1)) + *(grid + (*cells - 1) * *cells + (x + 1));
		neighbours += *(grid + (*cells - 1)) + *(grid + x) + *(grid + (x + 1));
	}

	// Right corner
	else if (x == *cells - 1) {
		neighbours += *(grid + (*cells - 2) * *cells + (x - 1)) + *(grid + (*cells - 2) * *cells + x) + *(grid + (*cells - 2) * *cells);
		neighbours += *(grid + (*cells - 1) * *cells + (x - 1)) + *(grid + (*cells - 1) * *cells);
		neighbours += *(grid + (x - 1)) + *(grid + x) + *grid;
	}

	// Middle
	else {
		neighbours += *(grid + (*cells - 2) * *cells + (x - 1)) + *(grid + (*cells - 2) * *cells + x) + *(grid + (*cells - 2) * *cells + (x + 1));
		neighbours += *(grid + (*cells - 1) * *cells + (x - 1)) + *(grid + (*cells - 1) * *cells + (x + 1));
		neighbours += *(grid + (x - 1)) + *(grid + x) + *(grid + (x + 1));
	}

	return neighbours;
}

// Combine the neighbours with the rules of GOL to return the new value of the cell
int rules(int* grid, const int* cells, int neighbours, int x, int y) {
	if (neighbours < 2)
		return 0;
	if (neighbours > 3)
		return 0;
	if (*(grid + y * *cells + x) == 0 && neighbours == 3)
		return 1;
	return *(grid + y * *cells + x);
};