#include "board.h"
#include "constants.h"
#include "movement.h"
#include <iostream>
#include <cctype>   // para std::isupper, std::islower

bool isPawnMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    char piece = getPiece(fromRow, fromCol);

    if (fromRow < 0 || fromRow >= BOARD_SIZE || toRow < 0 && toRow >= BOARD_SIZE || fromCol < 0 || fromCol >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE) {

        return false;
    }

    if (piece!=whitePawn && piece != blackPawn)
    {
        return false; 
    }

    bool isWhite = (piece = whitePawn); //Dirección: -1 para BLANCAS
    int direction;
    int startRow;

    if (isWhite)
    {
        direction = -1;
        startRow = 6;
    }
    else
    {
        direction = 1;
        startRow = 1;
    }

    int deltaR = toRow - fromRow;
    int deltaC_raw = toCol - fromCol;
    int deltaC;


    if (deltaC_raw < 0) {
        deltaC = -deltaC_raw;
    }
    else {
        deltaC = deltaC_raw;
    }

    char destinationPiece = getPiece(toRow, toCol);

   //solo permitimos avance recto
    if (deltaC != 0) {
        return false;
    }

    //revisamos que la diferencia de fila sea en la dirección correcta
    if (deltaR * direction < 0) {
        return false;
    }

    // Avance de un casillero
    if (deltaR == direction) {
        // Debe estar vacío
        if (destinationPiece == emptySpace) {
            return true;
        }
    }

    // Avance de dos casilleros (solo desde la fila inicial)
    else if (deltaR == (2 * direction)) {
        // 1. Debe estar en la fila de inicio
        if (fromRow != startRow) {
            return false;
        }

        // 2. El destino y el casillero intermedio deben estar vacíos
        int intermediateRow = fromRow + direction;

        // Verificación de dos casilleros vacíos
        if (getPiece(intermediateRow, fromCol) == emptySpace) {
            if (destinationPiece == emptySpace) {
                return true;
            }
        }
    }

    // Si no es un movimiento de 1 ni 2 casilleros, es inválido.
    return false;
}

   
     

     



    

 
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
