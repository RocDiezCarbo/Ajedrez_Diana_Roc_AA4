#pragma once

#include "constants.h"
#include <iostream>

class Board {
public:
    Board();
    void clear();
    void initializePawns();
    void initializePieces();
    void init();
    void print() const;
    char getPiece(int row, int col) const;
    void setPiece(int row, int col, char piece);

private:
    char squares[BOARD_SIZE][BOARD_SIZE];
    void printWithIndex() const;
};

