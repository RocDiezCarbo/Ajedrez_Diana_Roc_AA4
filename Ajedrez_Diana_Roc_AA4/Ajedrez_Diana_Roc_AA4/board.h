#pragma once

#include "constants.h"
#include <iostream>

// Board class encapsulates the internal 8x8 grid and all operations
// related to initializing and printing the chessboard.
class Board {
public:
    // Constructor: automatically initializes the board
    // with standard chess starting positions.
    Board();

    // Clears the board and fills all squares with emptySpace.
    void clear();

    // Initializes pawns on their default ranks.
    void initializePawns();

    // Initializes the non-pawn pieces (rooks, knights, bishops, queen, king).
    void initializePieces();

    // Initializes the full board: empty, pieces, and pawns.
    void init();

    // Prints the current board state to stdout with numeric indices.
    void print() const;

    // Accessor: returns the piece at (row, col).
    // Precondition: 0 <= row, col < BOARD_SIZE.
    char getPiece(int row, int col) const;

    // Mutator: sets the piece at (row, col) to 'piece'.
    // Precondition: 0 <= row, col < BOARD_SIZE.
    void setPiece(int row, int col, char piece);

private:
    // Internal 2D array representing the board.
    // The first index is the row (y), the second is the column (x).
    char squares[BOARD_SIZE][BOARD_SIZE];

    // Helper to print board indices and content.
    void printWithIndex() const;
};
