#pragma once

// Board size
const int BOARD_SIZE = 8;

// Global board storage (defined in constants.cpp)
extern char board[BOARD_SIZE][BOARD_SIZE];

// Empty square
extern const char emptySpace;

// White pieces
extern const char whitePawn;
extern const char whiteTower;
extern const char whiteBishop;
extern const char whiteHorse;
extern const char whiteQueen;
extern const char whiteKing;

// Black pieces
extern const char blackPawn;
extern const char blackTower;
extern const char blackBishop;
extern const char blackHorse;
extern const char blackQueen;
extern const char blackKing;

void clearScreen();