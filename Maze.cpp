#include <iostream>
#include <vector>
using namespace std;

#ifndef MAZE_H
#define MAZE_H

class Maze {
private:
    vector<vector<int>> grid;
public:
    Maze(const vector<vector<int>>& inputGrid) : grid(inputGrid) {}

    void display() {
        for (const auto& row : grid) {
            for (int cell : row) {
                switch (cell) {
                case 1: cout << "W"; break; // Wall
                case 2: cout << "S"; break; // Starting point
                case 3: cout << "E"; break; // Endpoint
                case 4: cout << "G"; break; // Goggles
                case 5: cout << "P"; break; // Speed potion
                case 6: cout << "F"; break; // Fog
                case 7: cout << "L"; break; // Slowpoke potion
                default: cout << "."; break; // Empty space
                }
            }
            cout << endl;
        }
    }
};

#endif // MAZE_H
