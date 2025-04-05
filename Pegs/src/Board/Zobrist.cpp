#include <random>
#include "Board/Board.hpp"
#include "Board/BoardHelper.hpp"
#include "Board/Zobrist.hpp"

void Zobrist::Init()
{
    for (int squareIndex = 0; squareIndex < 24; squareIndex++)
    {
        for (int i = 0; i < 2; i++)
        {
            piecesArray[i][squareIndex] = RandomUnsigned64BitNumber();
        }
    }

    sideToMove = RandomUnsigned64BitNumber();
}

// Calculate zobrist key from current board position.
// NOTE: this function is slow and should only be used when the board is initially set up from fen.
// During search, the key should be updated incrementally instead.
uint64_t Zobrist::CalculateZobristKey(Board& board)
{
    uint64_t zobristKey = 0;

    for (int squareIndex = 0; squareIndex < 24; squareIndex++)
    {
        if (!SquareIsSet(board.bitboards[2], squareIndex))
        {
            zobristKey ^= piecesArray[SquareIsSet(board.bitboards[0], squareIndex) ? 0 : 1][squareIndex];
        }
    }
    if (board.turn == Piece::black)
    {
        zobristKey ^= sideToMove;
    }

    return zobristKey;
}

uint64_t Zobrist::RandomUnsigned64BitNumber() noexcept
{
    static std::mt19937_64 engine(seed);
    return engine();
}

const std::array<std::array<uint64_t, 24>, 2>& Zobrist::GetPiecesArray()
{
    return piecesArray;
}

const uint64_t& Zobrist::GetSideToMove()
{
    return sideToMove;
}
