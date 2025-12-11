#include "board.h"
#include "constants.h"
#include <iostream>

// Helper function to print coordinates and the internal board.
// This function has internal linkage (only visible in this file).
static void printBoardWithIndex() {
    // Print column indices (1..BOARD_SIZE)
    std::cout << "  ";
    for (int col = 0; col < BOARD_SIZE; ++col) {
        std::cout << (col + 1) << ' ';
    }
    std::cout << '\n';

    // Print each row index and the row contents.
    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::cout << (row + 1) << ' ';
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::cout << board[row][col] << ' ';
        }
        std::cout << '\n';
    }
}

// Clears the board by filling all squares with emptySpace.
void clearBoard() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            board[row][col] = emptySpace;
        }
    }
}

// Places white and black pawns on their default ranks.
void initializePawns() {
    // White pawns on rank 7 (index 6)
    for (int col = 0; col < BOARD_SIZE; ++col) {
        board[6][col] = whitePawn;
    }

    // Black pawns on rank 2 (index 1)
    for (int col = 0; col < BOARD_SIZE; ++col) {
        board[1][col] = blackPawn;
    }
}

// Places rooks, knights, bishops, queen, and king on starting squares.
void initializePieces() {
    // White back rank (index 7)
    board[7][0] = whiteTower;
    board[7][1] = whiteHorse;
    board[7][2] = whiteBishop;
    board[7][3] = whiteQueen;
    board[7][4] = whiteKing;
    board[7][5] = whiteBishop;
    board[7][6] = whiteHorse;
    board[7][7] = whiteTower;

    // Black back rank (index 0)
    board[0][0] = blackTower;
    board[0][1] = blackHorse;
    board[0][2] = blackBishop;
    board[0][3] = blackQueen;
    board[0][4] = blackKing;
    board[0][5] = blackBishop;
    board[0][6] = blackHorse;
    board[0][7] = blackTower;
}

// Initializes the full board to the standard starting position.
void initBoard() {
    clearBoard();
    initializePieces();
    initializePawns();
}

// Public interface to print the board (does not modify state).
void printBoard() {
    printBoardWithIndex();
}

// Returns the piece at the given row and column.
char getPiece(int row, int col) {
    return board[row][col];
}

// Sets the piece at the given row and column.
void setPiece(int row, int col, char piece) {
    board[row][col] = piece;
}
