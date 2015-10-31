#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "puzzle_state.h"

using namespace std;

// Breaks three input into individual strings for puzzle row
// 'input.at(i)' returns a char!
// Only supports 8-puzzle input tiles (0 to 8)
vector<string> GetCustomInput(string &input) {
    getline(cin, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    vector<string> puzzle_row;
    for (unsigned i = 0; i < puzzle_size; ++i) {
        puzzle_row.push_back(string(1, input.at(i)));
    }
    return puzzle_row;
}

void PrintDashes() {
    for (unsigned i = 0; i < 12; ++i) {
        cout << "-";
    }
    cout << endl;
}

void PrintState(puzzle_state my_puzzle) {
    PrintDashes();
    my_puzzle.puzzle_state::PrintPuzzle();
    PrintDashes();
    my_puzzle.PrintCost();
    PrintDashes();
}

void UniformCost(puzzle_state &my_puzzle) {
    vector<string> explored_states;
    priority_queue<puzzle_state> states;
    states.push(my_puzzle);

}

void A_StarMT(puzzle_state &my_puzzle) {

}

void A_StarMD(puzzle_state &my_puzzle) {

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
            input.clear();
        }
    }

    puzzle_state my_puzzle(puzzle);
    puzzle_state new_puzzle = my_puzzle.puzzle_state::CreateUp(my_puzzle);
    puzzle_state new_new_puzzle = new_puzzle.puzzle_state::CreateLeft(new_puzzle);
    // PrintState(my_puzzle);
    // PrintState(new_puzzle);
    // PrintState(new_new_puzzle);
    my_puzzle.SetCosts("MT");
    new_puzzle.SetCosts("MT");
    new_new_puzzle.SetCosts("MT");

    priority_queue<puzzle_state> states;
    states.push(my_puzzle);
    states.push(new_puzzle);
    states.push(new_new_puzzle);

    while(!states.empty()) {
        PrintState(states.top());
        states.pop();
    }


    // while (1) {
    //     cout << "Enter your choice of algorithm" << endl;
    //     cout << "1 for Uniform Cost Search" << endl;
    //     cout << "2 for A* with Misplaced Tile heuristic" << endl;
    //     cout << "3 for A* with Manhattan distance heuristic" << endl;
    //     cin >> input;
    //     if (input == "1") {
    //         UniformCost(my_puzzle);
    //         break;
    //     }
    //     else if (input == "2") {
    //         A_StarMT(my_puzzle);
    //         break;
    //     }
    //     else if (input == "3") {
    //         A_StarMD(my_puzzle);
    //         break;
    //     }
    //     else {
    //         cout << "Invalid input." << endl;
    //         input.clear();
    //     }
    // }

    return 0;
}
