#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;


enum Direction { UP, DOWN, LEFT, RIGHT };


class Agent {
private:
	int x, y;
	int mazeHeight;
	int mazeWidth;
	Direction currentDirection;
	int perceptiveField;
	int stepWidth;
	int score;
	vector<vector<bool>> visited;
	vector<pair<int, int>> path;

public:
	Agent(int startX, int startY, int mazeHeight, int mazeWidth) :
		x(startX),
		y(startY),
		mazeHeight(mazeHeight),
		mazeWidth(mazeWidth),
		currentDirection(RIGHT),
		perceptiveField(1),
		stepWidth(1),
		score(0)
	{
		visited.resize(mazeHeight, vector<bool>(mazeWidth, false));
	}


	bool dfs(int x, int y, const vector<vector<int>>& maze) {
		if (x < 0 || x >= maze.size() || y < 0 || y >= maze[0].size() || visited[x][y] || maze[x][y] == 1) {
			return false;
		}

		visited[x][y] = true;
		path.push_back({ x, y }); // Add to path

		interactWithObject(maze[x][y]);

		
		if (maze[x][y] == 1) {
			return false; // Wall
		}
		if (maze[x][y] == 3) { // Check for goal
			return true;
		}


		//// Calculate next positions based on stepWidth
		//vector<pair<int, int>> nextPositions = {
		//{x - stepWidth, y}, // Up
		//{x + stepWidth, y}, // Down
		//{x, y - stepWidth}, // Left
		//{x, y + stepWidth}  // Right
		//};

		//// Explore adjacent cells based on stepWidth
		//for (auto& pos : nextPositions) {
		//	if (dfs(pos.first, pos.second, maze)) {
		//		return true;
		//	}
		//}

		if (dfs(x - stepWidth, y, maze) || dfs(x, y + stepWidth, maze) || dfs(x + stepWidth, y, maze) || dfs(x, y - stepWidth, maze)) {
			return true;
		}

		path.pop_back(); // Remove from path if it leads to dead end
		return false;
	}


	bool findPath(const vector<vector<int>>& maze) {
		return dfs(x, y, maze);
	}

	void printPath() const {
		for (const auto& p : path) {
			cout << "(" << p.first << ", " << p.second << ") ";
		}
		cout << endl;
	}

	void autonomousMove(const vector<vector<int>>& maze) {
		int newX = x, newY = y;

		switch (currentDirection) {
		case UP:    newX--; break;
		case DOWN:  newX++; break;
		case LEFT:  newY--; break;
		case RIGHT: newY++; break;
		}

		bool firstCheck = newX >= 0 && newX < maze.size();
		bool secondCheck = newY >= 0 && newY < maze[0].size();
		bool thirdCheck = maze[newX][newY] != 1;

		if (firstCheck && secondCheck && thirdCheck) {
			move(currentDirection, maze);
		}
		else {
			turnRight();
		}
	}

	void interactWithObject(int object) {
		cout << "Interacted with: " << object << endl;

		switch (object) {
		case 4: // Goggles
			perceptiveField = min(perceptiveField + 1, 3);
			break;
		case 5: // Speed potion
			stepWidth = min(stepWidth + 1, 3);
			break;
		case 6: // Fog
			perceptiveField = max(perceptiveField - 1, 1);
			break;
		case 7: // Slowpoke potion
			stepWidth = std::max(stepWidth - 1, 1);
			break;
			// Other cases
		}
	}

	tuple<int, int> getPosition() const {
		return std::make_pair(x, y);
	}

	int getScore() {
		return score;
	}

	void turnLeft() {
		switch (currentDirection) {
		case UP:    currentDirection = LEFT; break;
		case DOWN:  currentDirection = RIGHT; break;
		case LEFT:  currentDirection = DOWN; break;
		case RIGHT: currentDirection = UP; break;
		}
	}

	void turnRight() {
		switch (currentDirection) {
		case UP:    currentDirection = RIGHT; break;
		case DOWN:  currentDirection = LEFT; break;
		case LEFT:  currentDirection = UP; break;
		case RIGHT: currentDirection = DOWN; break;
		}
	}
	void move(Direction direction, const vector<vector<int>>& maze) {
		int newX = x, newY = y;

		switch (direction) {
		case UP: newX -= stepWidth; break; // Up
		case DOWN: newX += stepWidth; break; // Down
		case LEFT: newY -= stepWidth; break; // Left
		case RIGHT: newY += stepWidth; break; // Right
		}

		// Check for wall collision and bounds
		if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze[0].size() && maze[newX][newY] != 1) {
			x = newX;
			y = newY;

			interactWithObject(maze[x][y]);
			score++;

			logPosition();
			cout << "Agent's currennt direction: " << currentDirection << endl;
		}
		else {
			cout << "Collision: Unable to move in the specified direction." << endl;
		}
	}

	void logPosition() {
		cout << "Agent's current position: (" << x << ", " << y << ")" << endl;
	}
};
