#include <iostream>

#include "constant.h"

void emptyBoard() {

	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			std::cout << emptySpace << " ";
		}
		std::cout << "\n";
	}

}

void main() {
	emptyBoard();
}