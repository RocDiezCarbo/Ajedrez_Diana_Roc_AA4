#include "board.h"

char board[BOARD_SIZE][BOARD_SIZE];

// Create the 8x8 empty board
void emptyBoard() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = emptySpace;
        }
    }
}

// Inicializate the Pawns
void inicializatePawns() {
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[6][x] = whitePawn;
    }

    for (int x = 0; x < BOARD_SIZE; x++) {
        board[1][x] = blackPawn;
    }
}

// Inicializate the rest of the pieces
void inicializatePieces() {
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

// Print the index of the table
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

// Make the print of the chess table
void printBoard() {
    // First initialize board
    emptyBoard();
    inicializatePieces();
    inicializatePawns();

    // Then print with indexes
    printIndex();
}
