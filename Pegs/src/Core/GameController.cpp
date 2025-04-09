#include <iostream>
#include <thread>

#include "Board/Board.hpp"
#include "Board/BoardHelper.hpp"

#include "Core/Clock.hpp"
#include "Core/IBot.hpp"
#include "Core/GameController.hpp"
#include "Core/Renderer.hpp"

void GameController::StartGame(IBot& whiteBot, IBot& blackBot, Board& board, const long long startingSeconds)
{
    int moveCount = 1;

    this->board = &board;
    clock.Start(startingSeconds * 1000, board.turn == Piece::white);

    sf::RenderWindow window(sf::VideoMode({ 256, 384 }), "SFML works!");
    std::thread thread(Renderer::newThread, std::ref(window));
    Renderer::updateBoard(board, window);

    while (board.GetGameResult() == GameResult::inProgress)
    {
        Move move;

        if (board.turn == Piece::white)
        {
            move = MakeMove(whiteBot);

            if (!move.IsEmpty())
            {
                std::cout << moveCount++ << ". " << ToNotation(move.GetStartSquare(), move.GetTargetSquare(), move.GetCapture()) << std::endl;
            }
            else break;
        }

        if (board.GetGameResult() != GameResult::inProgress) break;

        if (board.turn == Piece::black)
        {
            move = MakeMove(blackBot);

            if (!move.IsEmpty())
            {
                std::cout << moveCount++ << ". " << ToNotation(move.GetStartSquare(), move.GetTargetSquare(), move.GetCapture()) << std::endl;
            }
            else break;
        }

        if (board.GetGameResult() != GameResult::inProgress) break;
    }

    GameResult result = board.GetGameResult();
    if (result == GameResult::whiteWin || result == GameResult::blackWin)
        std::cout << "#\n";

    else if (result == GameResult::inProgress) result = board.turn == Piece::white ? GameResult::blackWin : GameResult::whiteWin;

    std::cout << std::endl << GetResultString(result);
}

Move GameController::MakeMove(IBot& bot)
{
    Board botBoard(*board);
    Move move = bot.Think(botBoard, clock.GetWhiteTimer());

    if (!IsLegalMove(move))
    {
        std::cout << "Bot tried to play an illegal move! Stopping game...\n";
        std::cout << "Attempted move: " << ToNotation(move.GetStartSquare(), move.GetTargetSquare(), move.GetCapture()) << std::endl;
        return Move();
    }

    clock.Turn();

    // Time is only checked after the bot has thought. This is to keep everything on one thread
    if (!clock.isWhiteToMove ? clock.WhiteMillisecondsRemaining == 0 : clock.BlackMillisecondsRemaining == 0)
    {
        std::cout << "Bot ran out of time! Stopping game...\n";
        return Move();
    }

    board->MakeMove(move);

    return move;
}

bool GameController::IsLegalMove(Move move) const
{
    bool isWhiteToMove = board->turn == Piece::white;
    const uint64_t friendlyPieces = board->bitboards[!isWhiteToMove];
    const uint64_t enemyPieces = board->bitboards[isWhiteToMove];
    const uint64_t pieces = board->bitboards[2];
    const uint64_t legalMask = ~pieces;
    
    int startSquare = move.GetStartSquare();
    int targetSquare = move.GetTargetSquare();
    int captureSquare = move.GetCapture();
    int direction = move.GetDirection();
    int absDir = std::abs(direction);

    // Check if the starting square is in the board
    if (!ValidSquare(FileIndex(startSquare) - 1, RankIndex(startSquare) - 1))
    {
        return false;
    }

    // Check if the square to move to is in the board
    if (!ValidSquare(FileIndex(targetSquare) - 1, RankIndex(targetSquare) - 1))
    {
        return false;
    }


    // Check if starting square is a friendly piece
    if (!SquareIsSet(friendlyPieces, startSquare))
        return false;

    // Check if square to move to is not occupied
    if (SquareIsSet(pieces, targetSquare))
        return false;

    // Check if capture square matches
    if (captureSquare != 0)
    {
        if ((startSquare + targetSquare) / 2 != captureSquare || !SquareIsSet(enemyPieces, captureSquare))
            return false;

        if (std::abs(RankIndex(targetSquare) - RankIndex(startSquare)) != 2 || std::abs(FileIndex(targetSquare) - FileIndex(startSquare)) != 2)
            return false;
    }
    else
    {
        // Check if move is a legal move
        if (absDir != 1 && direction != 4 * board->turn)
        {
            // Check if move is a legal skipping move
            if (SquareIsSet(pieces, startSquare + 4 / board->turn))
            {
                if (direction == 3 * board->turn || direction == 5 * board->turn)
                {
                    if (RankIndex(targetSquare) - RankIndex(startSquare) == board->turn)
                        return true;
                }
            }
            return false;
        }
    }

    return true;
}

std::string GameController::ToNotation(int startSquare, int targetSquare, int captureSquare)
{
    constexpr char fileSuffix[4] = { 'a', 'b', 'c', 'd' };
    std::string algebraic = fileSuffix[FileIndex(startSquare) - 1] + std::to_string(RankIndex(startSquare))
        + fileSuffix[FileIndex(targetSquare) - 1] + std::to_string(RankIndex(targetSquare));
    if (captureSquare != 0) algebraic += "+";

    return algebraic;
}

std::string GameController::GetResultString(GameResult result)
{
    switch (result)
    {
    case GameResult::whiteWin:
        return "White won";
    case GameResult::blackWin:
        return "Black won";
    case GameResult::draw:
        return "Draw";
    default:
        return "inProgress";
    }
}

