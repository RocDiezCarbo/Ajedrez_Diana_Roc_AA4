#pragma once

// Pawn move validation
bool isPawnMoveValid(int fromRow, int fromCol, int toRow, int toCol);

// Rook move validation
bool isRookMoveValid(int fromRow, int fromCol, int toRow, int toCol);

// Queen move validation
bool isQueenMoveValid(int fromRow, int fromCol, int toRow, int toCol);

// Bishop move validation
bool isBishopMoveValid(int fromRow, int fromCol, int toRow, int toCol);

// King move validation 
bool isKingMoveValid(int fromRow, int fromCol, int toRow, int toCol)