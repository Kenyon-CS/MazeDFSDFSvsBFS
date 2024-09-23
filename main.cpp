#include "string"
#include "vector"
#include "unordered_map"
#include "queue"
#include "cstdlib"
#include "ctime"
#include <iostream>
#include "algorithm"
#include "stack"
using namespace std;

class Maze{
public:
  // Definition for Maze.
    void maze(vector<vector<char> >& map){
        //U unvisited, ' ' visited
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                if (i == 0 ||  i == map.size()-1 || j == 0 ||  j == map[0].size()-1) {
                	map[i][j] = '=';
                } else {
            		map[i][j] = '*';
                }
            }
        }
        _maze(map, 1, 1);
        map[1][1] = 'S';
        map[map.size()-2][map[0].size()-2] = 'E';
    }

    void showMaze(vector<vector<char> >& map){
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                cout<<map[i][j];
            }
            cout<<endl;
        }
    }
    
    void solveMaze(vector<vector<char> >& map){
		bool success = iterativeDFS(map,1,1);
		if (!success) {
			cout << "No solution to maze!";
		}
    }
    
    // Iterative DFS using a stack
bool iterativeDFS(vector<vector<char> >& map, int start_i, int start_j)
{
    int direct[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    stack<pair<int, int>> stk;

    // Push the starting point onto the stack
    stk.push({start_i, start_j});

    while (!stk.empty()) {
        // Get current position
        pair<int, int> curr = stk.top();
        stk.pop();

        int i = curr.first;
        int j = curr.second;

        // Check if hit edge, a wall, or a visited cell
        if (map[i][j] == '=' || map[i][j] == '*' || map[i][j] == '.' || map[i][j] == '%') continue;

        // Check if we have reached the exit 'E'
        if (map[i][j] == 'E') return true;

        // Mark the current position as visited
        map[i][j] = '.';

        // Explore all four directions
        for (int k = 0; k < 4; ++k) {
            int newi = i + direct[k][0];
            int newj = j + direct[k][1];

            // If the new position is within bounds, push it onto the stack
            if (newi >= 0 && newi < map.size() && newj >= 0 && newj < map[0].size()) {
                stk.push({newi, newj});
            }
        }

        // Mark the path with '%' to indicate breadcrumbs
        map[i][j] = '%';
	    //cout << i << "," << j << " ";
    }

    // Return false if no path to 'E' was found
    return false;
}
    
    //Use DFS to create maze
    void _maze(vector<vector<char> >& map, int i, int j){
        int direct[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
        int visitOrder[] = {0,1,2,3};
        //out of boundary
        if (map[i][j] == '=') return;
        #ifdef DEBUG
        cout<<"("<<i<<", "<<j<<")"<<endl;
        #endif
        //visited, go back to the coming direction, return 
        if(map[i][j] == ' ') return ;

        //some neightbors are visited in addition to the coming direction, return
        //this is to avoid circles in maze
        if(countVisitedNeighbor(map, i, j) > 1) return ;

        map[i][j] = ' '; // visited

        //shuffle the visitOrder
        shuffle(visitOrder, 4);
        
        for (int k = 0; k < 4; ++k)
        {
            int ni = i + direct[visitOrder[k]][0];
            int nj = j + direct[visitOrder[k]][1];
            _maze(map, ni, nj);
        }
    }

    int countVisitedNeighbor(vector<vector<char> >& map, int i, int j){
        int direct[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        int count = 0;
        for (int k = 0; k < 4; ++k)
        {
            int ni = i + direct[k][0];
            int nj = j + direct[k][1];
            //out of boundary
            if (map[i][j] == '=') continue;
            if(map[ni][nj] == ' ') count++;//visited
        }
        return count;
    }
    void shuffle(int a[], int n){
        for (int i = 0; i < n; ++i)
        {
            swap(a[i], a[rand() % n]);
        }
    }
    void swap(int & a, int &b){
        int c = a;
        a = b;
        b = c;
    }
};


int main(int argc, char const *argv[])
{
	Maze s;
    int height = 30;
    int width = 60;
    srand(time(0));
    vector<char> row(width+2);
    vector<vector<char> > map;
    for (int i = 0; i < height+2; ++i)
    {
        map.push_back(row);
    }
    s.maze(map);
    s.showMaze(map);
    s.solveMaze(map);
    s.showMaze(map);
    return 0;
}
