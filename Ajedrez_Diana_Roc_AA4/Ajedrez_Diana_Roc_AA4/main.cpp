#include <iostream>
#include <cctype>
#include "constants.h"
#include "board.h"
#include "movement.h"
#include "check.h"


int main() {

    bool gameOver = false;
    bool whiteTurn = true;

    initBoard();     // set starting position
    printBoard();    // show initial board


    while (!gameOver)
    {
        std::cout << (whiteTurn ? "White's turn.\n" : "Black's turn.\n");

        int fromRow, fromCol;
        char piece;

        // Piece selection
        while (true)
        {
            std::cout << "Select piece (row col): ";
            std::cin >> fromRow >> fromCol;

            fromRow -= 1;
            fromCol -= 1;

            if (fromRow < 0 || fromRow >= BOARD_SIZE ||
                fromCol < 0 || fromCol >= BOARD_SIZE)
            {
                std::cout << "Out of bounds.\n";
                continue;
            }

            piece = getPiece(fromRow, fromCol);

            if (piece == emptySpace)
            {
                std::cout << "No piece there.\n";
                continue;
            }

            if (whiteTurn && !std::isupper(piece)) {
                std::cout << "Not a white piece.\n";
                continue;
            }

            if (!whiteTurn && !std::islower(piece)) {
                std::cout << "Not a black piece.\n";
                continue;
            }

            break;
        }

        // Destination selection
        int toRow, toCol;

        while (true)
        {
            std::cout << "Select destination (row col): ";
            std::cin >> toRow >> toCol;

            toRow -= 1;
            toCol -= 1;

            if (toRow < 0 || toRow >= BOARD_SIZE ||
                toCol < 0 || toCol >= BOARD_SIZE)
            {
                std::cout << "Out of bounds.\n";
                continue;
            }

            if (toRow == fromRow && toCol == fromCol)
            {
                std::cout << "Same square.\n";
                continue;
            }

            break;
        }

        // Validate movement 
        bool moveValid = false;

        switch (std::tolower(static_cast<unsigned char>(piece)))
        {
        case 'p':   // pawn
            moveValid = isPawnMoveValid(fromRow, fromCol, toRow, toCol);
            break;

        case 't':   // rook (tower)
            moveValid = isRookMoveValid(fromRow, fromCol, toRow, toCol);
            break;

        case 'b':   // bishop
            moveValid = isBishopMoveValid(fromRow, fromCol, toRow, toCol);
            break;

        case 'k':   // king
            moveValid = isKingMoveValid(fromRow, fromCol, toRow, toCol);
            break;
        case 'h':   // horse
            moveValid = isHorseMoveValid(fromRow, fromCol, toRow, toCol);
            break;

        case 'q':
            moveValid = isQueenMoveValid(fromRow, fromCol, toRow, toCol);
            break;

        default:
            std::cout << "Piece not implemented.\n";
            moveValid = false;
            break;
        }

        // Apply movement
        if (moveValid)
        {
            // Guardar lo que había en destino ANTES de sobrescribirlo
            char captured = getPiece(toRow, toCol);

            // Movimiento provisional
            setPiece(toRow, toCol, piece);
            setPiece(fromRow, fromCol, emptySpace);

            // ---------- BLOQUEO: no permitir dejar tu rey en jaque ----------
            if (isKingInCheck(whiteTurn))
            {
                // Deshacer movimiento
                setPiece(fromRow, fromCol, piece);
                setPiece(toRow, toCol, captured);

                std::cout << "Illegal move (your king would be in check).\n";
                continue;
            }

            // ---------- END GAME: king captured ----------
            char enemyKing = whiteTurn ? blackKing : whiteKing;
            if (captured == enemyKing)
            {
                clearScreen();
                printBoard();
                std::cout << (whiteTurn ? "White wins (king captured).\n"
                    : "Black wins (king captured).\n");
                gameOver = true;
                continue;
            }

            // ---------- Pawn promotion ----------
            if (piece == whitePawn && toRow == 0)
            {
                setPiece(toRow, toCol, whiteQueen);
            }
            else if (piece == blackPawn && toRow == BOARD_SIZE - 1)
            {
                setPiece(toRow, toCol, blackQueen);
            }

            whiteTurn = !whiteTurn;   // change turn
            clearScreen();            // clear screen
            printBoard();             // show board

            if (isKingInCheck(whiteTurn))
                std::cout << "Check!\n";

            if (isCheckmate(whiteTurn))
            {
                std::cout << (whiteTurn ? "Checkmate! Black wins.\n"
                    : "Checkmate! White wins.\n");
                gameOver = true;
            }
        }
        else
        {
            std::cout << "Illegal move.\n";
        }

        return 0;
    }

}
