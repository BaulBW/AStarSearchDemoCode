#include "AStarSearch.h"

// dir's
vector<vector<int>> delta{ {1,0}, {0,1}, {-1,0}, {0,-1} };

vector<State> ParseLine(string line) {

    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',')
    {
        if (n == 0)
        {
            row.push_back(State::kEmpty);
        }
        else
        {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {

    ifstream myfile(path);
    vector<vector<State>> board;
    if (myfile)
    {
        string line;
        while (getline(myfile, line))
        {
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}


// Compare F-value, the node with smallest F-value will be explored first
bool Compare(const vector<int> a, const vector<int> b) {

    int f1 = a[2] + a[3];
    int f2 = b[2] + b[3];
    return f1 > f2;
}


// Sort the two-dimensional vectors in descending order of F-value.
void CellSort(vector<vector<int>>& openlist) {
    sort(openlist.begin(), openlist.end(), Compare);
}


// Calculate the heuristic function, defined by manhattan distance
int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}



// Check that a cell is valid. Valid cells can be added to openlist.
bool CheckValidCell(int x, int y, vector<vector<State>>& grid) {

    if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == State::kEmpty)
        return true;
    else return false;
}

// Add a node to the open list and mark it as closed.
void AddToOpen(int x, int y, int g, int h, int x0, int y0, vector<vector<int>>& openlist, vector<vector<State>>& grid) {

    openlist.push_back(vector<int>{x, y, g, h, x0, y0});
    grid[x][y] = State::kClosed;
}



// Expand current nodes's neighbors and add them to the open list.
void ExpandNeighbors(const vector<int>& current, vector<int> goal, vector<vector<int>>& openlist, vector<vector<State>>& grid) {

    int x = current[0];
    int y = current[1];
    int g = current[2];

    // Add eligible neighbors of the current node to openlist.
    for (int i = 0; i < 4; i++)
    {
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];

        if (CheckValidCell(x2, y2, grid))
        {
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, x, y, openlist, grid);
        }
    }
}



// A* algorithm, init is the starting point, goal is the destination
vector<vector<State>> Search(vector<vector<State>> grid, vector<int> init, vector<int> goal, vector<vector<int>>& explored) {

    vector<vector<int>> openlist;

    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, -1, -1, openlist, grid);

    while (!openlist.empty())
    {
        // Get the next node
        CellSort(openlist);
        auto current = openlist.back();
        openlist.pop_back();
        explored.push_back(current);
        x = current[0];
        y = current[1];
        grid[x][y] = State::kPath;

        // Check if we're done.
        if (x == goal[0] && y == goal[1]) {
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            return grid;
        }

        // Add neighbors to openlist
        ExpandNeighbors(current, goal, openlist, grid);
    }

    // openlist is empty but we haven't found a path.
    cout << "No path found!\n";
    return vector<vector<State>>();
}

string CellString(State cell) {

    switch(cell)
    {
    case State::kObstacle: return "O   ";
    case State::kPath: return "P   ";
    case State::kEmpty: return "E   ";
    case State::kClosed: return "C   ";
    case State::kStart: return "S   ";
    case State::kFinish: return "D   ";
    default: return "?   ";
    }
}


void PrintBoard(const vector<vector<State>> board) {
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            cout << CellString(board[i][j]);
        }
        cout << "\n";
    }
}

void PrintPath(const vector<vector<int>> explored)
{
    int prevx = explored.back()[4], prevy = explored.back()[5];
    int curx = explored.back()[0], cury = explored.back()[1];
    cout << curx << ", " << cury << "\n";

    for (int i = explored.size() - 2; i >= 0; i--)
    {
        curx = explored[i][0], cury = explored[i][1];
        if (curx == prevx && cury == prevy)
        {
            prevx = explored[i][4];
            prevy = explored[i][5];
            cout << curx << ", " << cury << "\n";
        }
    }
}
