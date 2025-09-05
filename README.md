# Snake Game

A classic Snake game implementation built with C++ and the SFML library.

## Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Running](#running)
- [How to Play](#how-to-play)
- [Project Structure](#project-structure)

## Features

-   Classic snake gameplay: control a growing snake to eat food.
-   Main menu with options to start the game or exit.
-   Game state management (Main Menu, Game Play).
-   Dynamic asset loading for fonts and textures.

## Technologies Used

-   **C++20**
-   **SFML 3.x**: A simple and fast multimedia library.
-   **Make**: For building the project.

## Getting Started

Follow these instructions to get a copy of the project up and running on your local machine.

### Prerequisites

You will need the following software installed on your system:

-   A C++ compiler that supports C++20 (e.g., Clang, GCC).
-   `make`.
-   **SFML Library**: The project depends on SFML. On macOS, you can install it using Homebrew:
    ```sh
    brew install sfml
    ```

### Building

1.  Clone the repository:
    ```sh
    git clone https://github.com/Brxj19/Snake-Game.git
    cd Snake-game
    ```

2.  Compile the project using the provided Makefile:
    ```sh
    make
    ```
    This will compile the source files and create an executable in the `bin/` directory.

### Running

After a successful build, you can run the game with the following command:

```sh
./bin/game
```

## How to Play

-   Use the **Arrow Keys** or **W/A/S/D** keys to navigate the menus and control the snake.
-   In the main menu, use **Up/Down** to select an option and **Enter** to confirm.
-   In the game, guide the snake to eat the food that appears on the screen.
-   The game ends if the snake collides with the walls or with its own body.

## Project Structure

```
.
Snake-Game/
├── Makefile                 # Top-level build instructions
├── README.md                # Project overview (this file)
├── assets/                  # Game assets
│   ├── font/
│   │   └── DynaPuff-Regular.ttf
│   └── textures/
│       ├── food.png
│       ├── grass.png
│       ├── snake.png
│       └── wall.png
├── includes/                # Header files
│   ├── AssetManager.hpp
│   ├── Game.hpp
│   ├── GameOver.hpp
│   ├── GamePlay.hpp
│   ├── MainMenu.hpp
│   ├── PauseGame.hpp
│   ├── State.hpp
│   ├── Snake.hpp
│   └── StateManager.hpp
├── src/                     # Source files
│   ├── AssetManager.cpp
│   ├── Game.cpp
│   ├── GamePlay.cpp
│   ├── GameOver.cpp
│   ├── MainMenu.cpp
│   ├── PauseGame.cpp
│   ├── Snake.cpp
│   ├── StateManager.cpp
│   └── main.cpp             # Entry point
├── obj/                     # Compiled object files (build output)
└── bin/                     # Final executable
    └── game
