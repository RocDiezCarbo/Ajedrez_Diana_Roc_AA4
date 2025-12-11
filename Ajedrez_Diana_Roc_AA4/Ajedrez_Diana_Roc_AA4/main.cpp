#include <iostream>
#include <cctype>       // for isupper, islower
#include "constants.h"
#include "board.h"

int main() {

    bool gameOver = false;
    bool whiteTurn = true;

    // Initialize the board to the standard chess starting position.
    initBoard();

    // Print the starting board.
    printBoard();

    // Main game loop
    while (!gameOver)   // Correct logical comparison
    {
        // Display whose turn it is
        if (whiteTurn)
        {
            std::cout << "White's turn.\n";
        }
        else
        {
            std::cout << "Black's turn.\n";
        }

        int fromRow, fromCol;

        while (true)
        {
            std::cout << "Select the piece you want to move (row column, 1-8 1-8): ";
            std::cin >> fromRow >> fromCol;

            // Convert user input (1-8) to internal indices (0-7)
            fromRow -= 1;
            fromCol -= 1;

            // Validate that the coordinates are inside the board
            if (fromRow < 0 || fromRow >= BOARD_SIZE ||
                fromCol < 0 || fromCol >= BOARD_SIZE)
            {
                std::cout << "Coordinates are out of bounds. Try again.\n";
                continue;
            }

            // Retrieve the piece from the selected square
            char piece = getPiece(fromRow, fromCol);

            // Ensure the square is not empty
            if (piece == emptySpace)
            {
                std::cout << "There is no piece on that square. Try again.\n";
                continue;
            }

            // Validate that the selected piece belongs to the current player
            if (whiteTurn)
            {
                // White pieces are uppercase
                if (!std::isupper(static_cast<unsigned char>(piece)))
                {
                    std::cout << "The selected piece is not white. Try again.\n";
                    continue;
                }
            }
            else
            {
                // Black pieces are lowercase
                if (!std::islower(static_cast<unsigned char>(piece)))
                {
                    std::cout << "The selected piece is not black. Try again.\n";
                    continue;
                }
            }

            // If we reach this point, the selection is valid
            std::cout << "You selected piece '" << piece
                << "' at (" << (fromRow + 1) << ", " << (fromCol + 1) << ").\n";
            break;
        }


        // Temporary stop to avoid infinite loop until movement logic is added
        gameOver = true;
    }

    return 0;
}
