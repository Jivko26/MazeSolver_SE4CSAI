
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>
#include "Maze.cpp"
#include "Agent.cpp"

using namespace std;

struct Position {
    int x;
    int y;
};

pair<Position, Position> findStartAndEnd(const vector<vector<int>>& maze) {
    Position startPos, endPos;
    bool startFound = false, endFound = false;

    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 2) {
                startPos = { i, j };
                startFound = true;
            }
            else if (maze[i][j] == 3) {
                endPos = { i, j };
                endFound = true;
            }

            if (startFound && endFound) {
                break;
            }
        }
        if (startFound && endFound) {
            break;
        }
    }

    if (!startFound || !endFound) {
        throw runtime_error("Start or end position not found in the maze.");
    }

    return { startPos, endPos };
}

vector<vector<int>> readMazeFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> maze;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int value;

        while (ss >> value) {
            row.push_back(value);
        }

        maze.push_back(row);
    }

    return maze;
}

bool isGameOver(const Agent& agent, const vector<vector<int>>& maze) {
    int x, y;
    tie(x, y) = agent.getPosition();

    if (maze[x][y] == 3) {
        cout << "Goal reached!" << endl;
        return true;
    }

    return false;
}


int main() {
    string filename = "maze_prod.txt"; 

    vector<vector<int>> mazeGrid = readMazeFromFile(filename); 

    Maze maze(mazeGrid);
    
    cout << "Initial Maze Configuration:" << endl; 
    maze.display();

    Position startPos, endPos;
    int mazeHeight = mazeGrid.size();
    int mazeWidth = mazeGrid[0].size();
    try {
        tie(startPos, endPos) = findStartAndEnd(mazeGrid);
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    Agent agent(startPos.x, startPos.y, mazeHeight, mazeWidth);

    if (agent.findPath(mazeGrid)) {
        cout << "Path found:" << endl;
        agent.printPath();

    }
    else {
        cout << "No path found." << endl;
    }

 /*   cout << "Agent's initial position: (" << startPos.x << ", " << startPos.y << ")" << endl;

    bool gameOver = false;

    while (!gameOver)
    {
        agent.autonomousMove(mazeGrid);
        gameOver = isGameOver(agent, mazeGrid);
    }
    cout << "Score: " << agent.getScore() << endl;*/

    /*Initial Maze Configuration :
    S...WW.W.W.W.W.W.W.WW
        W..W.W.W.W.W.W.W.W.WW
        WW...P...F...W......W
        WW.WLW.W.W.W.WGW.W.W.
        WWPW.W.W.W.W.W.W.W.W.
        WW.W.W.W.W.W.W.W.W.W.
        WW.W...W...W...W...W.
        WW.W.WWWWWWWWWWWWWWW.
        WW.W.W...W.........W.
        WWFW.W.W.W.W.W.W.W.W.
        WW.W.W.W...W.W...W.W.
        WW.W.WLWWWWW.WWWWWWW.
        WW.W.W.W.....F.....W.
        WW.W.W.W.W.W.W.W.W.W.
        WW.WFW.W.W.W.W.W.W.W.
        WW.W.W.WPW.W.W.WLW.W.
        WW.W.P.W.W.W.W.W.W.W.
        WW.W.W.W...W.......W.
        W....W.W.W.W.W.W.W.WW
        WWW......WWWWWWWW...E
        .WW..WWWWW.........WW
        Path found :
    (0, 0) (0, 1) (0, 2) (1, 2) (2, 2) (2, 3) (2, 4) (2, 5) (2, 6) (3, 6) (4, 6) (5, 6) (6, 6) (6, 5) (6, 4) (7, 4) (8, 4) (9, 4) (10, 4) (11, 4) (12, 4) (13, 4) (14, 4) (15, 4) (16, 4) (16, 5) (16, 6) (15, 6) (14, 6) (13, 6) (12, 6) (11, 6) (10, 6) (9, 6) (8, 6) (8, 7) (8, 8) (9, 8) (10, 8) (10, 9) (10, 10) (9, 10) (8, 10) (8, 11) (8, 12) (9, 12) (10, 12) (11, 12) (12, 12) (12, 13) (12, 14) (12, 15) (12, 16) (12, 17) (12, 18) (13, 18) (14, 18) (15, 18) (16, 18) (17, 18) (18, 18) (19, 18) (19, 19) (19, 20)*/

}

