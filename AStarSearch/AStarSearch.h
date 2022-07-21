#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;
using std::abs;

enum class State { kStart, kFinish, kEmpty, kObstacle, kClosed, kPath };

vector<State> ParseLine(string line);

vector<vector<State>> ReadBoardFile(string path);

bool Compare(const vector<int> a, const vector<int> b);

void CellSort(vector<vector<int>>& openlist);

int Heuristic(int x1, int y1, int x2, int y2);

bool CheckValidCell(int x, int y, vector<vector<State>>& grid);

void AddToOpen(int x, int y, int g, int h, int x0, int y0, vector<vector<int>>& openlist, vector<vector<State>>& grid);

void ExpandNeighbors(const vector<int>& current, vector<int> goal, vector<vector<int>>& openlist, vector<vector<State>>& grid);

vector<vector<State>> Search(vector<vector<State>> grid, vector<int> init, vector<int> goal, vector<vector<int>>& explored);

string CellString(State cell);

void PrintBoard(const vector<vector<State>> board);

void PrintPath(const vector<vector<int>> explored);