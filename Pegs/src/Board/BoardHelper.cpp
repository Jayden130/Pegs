#include <string>
#include <bit>
#include "Board/BoardHelper.hpp"

int PopLSB(uint64_t& value)
{
	int index = std::countr_zero(value); // Index of LSB
	value &= value - 1; // Clear the LSB
	return index;
}

int GetLSB(uint64_t& value)
{
	int index = std::countr_zero(value); // Index of LSB
	return index;
}

int CountBits(uint64_t value)
{
	return std::popcount(value);
}

void SetSquare(uint64_t& bitboard, int squareIndex)
{
	bitboard |= 1ull << squareIndex;
}

void ClearSquare(uint64_t& bitboard, int squareIndex)
{
	bitboard &= ~(1ull << squareIndex);
}

void ToggleSquares(uint64_t& bitboard, int squareA, int squareB)
{
	bitboard ^= (1ull << squareA | 1ull << squareB);
}

bool SquareIsSet(uint64_t bitboard, int squareIndex)
{
	return ((bitboard >> squareIndex) & 1) != 0;
}

bool ValidSquare(int x, int y)
{
	return x >= 0 && x < 4 && y >= 0 && y < 6;
}
bool ValidSquare(int x, int y, int& index)
{
	index = GetSquareIndex(x, y);
	return x >= 0 && x < 4 && y >= 0 && y < 6;
}
int GetSquareIndex(int x, int y)
{
	return y * x + x;
}

int FileIndex(int squareIndex)
{
	return (squareIndex & 0b000011) + 1;
}

int RankIndex(int squareIndex)
{
	return (squareIndex >> 2) + 1;
}
