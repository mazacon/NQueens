/**
* Maz
* ChessBoard.cpp
**/

#include "ChessBoard.h"

// PRIVATE METHODS
bool ChessBoard::placeQueens(int row, int column)
{
	if (column >= boardSize)
	{	// The board is filled, problem is solved.
		return true;
	} // end if
	else
	{
		// while unconsidered rows exist in column 
		while (row < boardSize)
		{
			/* Starting with row, find the next square in column
			that is not under attack by a queen placed in any
			previous column. */

			// assigns targetRow the next usable row given [row][column]
			int targetRow = nextClearSquare(row, column);
			
			if (targetRow != -1)// if an unattacked square exists in column
			{
				/* Place a queen in the un-attacked square.
				Do a recursive call to try and place queens
				in subsequent columns : */

				boardPtr[targetRow][column] = 'Q';

				if (!placeQueens(0, column + 1))
				{
					/* Placement of the last queen resulted in
					a dead end; no solution could be found.
					Remove the last queen placed.
					Increment row so search can continue in
					next iteration. */

					boardPtr[targetRow][column] = '*';
					row++;
				} // end if
				else
				{
					/* Queens were successfully placed in all
					columns to the right of column, the
					problem is solved. */

					return true;
				} // end else
			} // end if
			else
			{
				/* No un - attacked square found for a queen in
				column.Backtrack: */
				return false;
			} // end else
		} // end while

		/* All rows have been considered in column without a
		successful queen placement. Backtrack: */

		return false;
	} // end else
} // end placeQueens()

void ChessBoard::initBoard()
{
	// make rows
	boardPtr = new char* [boardSize];

	// make columns
	for (int i = 0; i != boardSize; i++)
		boardPtr[i] = new char[boardSize];
	
	// fill every possible index with '*'
	for (int i = 0; i != boardSize; i++)
	{
		for (int j = 0; j != boardSize; j++)
		{
			boardPtr[i][j] = '*';
		}
	}
}

void ChessBoard::deleteBoard()
{
	// delete all columns 
	for (int i = 0; i != boardSize; i++)
		delete[] boardPtr[i];

	// delete all rows
	delete[] boardPtr;
}

int ChessBoard::nextClearSquare(int row, int column)
{
	int index = -1, i, j;
	bool safe;

	while (row < boardSize)
	{
		safe = true;

		// Check west for queens
		for (i = 0; i < column; i++)
			if (boardPtr[row][i] == 'Q') safe = false;

		// Check northwest for queens
		for (i = row, j = column; i >= 0 && j >= 0; i--, j--)
			if (boardPtr[i][j] == 'Q') safe = false;

		// Check southwest for queens
		for (i = row, j = column; j >= 0 && i < boardSize; i++, j--)
			if (boardPtr[i][j] == 'Q') safe = false;

		if (safe) 
		{	// if safe, return value = row number of good square 
			index = row;
			break;
		}
		row++;
	}
	// returns -1 if no good square found in column
	return index;
}

// CONSTRUCTORS/DESCTRUCTORS
ChessBoard::ChessBoard() : boardSize(8)
{
	// create board and fill with *'s
	initBoard();
}

ChessBoard::ChessBoard(int boardSize) : boardSize(boardSize)
{
	// create board and fill with *'s
	initBoard();
}

ChessBoard::~ChessBoard()
{
	// remove board from heap
	deleteBoard();
}

// PUBLIC METHODS
void ChessBoard::setSize(int boardSize)
{
	// clear any existing board off heap
	deleteBoard();

	// set given board size; max 12 min 4
	if (boardSize < 4) this->boardSize = 4;
	else if (boardSize > 12) this->boardSize = 12;
	else this->boardSize = boardSize;

	// create board on heap with newly set size
	initBoard();
}

int ChessBoard::getSize()
{
	return boardSize;
}

bool ChessBoard::solve()
{
	// starts off the recursive placeQueens() from index 0, 0
	return placeQueens(0, 0);
}

void ChessBoard::displayBoard()
{
	// for every row
	for (int row = 0; row != boardSize; row++)
	{
		// for every column in row
		for (int col = 0; col != boardSize; col++)
		{	
			// display data plus space
			std::cout << boardPtr[row][col] << ' ';
		}
		std::cout << std::endl; // newline after every row 
	}
}
