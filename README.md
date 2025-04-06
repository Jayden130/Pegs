# Pegs Bot Library (C++)
This library contains all necessary components to make a Pegs bot.

# What is Pegs?
Pegs is a 2 player game similar to Chess and Checkers. The goal is to get one of your Pegs to the other side of the board.
The board is a 4x6 grid and each opponent starts with 8 pegs.

![image](https://github.com/user-attachments/assets/e9edc669-8991-4958-a794-e2b397cdb228)

# Gameplay Rules
White always begins first.

- **Move rules**
  - A peg can move up, left and right freely, as long as there is nothing in the way, like a wall or other peg.
  - A peg can 'skip' if a peg of any color is in front of it. A skipping move is where you move up-left or up-right from the starting position.
  - A peg can capture a peg of the opponent by jumping over it diagonally. This can be in any of the four possible directions.

- **Ending the game**
  - The game has ended when a player gets a peg to the other side of the board. That player wins.
  - The game is a draw if the same position is repeated thrice, or if a player has no moves.

- **Move notation**
  - A written down move is similar to the chess [Algebraic notation](https://www.chess.com/terms/chess-notation).
  - The notation shows you where the piece to move is, where you want to move it and if it is a capture, or a winning move.
    - The file the peg is in, is written down as a letter (file 1 = a, file 2 = b, etc).
    - The rank the peg is in, is written down as a number (rank 1 = 1, rank 2 = 2, etc). This is written down after the file.
    - If the peg captures another peg, you add a '+' at the end.
    - If the move gets the peg to the other side of the board, you add # to the end, concluding the game.

  - The notation starts with where the peg is (example: a2), then it says where the peg is going to move (example: c4). If it is a capture, you add a '+' at the end (example: a2c4+).

# Getting Started
- Install an IDE, such as [Visual Studio](https://visualstudio.microsoft.com/downloads/)
- Install Visual C++ on your IDE.
- Download this repository and open the project.
- Open MyBot.cpp and write some code!
  - You might want to look at the Documentation below first, and the Gameplay Rules too!
  - **Bots are not supposed to use multithreading or parallelism.**
- Build and run the project to test your changes.
  - For testing, you have two options:
    - You can play the bot against yourself (HumanBot vs MyBot).
    - It can play a match against itself (MyBot vs MyBot).

# Documentation

## MyBot (class)
| Type | Definition | Notes |
| --- | --- | --- |
| Move | Think(Board board, Timer timer) | This is the function you need to implement for your bot. |


## Board (class)
| Type | Definition | Notes |
| --- | --- | --- |
| void | MakeMove(Move move) | Updates the board state with the given move. The move is assumed to be legal, and may result in errors if it is not. Note that this doesn't make the move in the actual game, it just allows you to look ahead at future possibilities. The move can be undone with the UndoMove(Move move) method.|
| void | UndoMove(Move move) | Undo a move that was made with the MakeMove method. Moves must be undone in reverse order, so for example, if moves A, B, C are made, they must be undone in the order C, B, A. |
| void | Turn() | Give the move to the other side. |
| GameResult | GetGameResult() | Returns the current result of the game. Returns `inProgress` if the game does not have a result. |
| Piece | turn | Who's turn it is to make a move on the board. |
| uint64_t | GetZobristKey() | Returns the zobrist key. This is a 64-bit hash of the current position. Learn more about this [here](https://www.chessprogramming.org/Zobrist_Hashing). |
| uint64_t\[3] | bitboards | array of 64-bit numbers where each bit set to 1 represents a square that contains a peg of the given color. 0 = white bitboard, 1 = black bitboard, 2 = all pieces bitboard. |
| vector\<uint64_t> | repetitionPositionHistory | Zobrist keys for all the positions played in the game so far. This is reset whenever a push move, skipping move or capture move is made, as previous positions are now impossible to reach again. |

## Move (struct)
| Type | Definition | Notes |
| --- | --- | --- |
| Move | Move(int startSquare, int targetSquare, int capture = 0) | Constructor for creating a move by its starting position index, target position index and, if relevant, a capture position index. |
| Move | Move(int value) | Constructor for creating a move by its move value. |
| unsigned short | moveValue | Compact (16bit) move representation to preserve memory. The format is as follows: (fffffftttttsssss). Bits 0-5: start square index. Bits 6-10: target square index. Bits 11-15: capture index |
| int | GetStartSquare() | Returns the starting square of the move. |
| int | GetTargetSquare() | Returns the target square of the move. |
| int | GetCapture() | Returns the capture square of the move. |
| int | GetDirection() | Returns the offset of the starting square and the target square. |
| bool | IsEmpty() | Returns true if the moveValue is 0. |

## Piece (enum)
| Type | Definition | Notes |
| --- | --- | --- |
| Piece | black | Value of -1. Represents a black piece. |
| none | black | Value of 0. Represents no piece. |
| white | black | Value of 1. Represents a white piece. |


