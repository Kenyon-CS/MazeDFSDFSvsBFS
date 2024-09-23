#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Maze Class
class Maze {
public:
    // Function to generate a maze with boundaries ('=') and walls ('*')
    void generateMaze(vector<vector<char>>& map) {
        // Initialize maze boundaries and walls
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                if (i == 0 || i == map.size() - 1 || j == 0 || j == map[0].size() - 1) {
                    map[i][j] = '='; // Boundary
                } else {
                    map[i][j] = '*'; // Wall
                }
            }
        }

        // Create maze paths using DFS
        createMazePaths(map, 1, 1);

        // Set the start 'S' and exit 'E' positions
        map[1][1] = 'S'; // Start
        map[map.size() - 2][map[0].size() - 2] = 'E'; // Exit
    }

    // Display the maze on the console
    void showMaze(const vector<vector<char>>& map) {
        for (const auto& row : map) {
            for (const char& cell : row) {
                cout << cell;
            }
            cout << endl;
        }
    }

    // Solve the maze using Depth-First Search (DFS)
    void solveMazeDFS(vector<vector<char>>& map) {
        bool success = iterativeDFS(map, 1, 1);
        if (!success) {
            cout << "No solution to maze!" << endl;
        }
    }

    // Solve the maze using Breadth-First Search (BFS)
    void solveMazeBFS(vector<vector<char>>& map) {
        bool success = iterativeBFS(map, 1, 1);
        if (!success) {
            cout << "No solution to maze!" << endl;
        }
    }

private:
    // Iterative DFS using a stack
    bool iterativeDFS(vector<vector<char>>& map, int start_i, int start_j) {
        stack<pair<int, int>> stk;
        stk.push({start_i, start_j});
        int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

        while (!stk.empty()) {
            auto [i, j] = stk.top();
            stk.pop();

            // Skip visited cells or boundaries
            if (map[i][j] == '=' || map[i][j] == '*' || map[i][j] == '.' || map[i][j] == '%') continue;

            // If exit is found
            if (map[i][j] == 'E') return true;

            // Mark current cell as visited
            map[i][j] = '.';

            // Explore all four directions
            for (auto& direction : directions) {
                int new_i = i + direction[0];
                int new_j = j + direction[1];
                if (new_i >= 0 && new_i < map.size() && new_j >= 0 && new_j < map[0].size()) {
                    stk.push({new_i, new_j});
                }
            }
        }

        return false;
    }

    // Iterative BFS using a queue
    bool iterativeBFS(vector<vector<char>>& map, int start_i, int start_j) {
        queue<pair<int, int>> q;
        q.push({start_i, start_j});
        int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            // Skip visited cells or boundaries
            if (map[i][j] == '=' || map[i][j] == '*' || map[i][j] == '.' || map[i][j] == '%') continue;

            // If exit is found
            if (map[i][j] == 'E') return true;

            // Mark current cell as visited
            map[i][j] = '.';

            // Explore all four directions
            for (auto& direction : directions) {
                int new_i = i + direction[0];
                int new_j = j + direction[1];
                if (new_i >= 0 && new_i < map.size() && new_j >= 0 && new_j < map[0].size()) {
                    q.push({new_i, new_j});
                }
            }
        }

        return false;
    }

    // DFS to create random paths in the maze
    void createMazePaths(vector<vector<char>>& map, int i, int j) {
        int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        int visitOrder[] = {0, 1, 2, 3};

        if (map[i][j] == '=') return; // Boundary check
        if (map[i][j] == ' ') return; // Already visited

        // Check to avoid loops by ensuring minimal visited neighbors
        if (countVisitedNeighbors(map, i, j) > 1) return;

        map[i][j] = ' '; // Mark as visited (path)

        // Shuffle directions to randomize maze generation
        random_shuffle(visitOrder, visitOrder + 4);

        for (int k = 0; k < 4; ++k) {
            int new_i = i + directions[visitOrder[k]][0];
            int new_j = j + directions[visitOrder[k]][1];
            createMazePaths(map, new_i, new_j);
        }
    }

    // Count the number of visited neighbors of a cell
    int countVisitedNeighbors(const vector<vector<char>>& map, int i, int j) {
        int directions[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int count = 0;
        for (auto& direction : directions) {
            int new_i = i + direction[0];
            int new_j = j + direction[1];
            if (new_i >= 0 && new_i < map.size() && new_j >= 0 && new_j < map[0].size()) {
                if (map[new_i][new_j] == ' ') count++;
            }
        }
        return count;
    }
};

// Main function to run the maze generation and solving
int main() {
    Maze maze;
    int height = 30;
    int width = 60;

    // Seed random number generator
    srand(time(0));

    // Create an empty maze grid with borders
    vector<vector<char>> map(height + 2, vector<char>(width + 2));

    // Generate and display the maze
    maze.generateMaze(map);
    maze.showMaze(map);

    // Solve the maze using BFS (or DFS if preferred)
    maze.solveMazeBFS(map);

    // Display the solved maze
    cout << "BFS Solution\n";;
    maze.showMaze(map);

    // Solve the maze using DFS
    maze.solveMazeDFS(map);

    // Display the solved maze
    cout << "DFS Solution\n";;
    maze.showMaze(map);
    return 0;
}
