#include <iostream>
#include "constants.h"
#include "board.h"

// Global board definition
char board[BOARD_SIZE][BOARD_SIZE];

// Create an empty 8x8 board
void emptyBoard() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = emptySpace;
        }
    }
}

// Initialize pawns
void initializePawns() {
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[6][x] = whitePawn; // White pawns
        board[1][x] = blackPawn; // Black pawns
    }
}

// Initialize the rest of the pieces
void initializePieces() {
    // White pieces
    board[7][0] = whiteTower;
    board[7][1] = whiteHorse;
    board[7][2] = whiteBishop;
    board[7][3] = whiteQueen;
    board[7][4] = whiteKing;
    board[7][5] = whiteBishop;
    board[7][6] = whiteHorse;
    board[7][7] = whiteTower;

    // Black pieces
    board[0][0] = blackTower;
    board[0][1] = blackHorse;
    board[0][2] = blackBishop;
    board[0][3] = blackQueen;
    board[0][4] = blackKing;
    board[0][5] = blackBishop;
    board[0][6] = blackHorse;
    board[0][7] = blackTower;
}

// Print the board row/column indexes
void printIndex() {
    std::cout << "  ";
    for (int x = 0; x < BOARD_SIZE; x++) {
        std::cout << (x + 1) << ' ';
    }
    std::cout << '\n';

    for (int y = 0; y < BOARD_SIZE; y++) {
        std::cout << (y + 1) << ' ';

        for (int x = 0; x < BOARD_SIZE; x++) {
            std::cout << board[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

// Initialize the complete board
void initBoard() {
    emptyBoard();
    initializePieces();
    initializePawns();
}

// Print the board (does not modify it)
void printBoard() {
    printIndex();
}
