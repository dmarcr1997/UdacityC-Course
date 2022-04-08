#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


void ReadBoardFile(string path){
	ifstream board_file(path);
    if(board_file){
        cout << "The file stream has been created!" << endl;
        string line;
        while(getline(board_file, line)){
            cout << line << endl;
        }
    }
}

void PrintBoard(vector<vector<int>> board){
	for(auto row: board){
        for(int val: row){
            cout << val;  
        }
        cout << endl;
    }
}

int main(){
    vector<vector<int>> board
    {{0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0}};
    PrintBoard(board);
    string path = "./board1.txt";
    ReadBoardFile(path);
}