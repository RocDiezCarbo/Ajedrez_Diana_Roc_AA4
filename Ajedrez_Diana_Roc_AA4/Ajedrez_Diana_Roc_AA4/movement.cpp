#include "board.h"
#include "constants.h"
#include "movement.h"
#include <iostream>
#include <cctype>   // para std::isupper, std::islower

bool isPawnMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{

   if (fromRow<0 && fromRow>BOARD_SIZE || fromCol<0 && fromCol> BOARD_SIZE || ) 
     

     


   char piece = getPiece(fromRow, fromCol);

    

 
}

bool isRookMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = getPiece(fromRow, fromCol);
    char target = getPiece(toRow, toCol);

    if (fromRow != toRow && fromCol != toCol)
        return false;

    // Direction
    int deltaRow = 0, deltaCol = 0;

    if (toRow > fromRow)     
        deltaRow = 1;
    else if (toRow < fromRow) 
        deltaRow = -1;

    if (toCol > fromCol)     
        deltaCol = 1;
    else if (toCol < fromCol)
        deltaCol = -1;

    // Check no pieces in front
    int row = fromRow + deltaRow;
    int col = fromCol + deltaCol;

    while (row != toRow || col != toCol)
    {
        if (getPiece(row, col) != emptySpace)
            return false;

        row += deltaRow;
        col += deltaCol;
    }

    // Chack destinatio
    if (target != emptySpace)
    {
        bool originWhite = std::isupper(static_cast<unsigned char>(piece));
        bool targetWhite = std::isupper(static_cast<unsigned char>(target));

        // Mismo color → movimiento ilegal
        if (originWhite == targetWhite)
            return false;
    }

    return true;
}
