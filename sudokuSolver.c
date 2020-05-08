/*
 * Author: Karanbir Boparai
 * Sudoku Solver with recursive backtracking
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkColumn(int columnNum, int cellNum, int grid[9][9]);
bool checkRow(int rowNum, int cellNum, int grid[9][9]);
bool checkSubgrid(int rowNum, int columnNum, int cellNum, int grid[9][9]);
bool isValid(int grid[9][9]);
void printSudoku(int grid[9][9]);
bool solveSudoku(int rowNum, int columnNum, int grid[][9]);

int main(void)
{
	int userInput = 0;
	bool sudokuStatus = false;
	// 2D array that holds the hardcoded sudoku grid. 0 means that the cell is empty
	int sudokuGrid[9][9] = {{0, 0, 0, 4, 6, 0, 0, 0, 0},
							{0, 8, 0, 0, 0, 3, 4, 0, 0},
							{0, 9, 0, 0, 0, 0, 0, 0, 7},
							{2, 0, 0, 0, 9, 0, 0, 1, 0},
							{1, 0, 0, 0, 0, 0, 0, 0, 3},
							{0, 6, 0, 0, 7, 0, 0, 0, 4},
							{5, 0, 0, 0, 0, 0, 0, 6, 0},
							{0, 0, 7, 9, 0, 0, 0, 8, 0},
							{0, 0, 0, 0, 5, 2, 0, 0, 0}};

	printf("\nPress 1 to solve the hardcoded sudoku.\n");
	printf("Press 2 to input a sudoku.\n");
	printf("Press any other key to quit.\n");
	scanf("%d", &userInput);

	if(userInput != 1 && userInput != 2)
	{
		printf("\nExiting...\n\n");
		return 0;
	}
	else if(userInput == 2)
	{
		int i = 0, j = 0;
		bool correctInput = false;

		printf("\nEnter the sudoku row by row and enter 0 for empty cells.\n");
		printf("Enter the numbers 1 by 1 seperated by a space.\n");
		printf("Eg: 0 6 4 0 0 2 0 5 0 and then press enter\n\n");

		for(i = 0; i < 9; i++)
		{
			while(correctInput == false)
			{
				printf("Enter Row %d: ", i + 1);
				scanf("%d %d %d %d %d %d %d %d %d", &sudokuGrid[i][0], 
					&sudokuGrid[i][1], &sudokuGrid[i][2], &sudokuGrid[i][3], 
					&sudokuGrid[i][4], &sudokuGrid[i][5], &sudokuGrid[i][6], 
					&sudokuGrid[i][7], &sudokuGrid[i][8]);
				correctInput = true;

				// Checking if user input is only between 0-9
				for(j = 0; j < 9; j++)
				{
					if((sudokuGrid[i][j] < 0) || (sudokuGrid[i][j] > 9))
					{
						correctInput = false;
					}
				}

				if(correctInput == false)
				{
					printf("Input can only be 0 to 9. Try again.\n\n");
				}
			}
			correctInput = false;
		}
	}

	printf("\nSudoku to Solve(0 means empty cell):\n");
	printSudoku(sudokuGrid);
		
	sudokuStatus = solveSudoku(0, 0, sudokuGrid);

	if(sudokuStatus == true && isValid(sudokuGrid))
	{
		printf("Solution:\n");
		printSudoku(sudokuGrid);
	}
	else
	{
		printf("***** Sudoku is not valid *****\n\n");
	}

	return 0;
}

/*
 * This function checks if number in the cell is present in it's column
 * @param: column number(0-8)
 * @param: Number to check(1-9)
 * @param: 2D array that holds the sudoku grid
 * @return: True if cellNum is present in the column and vice-versa
*/
bool checkColumn(int columnNum, int cellNum, int grid[9][9])
{
	int i = 0;

	for(i = 0; i < 9; i++)
	{
		if(grid[i][columnNum] == cellNum)
		{
			return true;
		}
	}

	return false;
}

/*
 * This function checks if number in the cell is present in it's row
 * @param: Row number(0-8)
 * @param: Number to check(1-9)
 * @return: True if cellNum is present in the row and vice-versa
*/
bool checkRow(int rowNum, int cellNum, int grid[9][9])
{
	int i = 0;

	for(i = 0; i < 9; i++)
	{
		if(grid[rowNum][i] == cellNum)
		{
			return true;
		}
	}

	return false;
}

/*
 * This function checks of number in the cell is present in it's subgrid
 * @param: Row number(0-8)
 * @param: Column number(0-8)
 * @param: Number to check(1-9)
 * @param: 2D array that holds the sudoku grid
 * @return: True if cellNum is present in the subgrid and vice-versa
*/
bool checkSubgrid(int rowNum, int columnNum, int cellNum, int grid[9][9])
{
	// These variables are for storing the row and column of the first cell in the subgrid
	// After finding these, the function checks the subgrid in left-right, top-bottom order for cellNum
	int subgridFirstCellRowNum = 0, subgridFirstCellColumnNum = 0;
	int i = 0, j = 0;

	// Finding the row number of the first cell of the subgrid
	if(rowNum < 3)
	{
		subgridFirstCellRowNum = 0;
	}
	else if(rowNum < 6)
	{
		subgridFirstCellRowNum = 3;
	}
	else
	{
		subgridFirstCellRowNum = 6;
	}

	// Finding the column number of the first cell of the subgrid
	if(columnNum < 3)
	{
		subgridFirstCellColumnNum = 0;
	}
	else if(columnNum < 6)
	{
		subgridFirstCellColumnNum = 3;
	}
	else
	{
		subgridFirstCellColumnNum = 6;
	}

	// Checking the subgrid for cellNum in left-right, top-bottom order
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			if(grid[subgridFirstCellRowNum + i][subgridFirstCellColumnNum + j] == cellNum)
			{
				return true;
			}
		}
	}

	return false;
}

/*
 * This function checks if a finished sudoku is valid
 * @param: 2D array that holds the sudoku grid
 * @return: True if the sudoko is valid and vice-versa
*/
bool isValid(int grid[9][9])
{
	// solveSudoku can fill a sudoku by following the rules and complete it but the sudoku still needs to be checked if it is valid
	// The function goes row by row and adds all the cells and finds the product which is constant if the cells have numbers 1-9

	int i = 0, j = 0, rowSum = 1, rowProduct = 0;

	for(i = 0; i < 9; i++)
	{
		rowSum = 0;
		rowProduct = 1;

		for(j = 0; j < 9; j++)
		{
			rowSum = rowSum + grid[i][j];
			rowProduct = rowProduct * grid[i][j];
		}

		if(rowSum != 45 || rowProduct != 362880)
		{
			return false;
		}
	}

	return true;
}

/*
 * This function prints the sudoku grid
 * @param: 2D array that holds the sudoku grid
*/
void printSudoku(int grid[9][9])
{
	int x = 0, y = 0;

	for(x = 0; x < 9; x++)
	{
		for(y = 0; y < 9; y++)
		{
			printf("%d", grid[x][y]);

			if(y == 2 || y == 5)
			{
				printf(" | ");
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");

		if(x == 2 || x == 5)
		{
			printf("------------------------------------");
		}

		printf("\n");
	}
}

/*
 * This function solves the sudoku by recursive backtracking
 * @param: Row number of current cell
 * @param: Column number of current cell
 * @param: Pointer to 2D array that holds the sudoku grid
 * @return: True if a solution has been found and false if there is need to backtrack
*/
bool solveSudoku(int rowNum, int columnNum, int grid[][9])
{
	/*
	 * rowNum & columnNum is for the current cell being looked at. If cell is already filled, then we skip it and move to next cell
	 * If cell is not filled, then we assume the number 1. If it violates the sudoku rules then we assume 2 and so on until 9
	 * If the assumption is valid then we move to the next cell
	 * If none of the assumptions from 1-9 hold then we backtrack and change the assumption of the last assumed cell
	 * Sudoku is solved if we reach the last cell and have a valid assumption
	 * Sudoku is not valid if we backtrack to the first cell and none of the assumptions from 1-9 hold
	*/

	int currentAssumedNum = 0;
	bool sudokuStatus = false;

	// Having 0 in the cell means the cell needs to be filled
	if(grid[rowNum][columnNum] == 0)
	{
		for(currentAssumedNum = 1; currentAssumedNum <= 9; currentAssumedNum++)
		{
			// If the current assumed number is not present in the row, column and subgrid then it is a valid assumption
			if(!checkRow(rowNum, currentAssumedNum, grid) 
				&& !checkColumn(columnNum, currentAssumedNum, grid) 
				&& !checkSubgrid(rowNum, columnNum, currentAssumedNum, grid))
			{
				// Filling the assumed number in the sudoku grid
				grid[rowNum][columnNum] = currentAssumedNum;

				// If we are looking at the last cell in the grid and we are able to assume a number there then we have sudoku solution
				if(columnNum == 8 && rowNum == 8)
				{
					return true;
				}
				// If we are looking at the last cell in a row then the next cell is in the 1'st column of the next row
				else if(columnNum == 8)
				{
					sudokuStatus = solveSudoku(rowNum + 1, 0, grid);

					if(sudokuStatus == false)
					{	
						// If sudokuStatus is false that means we are backtracking
						// So therefore the assumption for the current cell was wrong & it is made empty again
						grid[rowNum][columnNum] = 0;
					}
				}
				else
				{
					sudokuStatus = solveSudoku(rowNum, columnNum + 1, grid);

					if(sudokuStatus == false)
					{	
						grid[rowNum][columnNum] = 0;
					}
				}
			}
			else
			{
				// If the assumed number is not valid then we do nothing and assume the next number
				// But if the assumed number was 9 and it is invalid then we return false so we can backtrack
				if(currentAssumedNum == 9)
				{
					return false;
				}
			}

			if(sudokuStatus == true)
			{
				// If sudokuStatus is true then solution has been found and we can break loop so we don't keep assuming numbers
				break;
			}
		}
	}	
	// If cellNum != 0 that means cell is already filled and we can go to next cell
	else
	{
		// If we are looking at the last cell in the sudoku and we are able to assume a number there then we have sudoku solution
		if(columnNum == 8 && rowNum == 8)
		{
			return true;
		}
		// If we are looking at the last cell in a row then the next cell is in the 1'st column of the next row
		else if(columnNum == 8)
		{
			sudokuStatus = solveSudoku(rowNum + 1, 0, grid);
		}
		else
		{
			sudokuStatus = solveSudoku(rowNum, columnNum + 1, grid);
		}
	}

	return sudokuStatus;
}
