#include <iostream>
#include <vector>
#include <algorithm>
#include "puzzle_state.h"

using namespace std;

// Breaks three input into individual strings for puzzle row
// 'input.at(i)' returns a char!
vector<string> GetCustomInput(string &input) {
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    vector<string> puzzle_row;
    for (unsigned i = 0; i < puzzle_size; ++i) {
        puzzle_row.push_back(string(1, input.at(i))); // make string of size 1 with char input.at(i)
    }
    return puzzle_row;
}

void PrintDashes() {
    for (unsigned i = 0; i < 12; ++i) {
        cout << "-";
    }
    cout << endl;
}

int main() {
    vector<vector<string> > puzzle;
    string input;
    while (1) {
        cout << "Enter 1 for default puzzle, 2 for custom puzzle: " << endl;
        cin >> input;
        if (input == "1") {
            puzzle = { {"1", "2", "3"},
                       {"4", "8", "0"},
                       {"7", "6", "5"} };
            break;
        }
        else if (input == "2") {
            cin.ignore();
            cout << "Enter your puzzle, use zero to represent the blank: " << endl;
            cout << "Enter the first row, use spaces in between numbers: " << endl;
            puzzle.push_back(GetCustomInput(input));
            cout << "Enter the second row, use spaces in between numbers: " << endl;
            puzzle.push_back(GetCustomInput(input));
            cout << "Enter the third row, use spaces in between numbers: " << endl;
            puzzle.push_back(GetCustomInput(input));
            break;
        }
        else {
            cout << "Invalid input." << endl;
        }
    }
    puzzle_state my_puzzle(puzzle);

    cout << "Initial state of puzzle: " << endl;
    my_puzzle.puzzle_state::PrintPuzzle();
    my_puzzle.puzzle_state::MTCost();
    PrintDashes();
    my_puzzle.puzzle_state::MoveUp();
    my_puzzle.puzzle_state::PrintPuzzle();
    my_puzzle.puzzle_state::MTCost();
    PrintDashes();
    my_puzzle.puzzle_state::MoveDown();
    my_puzzle.puzzle_state::PrintPuzzle();
    my_puzzle.puzzle_state::MTCost();
    PrintDashes();
    my_puzzle.puzzle_state::MoveLeft();
    my_puzzle.puzzle_state::PrintPuzzle();
    my_puzzle.puzzle_state::MTCost();
    PrintDashes();
    my_puzzle.puzzle_state::MoveRight();
    my_puzzle.puzzle_state::PrintPuzzle();
    my_puzzle.puzzle_state::MTCost();
    PrintDashes();

    return 0;
}
