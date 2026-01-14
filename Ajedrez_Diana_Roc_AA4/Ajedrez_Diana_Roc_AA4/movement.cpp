
#include "board.h"
#include "constants.h"
#include "movement.h"
#include <cctype>

// ---------- internal utilities ----------

static bool inBounds(int r, int c)
{
    return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
}

static bool isWhitePiece(char p)
{
    return std::isupper(static_cast<unsigned char>(p));
}

static bool sameColor(char a, char b)
{
    if (a == emptySpace || b == emptySpace) {
        return false;
    }
    return isWhitePiece(a) == isWhitePiece(b);
}

static int absInt(int x)
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

    // One-square advance
    if (dc == 0 && dr == direction)
        return target == emptySpace;

    // Two-square advance from starting position
    if (dc == 0 && dr == 2 * direction)
    {
        if (fromRow != startRow)
            return false;

        int midRow = fromRow + direction;
        return getPiece(midRow, fromCol) == emptySpace &&
            target == emptySpace;
    }

    // Diagonal capture
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

// ---------- KING ----------

bool isKingMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!inBounds(fromRow, fromCol) || !inBounds(toRow, toCol))
        return false;

    if (fromRow == toRow && fromCol == toCol)
        return false;

    char piece = getPiece(fromRow, fromCol);
    if (piece != whiteKing && piece != blackKing)
        return false;

    int dr = absInt(toRow - fromRow);
    int dc = absInt(toCol - fromCol);

    if (dr > 1 || dc > 1)
    {
        return false;
    }

    char target = getPiece(toRow, toCol);

    if (target != emptySpace && sameColor(piece, target))
        return false;

    return true;
}

// ---------- BISHOP ----------

bool isBishopMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!inBounds(fromRow, fromCol) || !inBounds(toRow, toCol))
        return false;

    if (fromRow == toRow && fromCol == toCol)
        return false;

    char piece = getPiece(fromRow, fromCol);
    if (piece != whiteBishop && piece != blackBishop)
        return false;

    int dr = toRow - fromRow;
    int dc = toCol - fromCol;

    bool diagonal = (absInt(dr) == absInt(dc));

    if (!diagonal)
    {
        return false;
    }

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

// ---------- KNIGHT ----------

bool isHorseMoveValid(int fromRow, int fromCol, int toRow, int toCol)
{
    if (!inBounds(fromRow, fromCol) || !inBounds(toRow, toCol))
        return false;

    if (fromRow == toRow && fromCol == toCol)
        return false;

    char piece = getPiece(fromRow, fromCol);
    if (piece != whiteHorse && piece != blackHorse)
        return false;

    int dr = absInt(toRow - fromRow);
    int dc = absInt(toCol - fromCol);

    // "L" Shape Movement: (2,1) or (1,2)
    bool lShape = (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
    if (!lShape)
        return false;

    char target = getPiece(toRow, toCol);

    // Prevent capturing pieces of the same color
    if (target != emptySpace && sameColor(piece, target))
        return false;

    return true;
}

bool attacksSquare(char enemyPiece, int fromR, int fromC, int targetR, int targetC)
{
    // Bounds safety check
    if (!inBounds(fromR, fromC) || !inBounds(targetR, targetC))
        return false;

    if (fromR == targetR && fromC == targetC)
        return false;

    unsigned char up = static_cast<unsigned char>(enemyPiece);
    char type = static_cast<char>(std::tolower(up));

    int dr = targetR - fromR;
    int dc = targetC - fromC;

    // ---------- PAWN (attack logic != movement logic) ----------
    if (type == 'p')
    {
        bool enemyIsWhite = std::isupper(up);
        int dir = enemyIsWhite ? -1 : 1; // white attacks upwards, black downwards
        return (dr == dir) && (absInt(dc) == 1);
    }

    // ---------- KNIGHT (H/h in project) ----------
    if (type == 'h')
    {
        return (absInt(dr) == 2 && absInt(dc) == 1) || (absInt(dr) == 1 && absInt(dc) == 2);
    }

    // ---------- KING ----------
    if (type == 'k')
    {
        return (absInt(dr) <= 1 && absInt(dc) <= 1);
    }

    // For sliding pieces, calculate step and validate geometry
    int stepR = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
    int stepC = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);

    // ---------- ROOK (T/t in project) ----------
    if (type == 't')
    {
        if (dr != 0 && dc != 0)
            return false;
    }
    // ---------- BISHOP ----------
    else if (type == 'b')
    {
        if (absInt(dr) != absInt(dc))
            return false;
    }
    // ---------- QUEEN ----------
    else if (type == 'q')
    {
        bool straight = (dr == 0 || dc == 0);
        bool diagonal = (absInt(dr) == absInt(dc));
        if (!straight && !diagonal)
            return false;
    }
    else
    {
        // Unrecognized piece
        return false;
    }

    // ---------- check for blocking pieces (obstacles) ----------
    int r = fromR + stepR;
    int c = fromC + stepC;

    while (r != targetR || c != targetC)
    {
        if (getPiece(r, c) != emptySpace)
            return false;

        r += stepR;
        c += stepC;
    }

    return true;
}