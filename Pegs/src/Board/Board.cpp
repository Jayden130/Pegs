#include <iostream>
#include <random>
#include "Board/BoardHelper.hpp"
#include "Board/Board.hpp"
#include "Board/Zobrist.hpp"

Board::Board(Board& board)
{
	for (int i = 0; i < 3; i++)
	{
		bitboards[i] = board.bitboards[i];
	}
	turn = board.turn;
	twentymoveCounter = board.twentymoveCounter;
	zobristKey = board.zobristKey;
	repetitionPositionHistory = board.repetitionPositionHistory;
}

Board::Board(std::string fen)
{
	if (fen.length() == 0)
	{
		std::cerr << "Error creating fen position. \n";
		return;
	}

	int row = 0;
	int column = 0;
	for (int i = 0; i < fen.length(); i++)
	{
		char symbol = fen[i];

		if (i == 0)
		{
			if (symbol == 'w')
				turn = Piece::white;
			else turn = Piece::black;

			continue;
		}

		switch (symbol)
		{
		case '/':
			row++;
			column = 0;
			continue;

		case 'w':
			bitboards[0] |= 1ull << (row * 4 + column);
			bitboards[2] |= 1ull << (row * 4 + column);
			column++;
			continue;
		case 'b':
			bitboards[1] |= 1ull << (row * 4 + column);
			bitboards[2] |= 1ull << (row * 4 + column);
			column++;
			continue;
		
		default:
			if (isdigit(symbol))
			{
				column += symbol - '0';
			}
			continue;
		}
	}

	Zobrist::Init();
	zobristKey = Zobrist::CalculateZobristKey(*this);
}

void Board::MakeMove(Move move)
{
	// Get info about move
	int startSquare = move.GetStartSquare();
	int targetSquare = move.GetTargetSquare();
	int captureSquare = move.GetCapture();
	int direction = move.GetDirection();

	if (turn == Piece::white)
	{
		ToggleSquares(bitboards[0], startSquare, targetSquare);

		if (captureSquare != 0)
		{
			ClearSquare(bitboards[1], captureSquare);
			zobristKey ^= Zobrist::GetPiecesArray()[1][captureSquare];
		}
	}

	else
	{
		ToggleSquares(bitboards[1], startSquare, targetSquare);

		if (captureSquare != 0)
		{
			ClearSquare(bitboards[0], captureSquare);
			zobristKey ^= Zobrist::GetPiecesArray()[0][captureSquare];
		}
	}
	
	zobristKey ^= Zobrist::GetPiecesArray()[turn == Piece::white ? 0 : 1][startSquare];
	zobristKey ^= Zobrist::GetPiecesArray()[turn == Piece::white ? 0 : 1][targetSquare];

	if (captureSquare || direction > 2 || direction < -2)
	{
		repetitionPositionHistory.clear();
		twentymoveCounter = 0;
	}
	else
	{
		repetitionPositionHistory.emplace_back(zobristKey);
		twentymoveCounter++;
	}

	bitboards[2] = bitboards[0] | bitboards[1];
	Turn();
}

void Board::UndoMove(Move move)
{
	// Get info about move
	int startSquare = move.GetStartSquare();
	int targetSquare = move.GetTargetSquare();
	int captureSquare = move.GetCapture();
	int direction = move.GetDirection();

	if (turn == Piece::black)
	{
		ToggleSquares(bitboards[0], startSquare, targetSquare);

		if (captureSquare != 0)
		{
			SetSquare(bitboards[1], captureSquare);
			zobristKey ^= Zobrist::GetPiecesArray()[1][captureSquare];
		}
	}

	else
	{
		ToggleSquares(bitboards[1], startSquare, targetSquare);

		if (captureSquare != 0)
		{
			SetSquare(bitboards[0], captureSquare);
			zobristKey ^= Zobrist::GetPiecesArray()[0][captureSquare];
		}
	}

	if (repetitionPositionHistory.size() > 0)
		repetitionPositionHistory.pop_back();

	zobristKey ^= Zobrist::GetPiecesArray()[turn == Piece::white ? 1 : 0][startSquare];
	zobristKey ^= Zobrist::GetPiecesArray()[turn == Piece::white ? 1 : 0][targetSquare];

	bitboards[2] = bitboards[0] | bitboards[1];
	Turn();
}

void Board::Turn()
{
	if (turn == Piece::white)
		turn = Piece::black;
	else turn = Piece::white;

	zobristKey ^= Zobrist::GetSideToMove();
}

GameResult Board::GetGameResult()
{
	if ((Rank1 & bitboards[1]) != 0)
	{
		return GameResult::blackWin;
	}

	if ((Rank6 & bitboards[0]) != 0)
	{
		return GameResult::whiteWin;
	}

	// check for repetition
	int repCount = std::count(repetitionPositionHistory.begin(), repetitionPositionHistory.end(), zobristKey);
	if (repCount >= 3)
		return GameResult::draw;

	// check for 20 move rule
	if (twentymoveCounter >= 20)
		return GameResult::draw;

	return GameResult::inProgress;
}

uint64_t Board::GetZobristKey() const
{
	return zobristKey;
}
