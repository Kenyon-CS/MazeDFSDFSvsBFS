#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

// Maze Class
class Maze {
public:
    // Function to generate a maze with boundaries ('=') and walls ('*')
    void generateMaze(vector<vector<char>>& mazemap) {
        // Initialize maze boundaries and walls
        for (int i = 0; i < mazemap.size(); ++i) {
            for (int j = 0; j < mazemap[0].size(); ++j) {
                if (i == 0 || i == mazemap.size() - 1 || j == 0 || j == mazemap[0].size() - 1) {
                    mazemap[i][j] = '='; // Boundary
                } else {
                    mazemap[i][j] = '*'; // Wall
                }
            }
        }

        // Create maze paths using DFS
        createMazePaths(mazemap, 1, 1);

        // Set the start 'S' and exit 'E' positions
        mazemap[1][1] = 'S'; // Start
        mazemap[mazemap.size() - 2][mazemap[0].size() - 2] = 'E'; // Exit
    }

    // Display the maze on the console
    void showMaze(const vector<vector<char>>& mazemap) {
        for (const auto& row : mazemap) {
            for (const char& cell : row) {
                cout << cell;
            }
            cout << endl;
        }
    }

    // Solve the maze using Depth-First Search (DFS)
    void solveMazeDFS(vector<vector<char>>& mazemap) {
        iterativeDFS(mazemap, 1, 1);
    }

    // Solve the maze using Breadth-First Search (BFS)
    void solveMazeBFS(vector<vector<char>>& mazemap) {
        iterativeBFS(mazemap, 1, 1);
    }

private:
// Function to print the map
void printPath(const map<std::pair<int, int>, pair<int, int>>& path) {
    for (const auto& entry : path) {
        // Access key and value pairs
        pair<int, int> key = entry.first;
        pair<int, int> value = entry.second;

        // Print the key and value
        cout << "Key: (" << key.first << ", " << key.second << ")"
                  << " -> Value: (" << value.first << ", " << value.second << ")\n";
    }
}

    // Iterative DFS using a stack
    void iterativeDFS(vector<vector<char>>& mazemap, int start_i, int start_j) {
        stack<pair<int, int>> stk;
        map<pair<int,int>, pair<int,int> > path;  // A map from a pair to it's previous node
        stk.push({start_i, start_j});
        int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        pair<int, int> prev, current = {start_i, start_j};

        while (!stk.empty()) {
            prev = current;
            current = stk.top();
            auto [i, j] = current;
            stk.pop();
            path[current]=prev;  // new node points to the previous node for path home
             
            // Skip visited cells or boundaries
            if (mazemap[i][j] == '=' || mazemap[i][j] == '*' || mazemap[i][j] == '.' ) continue;

            // If exit is found
            if (mazemap[i][j] == 'E') {
                printPath(path);
                // mark the path back to start
                /*for (pair loc={i,j}; (path.find(loc) != path.end()); loc=path[loc]){
                    auto [i, j] = loc;
                    cout << i << "," << j <<" : ";
                }*/
                    
                return;
            }
            // Mark current cell as visited
            mazemap[i][j] = '.';

            // Explore all four directions
            for (auto& direction : directions) {
                int new_i = i + direction[0];
                int new_j = j + direction[1];
                if (new_i >= 0 && new_i < mazemap.size() && new_j >= 0 && new_j < mazemap[0].size()) {
                    stk.push({new_i, new_j});
                }
            }
        }
    }

    // Iterative BFS using a queue
    void iterativeBFS(vector<vector<char>>& mazemap, int start_i, int start_j) {
        queue<pair<int, int>> q;
        q.push({start_i, start_j});
        int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            // Skip visited cells or boundaries
            if (mazemap[i][j] == '=' || mazemap[i][j] == '*' || mazemap[i][j] == '.' || mazemap[i][j] == '%') continue;

            // If exit is found
            if (mazemap[i][j] == 'E') return;

            // Mark current cell as visited
            mazemap[i][j] = '.';

            // Explore all four directions
            for (auto& direction : directions) {
                int new_i = i + direction[0];
                int new_j = j + direction[1];
                if (new_i >= 0 && new_i < mazemap.size() && new_j >= 0 && new_j < mazemap[0].size()) {
                    q.push({new_i, new_j});
                }
            }
        }
    }

    // DFS to create random paths in the maze
    void createMazePaths(vector<vector<char>>& mazemap, int i, int j) {

        
        random_device rd;  // Seed for the random number generator
        mt19937 g(rd());   // Standard mersenne_twister_engine seeded with rd()
        
        int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        int visitOrder[] = {0, 1, 2, 3};

        if (mazemap[i][j] == '=') return; // Boundary check
        if (mazemap[i][j] == ' ') return; // Already visited

        // Check to avoid loops by ensuring minimal visited neighbors
        if (countVisitedNeighbors(mazemap, i, j) > 1) return;

        mazemap[i][j] = ' '; // Mark as visited (path)

        // Shuffle directions to randomize maze generation
        shuffle(visitOrder, visitOrder + 4, g);

        for (int k = 0; k < 4; ++k) {
            int new_i = i + directions[visitOrder[k]][0];
            int new_j = j + directions[visitOrder[k]][1];
            createMazePaths(mazemap, new_i, new_j);
        }
    }

    // Count the number of visited neighbors of a cell
    int countVisitedNeighbors(const vector<vector<char>>& mazemap, int i, int j) {
        int directions[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int count = 0;
        for (auto& direction : directions) {
            int new_i = i + direction[0];
            int new_j = j + direction[1];
            if (new_i >= 0 && new_i < mazemap.size() && new_j >= 0 && new_j < mazemap[0].size()) {
                if (mazemap[new_i][new_j] == ' ') count++;
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
    vector<vector<char>> mazemap(height + 2, vector<char>(width + 2));
    vector<vector<char>> mazemap2;
    
    // Generate 2 identical mazes
    maze.generateMaze(mazemap);
    mazemap2=mazemap;

    // Display the maze
    maze.showMaze(mazemap);

    // Solve the maze using BFS (or DFS if preferred)
    maze.solveMazeBFS(mazemap);

    // Display the solved maze
    cout << "BFS Solution\n";;
    maze.showMaze(mazemap);

    // Solve the maze2 using DFS
    maze.solveMazeDFS(mazemap2);

    // Display the solved maze
    cout << "DFS Solution\n";;
    maze.showMaze(mazemap2);
    return 0;
}
