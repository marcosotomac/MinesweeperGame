# MinesweeperGame

This is a C++ implementation of the classic **Minesweeper** game, designed as a project for a programming course. The game is a puzzle where players aim to clear a grid of cells without triggering any hidden mines.

## Features

- **Play the classic Minesweeper game**: Select cells to reveal their contents.
- **Clear the board**: Avoid hidden mines by using logic to deduce safe spots.
- **Win or lose based on game rules**.

## Files

- `Celda.cpp` / `Celda.h`: Defines the cell structure of the grid.
- `Historial.cpp` / `Historial.h`: Handles game history and moves.
- `JuegoBuscaminas.cpp` / `JuegoBuscaminas.h`: Implements the logic for playing the game.
- `Tablero.cpp` / `Tablero.h`: Represents the game board and its operations.
- `Jugador.h`: Contains player details and score tracking.
- `main.cpp`: Entry point of the program, where the game loop runs.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/marcosotomac/MinesweeperGame.git
    ```
2. Navigate to the project directory:
    ```bash
    cd MinesweeperGame
    ```
3. Compile the program:
    ```bash
    g++ main.cpp -o MinesweeperGame
    ```
4. Run the game:
    ```bash
    ./MinesweeperGame
    ```

## How to Play

- The game presents a grid where some cells contain hidden mines.
- Use the number clues to deduce which cells are safe to open.
- A mine is triggered if you open a cell containing it, and the game is lost.

Feel free to adjust the content based on any additional details you would like to include!
