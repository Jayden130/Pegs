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

# How to Start
