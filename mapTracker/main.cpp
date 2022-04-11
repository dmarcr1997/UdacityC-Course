#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State {kEmpty, kObstacle, kClosed};

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open, vector<vector<State>> &grid) {
  	open.push_back(vector<int> {x, y, g, h});
  	grid[x][y] = State::kClosed;
}

int Heuristic(int x1, int x2, int y1, int y2){
    return abs(x2 - x1) + abs(y2 - y1);
}

bool Compare(vector<int> node1, vector<int> node2){
  return (node1[2] + node1[3]) > (node2[2] + node2[3]) ? true : false;
}

vector<vector<State>> Search(vector<vector<State>> grid, int start[2], int goal[2]) {
    vector<vector<int>> open {};
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    AddToOpen(x, y, g, h, open, grid);
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
    default: return "0   "; 
  }
}

void PrintBoard(const vector<vector<State>> board) {
  for (auto row: board) {
    for (auto col: row) {
        cout << CellString(col);
    }
    cout << "\n";
  }
}

int main() {
    auto board = ReadBoardFile("./board1.txt");
    PrintBoard(board);
}