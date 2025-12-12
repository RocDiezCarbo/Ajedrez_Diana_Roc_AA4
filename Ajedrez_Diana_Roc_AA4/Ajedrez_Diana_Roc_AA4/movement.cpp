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

    bool isWhite = (piece = whitePawn); //dirección: -1 para BLANCAS
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

    //avanza UNA casilla
    if (deltaR == direction) {
        if (destinationPiece == emptySpace) {
            return true;
        }
    }

    //avanza DOS casillas pero solo si esta en la posicion inicial 
    else if (deltaR == (2 * direction)) {
        if (fromRow != startRow) {
            return false;
        }

        //la casilla destino y la casilla origen tienen que estar vacíos
        int intermediateRow = fromRow + direction;

        //verificamos
        if (getPiece(intermediateRow, fromCol) == emptySpace) {
            if (destinationPiece == emptySpace) {
                return true;
            }
        }
    }

    return false;
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

    // Chack destination
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



bool isQueenMoveValid(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow < 0 || fromRow >= BOARD_SIZE || toRow < 0 || toRow >= BOARD_SIZE ||
        fromCol < 0 || fromCol >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE) {
        return false;
    }

    //mira si origen y destino son iguales pq sino es inválido
    if (fromRow == toRow && fromCol == toCol) {
        return false;
    }

    char piece = getPiece(fromRow, fromCol);
    char target = getPiece(toRow, toCol);


    int deltaR_raw = toRow - fromRow;
    int deltaC_raw = toCol - fromCol;

    int deltaR_abs;
    if (deltaR_raw < 0) {
        deltaR_abs = -deltaR_raw;
    }
    else {
        deltaR_abs = deltaR_raw;
    }

    int deltaC_abs;//deltaC absolut
    if (deltaC_raw < 0) {
        deltaC_abs = -deltaC_raw;
    }
    else {
        deltaC_abs = deltaC_raw;
    }

    //movimiento recto 
    bool isStraight = false;
    if (deltaR_abs == 0 || deltaC_abs == 0) {
        if (deltaR_abs > 0 || deltaC_abs > 0) {
            isStraight = true;
        }
    }

    //movimiento diagonal 
    bool isDiagonal = false;
    if (deltaR_abs == deltaC_abs) {
        if (deltaR_abs > 0) {
            isDiagonal = true;
        }
    }

    //si no es ni recto ni diagonal
    if (!isStraight && !isDiagonal) {
        return false;
    }

    int deltaRow = 0;
    int deltaCol = 0;

    //dirección de Fila
    if (toRow > fromRow) {
        deltaRow = 1;
    }
    else if (toRow < fromRow) {
        deltaRow = -1;
    }

    //dirección de Columna
    if (toCol > fromCol) {
        deltaCol = 1;
    }
    else if (toCol < fromCol) {
        deltaCol = -1;
    }


    int row = fromRow + deltaRow;
    int col = fromCol + deltaCol;

    //miramos la trayectoria hasta llegar al destino
    while (row != toRow || col != toCol) {
        if (getPiece(row, col) != emptySpace) {
            return false; //es que hay una pieza bloqueando el camino.
        }

        row += deltaRow;
        col += deltaCol;
    }


    //mirat aixo roc pq no se si esta be del tot aquesta part pq ni ide d q es lo de static char, li he dit del chat q ho copies del teu codi de la torre
    if (target != emptySpace) {

        //color de la pieza de origen
        bool originIsWhite;
        if (std::isupper(static_cast<unsigned char>(piece))) {
            originIsWhite = true;
        }
        else {
            originIsWhite = false;
        }

        //el color de la pieza en el destino
        bool targetIsWhite;
        if (std::isupper(static_cast<unsigned char>(target))) {
            targetIsWhite = true;
        }
        else {
            targetIsWhite = false;
        }

        //si los colores son iguales, el movimiento es inválido (no se puede capturar una pieza amiga)
        if (originIsWhite == targetIsWhite) {
            return false;
        }
    }
    return true;
}

