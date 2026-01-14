#include "check.h"
#include "board.h"
#include "constants.h"
#include "movement.h"

#include <cctype>

// simulate movments
struct Undo {
    char captured;
};

static Undo makeMove(int fr, int fc, int tr, int tc)
{
    Undo u{ getPiece(tr, tc) };
    char p = getPiece(fr, fc);
    setPiece(tr, tc, p);
    setPiece(fr, fc, emptySpace);
    return u;
}

static void undoMove(int fr, int fc, int tr, int tc, Undo u)
{
    char p = getPiece(tr, tc);
    setPiece(fr, fc, p);
    setPiece(tr, tc, u.captured);
}

// call validator for each pice
static bool isMoveValidByPiece(char piece, int fr, int fc, int tr, int tc)
{
    switch (std::tolower(static_cast<unsigned char>(piece)))
    {
    case 'p': return isPawnMoveValid(fr, fc, tr, tc);
    case 't': return isRookMoveValid(fr, fc, tr, tc);
    case 'b': return isBishopMoveValid(fr, fc, tr, tc);
    case 'q': return isQueenMoveValid(fr, fc, tr, tc);
    case 'k': return isKingMoveValid(fr, fc, tr, tc);
    case 'h': return isHorseMoveValid(fr, fc, tr, tc);
    default:
        return false;
    }
}

bool isKingInCheck(bool whiteKing)
{
    int kr, kc;
    if (!findKing(whiteKing, kr, kc))
        return false;

    for (int r = 0; r < BOARD_SIZE; ++r)
        for (int c = 0; c < BOARD_SIZE; ++c)
        {
            char p = getPiece(r, c);
            if (p == emptySpace) continue;

            bool pIsWhite = std::isupper(static_cast<unsigned char>(p));
            if (pIsWhite == whiteKing) continue; // solo enemigos

            if (attacksSquare(p, r, c, kr, kc))
                return true;
        }

    return false;
}

bool isCheckmate(bool whiteToMove)
{
    // if not chake not chake mate
    if (!isKingInCheck(whiteToMove))
        return false;

    // search legal movment to go out of check
    for (int fr = 0; fr < BOARD_SIZE; ++fr)
        for (int fc = 0; fc < BOARD_SIZE; ++fc)
        {
            char piece = getPiece(fr, fc);
            if (piece == emptySpace) continue;

            bool pieceIsWhite = std::isupper(static_cast<unsigned char>(piece));
            if (pieceIsWhite != whiteToMove) continue;

            for (int tr = 0; tr < BOARD_SIZE; ++tr)
                for (int tc = 0; tc < BOARD_SIZE; ++tc)
                {
                    if (fr == tr && fc == tc) continue;

                    if (!isMoveValidByPiece(piece, fr, fc, tr, tc))
                        continue;

                    Undo u = makeMove(fr, fc, tr, tc);
                    bool stillInCheck = isKingInCheck(whiteToMove);
                    undoMove(fr, fc, tr, tc, u);

                    if (!stillInCheck)
                        return false; // exsist scape -> check mate
                }
        }

    return true; // in check with out scape -> chake mate
}
