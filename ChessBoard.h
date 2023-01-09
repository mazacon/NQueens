/**
* Maz
* ChessBoard.h
**/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>

class ChessBoard
{
private:
	// points to 2D char array on heap; the chess board
	char**	boardPtr;

	// the amount of squares on any side of the board
	int		boardSize;

	/**
	* Recursive function which tries placing queens on board
	* starting from index provided; backtracks in dead ends
	*
	* @param	row:		the row number to place queen
	* @param	column:		the column number to place queen
	* @return	true if all queens placed successfully, else false
	* @pre		provided index must be valid
	**/
	bool	placeQueens(int row, int column);

	// creates board and fill with *'s
	void	initBoard();

	// delete chess board off heap
	void	deleteBoard();

	/**
	* searches the given column for the next unattacked square
	* starting at the given row and moving down the column
	*
	* @param	row:		the row number to start searching from
	* @param	column:		the column number to start searching from
	* @return	row number of unattacked square; -1 if none exist
	* @pre		provided index must be valid
	**/
	int		nextClearSquare(int row, int column);

public:
	ChessBoard();
	ChessBoard(int boardSize);
	~ChessBoard();

	void	setSize(int boardSize);
	int		getSize();

	/**
	* tries solving the board beginning at index 0, 0
	* 
	* @return	true if board solved; false if impossible/failed
	**/
	bool	solve();

	// prints out contents of chess board
	void	displayBoard();
};

#endif CHESSBOARD_H