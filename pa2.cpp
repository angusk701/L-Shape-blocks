/*

  The following program solves the L-shape blocks problem

   Given
	  A 2^N x 2^N array (In this assignment, we restrict the value N as 1, 2 and 3 )
	   The location of the empty cell (x,y)
		  The legal (x,y) coordinates of the empty cell:

			  For a 2 x 2 block, the legal range is 0-1
			  For a 4 x 4 block, the legal range is 0-3
			  For a 8 x 8 block, the legal range is 0-7
	   You can assume all the input values are correct

	Output:

	  The empty cell (x,y) remains empty
	  All other cells are filled by non-overlapping L-shape blocks

	Output mode:
	  (0) Console output without normalization
	  (1) Console output with normalization

	   Author: Peter, Brian, Tommy
*/

#include <iostream>
using namespace std;

// Constants in global scope
const int MAX_WIDTH = 8;
const int LOCATEQUADRANT_NOT_IMPLEMENTED = 0;

// TODO:
// function locateQuadrant:
// @param x:  x coordinate of the empty cell
// @param y:  y coordinate of the empty cell
//
// If x < half width, y < half width, then return 1
// If x >= half width, y < half width, then return 2
// If x >= half width, y >= half width, then return 3
// If x < half width, y >= half width, then return 4
//
// @return: int
// The function returns after getting valid values for width, emptyXPos and emptyYPos
int locateQuadrant(int width, int x, int y)
{

	if (x < width/2 && y < width/2) return 1;
	else if (x >= width/2 && y < width/2) return 2;
	else if (x >= width/2 && y >= width/2) return 3;
	//if (x < width/2 && y >= width/2) 
	else return 4;
		
}

/**
	Given the puzzleMap (2D array from the recursive function),
	Generate the console output
 */
void visualizePuzzleByText(int width, char puzzleMap[][MAX_WIDTH])
{

	cout << "  ";
	for (int x = 0; x < width; x++)
		cout << x << " ";
	cout << endl;

	for (int y = 0; y < width; y++)
	{
		cout << y << ":";
		for (int x = 0; x < width; x++)
			cout << puzzleMap[x][y] << " ";
		cout << endl;
	}
}

/**
 * Initialize the whole puzzleMap using by a space character: ' '
 */
void initializePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < width; y++)
			puzzleMap[x][y] = ' ';
}

// TODO:
// Normalize the whole puzzleMap. The space character ' ' will not be changed.
//
void normalizePuzzleMap(int width, char puzzleMap[][MAX_WIDTH])
{
	char initial_char = 'A';
	char rightChar = 'A';
	int diff = 0;
	int count = 0;
	char new_array[MAX_WIDTH][MAX_WIDTH];
	initializePuzzleMap(width, new_array);
	for (int recur = 0; recur < (width*width/3); recur++){
	
	for (int j = 0; j< width; j++){
		for (int i = 0; i< width; i++){
			if ((puzzleMap[i][j] != ' ') && (new_array[i][j] == ' '))
			{
				initial_char = puzzleMap[i][j];
				count += 1;
				break;
			}
		}
		if (count == 1) break;
	}


	if (initial_char != rightChar){
		diff = initial_char - rightChar;
	}
	for (int y = 0; y< width; y++){
		for (int x = 0; x< width; x++){
			if ((new_array[x][y] == ' ') && (puzzleMap[x][y] == initial_char)) {
				new_array[x][y] = initial_char;
			}
		}


	for (int i = 0; i< width; i++){
		for (int j = 0; j< width; j++){
			if (new_array[i][j] == initial_char){

			if (puzzleMap[i][j] == ' '){
				continue;
			}

			
			else if (puzzleMap[i][j] - diff < rightChar){
				puzzleMap[i][j] = rightChar;
			}
			
			
			else if (diff < 0){
				diff = -diff;
				puzzleMap[i][j] += diff;
			}
			

			else{
				puzzleMap[i][j] = puzzleMap[i][j] - diff;
			}
			}

		}
	}


	}
	//visualizePuzzleByText(width, new_array);
	
	rightChar += 1;
	count = 0;
	}


	return;
}

// TODO:
// [The most important function in this program]
// The recursive function to fill up the character array: puzzleMap
// You need to figure out the parameters of the fillPuzzleRecursive function by yourself
//

//fillPuzzleRecursive(width, puzzleMap, 0, 0, emptyXPos, emptyYPos, nextChar);
void fillPuzzleRecursive(int width, char puzzleMap[][MAX_WIDTH], int tx,
						 int ty, int x, int y,char nextChar)
{
	// tx: top Left X coordinate
	// ty: top Left Y coordinate
	// x:  x coordinate of the empty cell
	// y:  y coordinate of the empty cell
	if (width == 2)
	{
		// The base case...
		//return;
		for (int j= ty; j< width + ty; j++){
			for (int i= tx; i< width + tx; i++){
				if ( i != x || j != y) 
				{
					puzzleMap[i][j] = nextChar;
				}
			}
		}
	}

	// The general case
	//
	// Key idea:
	//  Because qual must be equal to either 1, 2, 3 or 4
	// As a result:
	//    A L-shape MUST be created at the center of the bigger rectangle
	//    Each Quad MUST have exactly 1 empty space

	if (width == 4){
		int temp_x = x - tx;
		int temp_y = y - ty;
		int quad = locateQuadrant(width, temp_x,temp_y);
		if (quad == 1){
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2-1, ty +width/2-1, tx+ width/2-1, ty+ width/2-1,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty, x,y,nextChar+1);
			fillPuzzleRecursive(width/2, puzzleMap,tx +width/2, ty, tx+width/2,ty+1,nextChar+2);
			//tx = 0;
			//ty = width/2;
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty+width/2, tx + 1,ty+width/2,nextChar+3);
			//tx = width/2;
			//ty = width/2;		
			fillPuzzleRecursive(width/2, puzzleMap,tx +width/2, ty+width/2, tx+width/2,ty+width/2,nextChar+4);
		}

		else if (quad == 2){
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2-1, ty + width/2-1, tx +width/2, ty +width/2-1,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty, tx+ width/2 -1 ,ty+ width/2 -1,nextChar+1);
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty+width/2, tx+width/2 -1,ty + width/2,nextChar+2);
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2, ty, x,y,nextChar+3);
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2, ty + width/2, tx+width/2, ty+width/2,nextChar+4);
		}
		else if (quad == 3){
			fillPuzzleRecursive(width/2, puzzleMap, tx +width/2-1, ty+ width/2-1, tx +width/2, ty +width/2,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty, tx + width/2-1,ty + width/2 -1,nextChar+1);
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty +width/2, tx + width/2 -1,ty + width/2,nextChar+2);
			fillPuzzleRecursive(width/2, puzzleMap, tx + width/2, ty, tx+width/2,ty + width/2 -1,nextChar+3);
			fillPuzzleRecursive(width/2, puzzleMap,tx+width/2, ty+ width/2, x,y,nextChar+4);
		}
		else{
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2-1, ty +width/2 -1, tx + width/2-1, ty+ width/2,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty, tx + width/2 -1, ty + width/2 -1,nextChar+1);
			fillPuzzleRecursive(width/2, puzzleMap,tx, ty + width/2, x,y,nextChar+2);
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2, ty, tx + width/2, ty+width/2 -1,nextChar+3);
			fillPuzzleRecursive(width/2, puzzleMap,tx + width/2, ty + width/2, tx + width/2, ty+width/2,nextChar+4);
		}
	}

	if (width == 8){
		int quad = locateQuadrant(width, x,y);
		if (quad == 1){
			fillPuzzleRecursive(width/4, puzzleMap,3, 3, 3,3,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,0, 0, x,y,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 0, 4,3,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,0, 4, 3,4,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 4, 4,4,nextChar+1);

		}

		else if (quad == 2){
			fillPuzzleRecursive(width/4, puzzleMap,3, 3, 4,3,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,0, 0, 3,3,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 0, x,y,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,0, 4, 3,4,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 4, 4,4,nextChar+1);
		}
		else if (quad == 3){
			fillPuzzleRecursive(width/4, puzzleMap,3, 3, 4,4,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,0, 0, 3,3,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 0, 4,3,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,0, 4, 3,4,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 4, x,y,nextChar+1);
		}
		else{
			fillPuzzleRecursive(width/4, puzzleMap,3, 3, 3,4,nextChar );
			fillPuzzleRecursive(width/2, puzzleMap,0, 0, 3,3,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,0, 4, x,y,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 0, 4,3,nextChar+1);
			nextChar += 5;
			fillPuzzleRecursive(width/2, puzzleMap,4, 4, 4,4,nextChar+1);
		}

	}

	return;
}

// TODO:
// function checkInput:
//
// @param width: the width of the square. Valid values: 2, 4, 8
// You can assume inputs are always integers.
// @param emptyXPos: the x-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
// @param emptyYPos: the y-axis of the empty position.
// Valid range: [0, width-1].
// You can assume inputs are always integers.
//
//  Note: The pass-by-reference variables will be used in the main function.
// @return: void
// The function returns after getting valid values for width, emptyXPos and emptyYPos
void checkInput(int &width, int &emptyXPos, int &emptyYPos)
{
	// Some helper lines for you to use:

	do {
		cout << "Enter the width/height of the puzzle (2, 4, 8): ";
		cin >> width;
		cout << endl;

	} while ((width != 2 && width != 4 && width != 8));

	do {
		cout << "Enter the x-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyXPos;
		cout << endl;

	} while (emptyXPos < 0 || emptyXPos > width-1);


	do {
		cout << "Enter the y-coordinate of the empty cell (0-" << width - 1 << "): ";
		cin >> emptyYPos;
		cout << endl;

		} while (emptyYPos < 0 || emptyYPos > width-1);

	return;
}

// You are NOT ALLOWED to modify the main function
int main()
{

	int width = 0;
	int emptyXPos = 0;
	int emptyYPos = 0;

	checkInput(width, emptyXPos, emptyYPos);

	// initialized with empty spaces..
	char puzzleMap[MAX_WIDTH][MAX_WIDTH];

	// initialize
	initializePuzzleMap(width, puzzleMap);

	int modeOfOperation = 0;
	do
	{
		cout
			<< "0: Exit directly (for testing checkInput function), 1: Output Quadrant of the empty cell,"
			<< endl
			<< "2: Output without normalization (for student's debug only), 3: Output with normalization"
			<< endl;
		cout << "Enter the output mode: ";
		cin >> modeOfOperation;
		cout << endl;
	} while (modeOfOperation < 0 || modeOfOperation > 3);

	if (modeOfOperation == 0)
	{
		return 0;
	}
	if (modeOfOperation == 1)
	{
		int quad = locateQuadrant(width, emptyXPos, emptyYPos);
		cout << "Quadrant for the empty cell: " << quad << endl;
		return 0;
	}
	char nextChar = 'A';

	// invoke the recursive call here...
	// Result: puzzleMap will be filled by characters
	fillPuzzleRecursive(width, puzzleMap, 0, 0, emptyXPos, emptyYPos, nextChar);

	int quad = locateQuadrant(width, emptyXPos, emptyYPos);
	cout << "Quadrant for the empty cell: " << quad << endl;
	if (modeOfOperation == 2)
	{
		visualizePuzzleByText(width, puzzleMap);
	}
	else
	{
		normalizePuzzleMap(width, puzzleMap);
		visualizePuzzleByText(width, puzzleMap);
	}
	return 0;
}
