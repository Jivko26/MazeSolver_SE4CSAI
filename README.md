# Maze-Solving Agent in C++

## Project Overview

This project involves the development of an autonomous agent that solves mazes in C++. It reads a maze from a text file and uses a Depth-First Search (DFS) algorithm to find a path from the start to the endpoint, considering walls, paths, and various objects that influence the agent's movement capabilities.

## Features

    Maze Parsing: Reads and interprets a maze from a text file.
    Dynamic Agent: An agent with adjustable perceptiveField and stepWidth.
    DFS Algorithm: Modified DFS algorithm for pathfinding that accounts for the dynamic capabilities of the agent.
    Interaction with Objects: The agent interacts with objects in the maze that alter its movement and perception.
## How to Run

Ensure you have a C++ compiler installed. Compile the project using: g++ -o maze_solver main.cpp Agent.cpp Maze.cpp -std=c++11
Run the program: ./maze_solver

## Maze File Format

The maze is represented in a text file as a 2D grid:

    0: Empty space
    1: Wall
    2: Starting point
    3: Endpoint
    4: Goggles (increase perceptive field)
    5: Speed potion (increase step width)
    6: Fog (decrease perceptive field)
    7: Slowpoke potion (decrease step width)
    
Example: 
2 0 1 0
1 0 0 0
0 1 1 3

## Implementation Details

    Maze Representation: The maze is stored as a 2D vector.
    Agent: The agent moves through the maze based on the DFS algorithm.
    DFS Algorithm: Custom implementation to accommodate the agent's changing properties.

## Future Enhancements

    Optimization of the DFS algorithm for larger mazes.
    Improved handling of complex maze structures.
    Enhanced decision-making for the agent based on more advanced AI techniques.

## License
MIT

  
