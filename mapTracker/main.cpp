#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::sort;
using std::abs;

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open, vector<vector<State>> &grid) {
  	open.push_back(vector<int> {x, y, g, h});
  	grid[x][y] = State::kClosed;
}

int Heuristic(int x1, int x2, int y1, int y2){
    return abs(x2 - x1) + abs(y2 - y1);
}

bool Compare(vector<int> node1, vector<int> node2){
  int f1 = node1[2] + node1[3];
  int f2 = node2[2] + node2[3];
  return f1 > f2;
}

void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
  bool valid_x = (x >= 0 && x < grid.size());
  bool valid_y = (y >= 0 && y < grid[0].size());
  if(valid_x && valid_y){
    return grid[x][y] == State::kEmpty;
  }
  return false;
}

void ExpandNeighbors(const vector<int> &current, int goal[2], vector<vector<int>> &openlist, vector<vector<State>> &grid) {
  
  int x = current[0];
  int y = current[1];
  int g = current[2];

  
  for (int i = 0; i < 4; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    
    if (CheckValidCell(x2, y2, grid)) {
      
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
}

vector<vector<State>> Search(vector<vector<State>> grid, int start[2], int goal[2]) {
    vector<vector<int>> open {};
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    AddToOpen(x, y, g, h, open, grid);

    while(open.size() > 0){
      CellSort(&open);
      auto currentNode = open.back();
      open.pop_back();
      int x = currentNode[0];
      int y = currentNode[1];
      grid[x][y] = State::kPath;

      if (x == goal[0] && y == goal[1]) {
        grid[start[0]][start[1]] = State::kStart;
        grid[goal[0]][goal[1]] = State::kFinish;
        return grid;
      }
      ExpandNeighbors(currentNode, goal, open, grid);
    }
    cout << "No path found!\n";
    return vector<vector<State>> {}; 
}

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
   
    vector<State> row;
    while (sline >> n >> c && c == ',') {
     
      row.push_back(n == 0 ? State::kEmpty : State::kObstacle);
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
 
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦 ";
    case State::kFinish: return "🏁 ";
    default: return "0   "; 
  }
}

void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
        cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

int main() {
    int init[2]{0, 0};
    int goal[2]{4, 5};
    auto board = ReadBoardFile("./board1.txt");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}