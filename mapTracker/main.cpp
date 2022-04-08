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

enum class State {kEmpty, kObstacle};

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