#include "board.h"

char board[BOARD_SIZE][BOARD_SIZE];

void emptyBoard() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = emptySpace;
        }
    }
}

void inicializatePawns() {
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[6][x] = whitePawn;
    }

    for (int x = 0; x < BOARD_SIZE; x++) {
        board[1][x] = blackPawn;
    }
}

void inicializatePieces() {
    // Piezas blancas
    board[7][0] = whiteTower;
    board[7][1] = whiteHorse;
    board[7][2] = whiteBishop;
    board[7][3] = whiteQueen;
    board[7][4] = whiteKing;
    board[7][5] = whiteBishop;
    board[7][6] = whiteHorse;
    board[7][7] = whiteTower;

    // Piezas negras
    board[0][0] = blackTower;
    board[0][1] = blackHorse;
    board[0][2] = blackBishop;
    board[0][3] = blackQueen;
    board[0][4] = blackKing;
    board[0][5] = blackBishop;
    board[0][6] = blackHorse;
    board[0][7] = blackTower;
}

void printBoard() {
    emptyBoard();
    inicializatePieces();
    inicializatePawns();

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            std::cout << board[y][x] << ' ';
        }
        std::cout << '\n';
    }
}
