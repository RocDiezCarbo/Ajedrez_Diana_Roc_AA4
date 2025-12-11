#include "board.h"
#include "constants.h"
#include "movement.h"
#include <iostream>
#include <cctype>   // para std::isupper, std::islower

bool isPawnMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = getPiece(fromRow, fromCol);

    if (fromRow < 0 && fromRow >= BOARD_SIZE || toCol < 0 && toCol >= BOARD_SIZE) {

        return false;
    }

    if (piece!=whitePawn && piece != blackPawn)
    {
        return false; 
    }

    bool isWhite = (piece = whitePawn); //Dirección: -1 para BLANCAS
    int direction;
    if (isWhite)
    {
        direction = -1;
    }
    else
    {
        direction = 1;
    }





    

   
     

     



    

 
}

bool isRookMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = getPiece(fromRow, fromCol);
    char target = getPiece(toRow, toCol);

    if (fromRow != toRow && fromCol != toCol)
        return false;

    // 2. Dirección del movimiento
    int deltaRow = 0, deltaCol = 0;

    if (toRow > fromRow)     
        deltaRow = 1;
    else if (toRow < fromRow) 
        deltaRow = -1;

    if (toCol > fromCol)     
        deltaCol = 1;
    else if (toCol < fromCol)
        deltaCol = -1;

    // 3. Comprobar que no haya piezas en medio
    int row = fromRow + deltaRow;
    int col = fromCol + deltaCol;

    while (row != toRow || col != toCol)
    {
        if (getPiece(row, col) != emptySpace)
            return false;

        row += deltaRow;
        col += deltaCol;
    }

    // 4. Comprobar la casilla de destino
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
