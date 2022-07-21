// Udacity c++ nanodegree, A* search algorithm implementation
// Add one function to keep track of path

// AStarSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "AStarSearch.h"


int main() {
    vector<int> S{ 0, 0 };
    vector<int> D{ 4, 5 };
    vector<vector<int>> explored; // store all nodes explored and their parent nodes
    
    //State a = (State)1;
    //if (a == State::kFinish) cout << "correct\n";

    vector<vector<State>> board = ReadBoardFile("1.board"); // Read the map
    cout << "original map\n\n";
    PrintBoard(board);
    
    vector<vector<State>> path = Search(board, S, D, explored); // Search the path with A* algorithm
    cout << "\npath found\n\n";
    PrintBoard(path); // Print the path, O means obstacle, P means path, S mean starting point, D means destination, E means empty, C means closed

    cout << "\nprint path\n\n";
    PrintPath(explored);
}

