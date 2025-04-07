#include <iostream>

#include "Board/Board.hpp"
#include "Core/Timer.hpp"

#include "My Bot/MyBot.hpp"
#include "Human Bot/HumanBot.hpp"

#include "Core/GameController.hpp"

int main()
{
    std::cout << "Fen: ";
    std::string fen;
    std::getline(std::cin, fen);

    if (fen.length() == 0)
    {
        fen = "w wwww/wwww/4/4/bbbb/bbbb";
    }
    Board board(fen);
    
    MyBot whiteBot;
    MyBot blackBot;

    GameController controller;

    std::cout << "Game starting with fen: " << fen.c_str() << std::endl;
    controller.StartGame(whiteBot, blackBot, board, 60);

    return 0;
}