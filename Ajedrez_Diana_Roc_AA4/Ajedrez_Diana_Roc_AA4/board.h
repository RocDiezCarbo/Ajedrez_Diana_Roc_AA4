#pragma once

#include "constants.h"

// Clears the board by filling all squares with emptySpace.
void clearBoard();

// Places white and black pawns on their default ranks.
void initializePawns();

// Places rooks, knights, bishops, queen, and king on starting squares.
void initializePieces();

// Initializes the full board to the standard starting position.
void initBoard();

// Prints the board with indices (rows and columns).
void printBoard();

// Returns the piece at the given row and column.
char getPiece(int row, int col);

// Sets the piece at the given row and column.
void setPiece(int row, int col, char piece);
