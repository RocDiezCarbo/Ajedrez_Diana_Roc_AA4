#include "board.h"
#include "constants.h"
#include "movement.h"
#include <cctype>

// ---------- utilidades internas ----------

bool inBounds(int r, int c)
{
    return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
}

bool isWhitePiece(char p)
{
    return std::isupper(static_cast<unsigned char>(p));
}

bool sameColor(char a, char b)
{
    return isWhitePiece(a) == isWhitePiece(b);
}

int absInt(int x)
{
    return (x < 0) ? -x : x;
}

// ---------- PAWN ----------

bool isPawnMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!inBounds(fromRow, fromCol) || !inBounds(toRow, toCol))
        return false;

    if (fromRow == toRow && fromCol == toCol)
        return false;

    char piece = getPiece(fromRow, fromCol);
    if (piece != whitePawn && piece != blackPawn)
        return false;

    bool isWhite = (piece == whitePawn);
    int direction = isWhite ? -1 : 1;
    int startRow = isWhite ? 6 : 1;

    int dr = toRow - fromRow;
    int dc = toCol - fromCol;

    char target = getPiece(toRow, toCol);

    // avance de una casilla
    if (dc == 0 && dr == direction)
        return target == emptySpace;

    // avance de dos casillas desde la posición inicial
    if (dc == 0 && dr == 2 * direction)
    {
        if (fromRow != startRow)
            return false;

        int midRow = fromRow + direction;
        return getPiece(midRow, fromCol) == emptySpace &&
            target == emptySpace;
    }

    // captura diagonal
    if (absInt(dc) == 1 && dr == direction)
    {
        if (target == emptySpace)
            return false;

        return !sameColor(piece, target);
    }

    return false;
}

// ---------- ROOK ----------

bool isRookMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!inBounds(fromRow, fromCol) || !inBounds(toRow, toCol))
        return false;

    if (fromRow == toRow && fromCol == toCol)
        return false;

    char piece = getPiece(fromRow, fromCol);
    if (piece != whiteTower && piece != blackTower)
        return false;

    if (fromRow != toRow && fromCol != toCol)
        return false;

    char target = getPiece(toRow, toCol);

    int stepR = (toRow > fromRow) ? 1 : (toRow < fromRow ? -1 : 0);
    int stepC = (toCol > fromCol) ? 1 : (toCol < fromCol ? -1 : 0);

    int r = fromRow + stepR;
    int c = fromCol + stepC;

    while (r != toRow || c != toCol)
    {
        if (getPiece(r, c) != emptySpace)
            return false;

        r += stepR;
        c += stepC;
    }

    if (target != emptySpace && sameColor(piece, target))
        return false;

    return true;
}

// ---------- QUEEN ----------

bool isQueenMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!inBounds(fromRow, fromCol) || !inBounds(toRow, toCol))
        return false;

    if (fromRow == toRow && fromCol == toCol)
        return false;

    char piece = getPiece(fromRow, fromCol);
    if (piece != whiteQueen && piece != blackQueen)
        return false;

    int dr = toRow - fromRow;
    int dc = toCol - fromCol;

    bool straight = (dr == 0 || dc == 0);
    bool diagonal = (absInt(dr) == absInt(dc));

    if (!straight && !diagonal)
        return false;

    char target = getPiece(toRow, toCol);

    int stepR = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
    int stepC = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

    int r = fromRow + stepR;
    int c = fromCol + stepC;

    while (r != toRow || c != toCol)
    {
        if (getPiece(r, c) != emptySpace)
            return false;

        r += stepR;
        c += stepC;
    }

    if (target != emptySpace && sameColor(piece, target))
        return false;

    return true;
}

