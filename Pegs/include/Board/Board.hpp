#pragma once

#include <string>
#include <vector>
#include "Board/Piece.hpp"
#include "Board/Move.hpp"
#include "Board/GameResult.hpp"

class Board
{
public:
	Board() {}
	Board(Board& board);
	Board(std::string fen);

	Piece turn = Piece::white;
	uint64_t bitboards[3] = {0, 0, 0};

	std::vector<uint64_t> repetitionPositionHistory;

	void MakeMove(Move move);
	void UndoMove(Move move);
	void Turn();
	GameResult GetGameResult();
	uint64_t GetZobristKey() const;

private:
	uint64_t zobristKey = 0;
};