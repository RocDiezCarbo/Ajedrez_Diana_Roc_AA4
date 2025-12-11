#include "board.h"
#include "constants.h"
#include <iostream>

// Constructor: build an empty board and then place all standard pieces.
Board::Board() {
    init();
}

// Clears the board by filling all squares with emptySpace.
void Board::clear() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            squares[row][col] = emptySpace;
        }
    }
}

// Places white and black pawns on their default ranks.
void Board::initializePawns() {
    // White pawns on rank 7 (index 6)
    for (int col = 0; col < BOARD_SIZE; ++col) {
        squares[6][col] = whitePawn;
    }

    // Black pawns on rank 2 (index 1)
    for (int col = 0; col < BOARD_SIZE; ++col) {
        squares[1][col] = blackPawn;
    }
}

// Places rooks, knights, bishops, queen, and king on starting squares.
void Board::initializePieces() {
    // White back rank (index 7)
    squares[7][0] = whiteTower;
    squares[7][1] = whiteHorse;
    squares[7][2] = whiteBishop;
    squares[7][3] = whiteQueen;
    squares[7][4] = whiteKing;
    squares[7][5] = whiteBishop;
    squares[7][6] = whiteHorse;
    squares[7][7] = whiteTower;

    // Black back rank (index 0)
    squares[0][0] = blackTower;
    squares[0][1] = blackHorse;
    squares[0][2] = blackBishop;
    squares[0][3] = blackQueen;
    squares[0][4] = blackKing;
    squares[0][5] = blackBishop;
    squares[0][6] = blackHorse;
    squares[0][7] = blackTower;
}

// Initializes the full board to the standard starting position.
void Board::init() {
    clear();
    initializePieces();
    initializePawns();
}

// Helper method to print coordinates and the internal board.
void Board::printWithIndex() const {
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
            std::cout << squares[row][col] << ' ';
        }
        std::cout << '\n';
    }
}

// Public interface to print the board (does not modify state).
void Board::print() const {
    printWithIndex();
}

// Returns the piece at the given row and column.
char Board::getPiece(int row, int col) const {
    return squares[row][col];
}

// Sets the piece at the given row and column.
void Board::setPiece(int row, int col, char piece) {
    squares[row][col] = piece;
}
