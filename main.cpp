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

    string h_type;
    cout << "Pick an algorithm: MT, MD, or UCS" << endl;
    cin >> h_type;

    puzzle_state my_puzzle(puzzle);
    priority_queue<puzzle_state> states;
    vector<string> explored_states;
    vector<puzzle_state> explored;

    states.push(my_puzzle);
    const unsigned queue_cap = 30000; // used "hardest" 8 puzzle for MD, see attachment
    unsigned max_queue_size = states.size();
    unsigned nodes_expanded = 0;
    while(!states.empty() && states.size() < queue_cap) {
        if (max_queue_size < states.size()) {
            max_queue_size = states.size();
        }
        puzzle_state current = states.top();
        states.pop();
        if (CheckGoal(current)) {
            cout << "Found goal: " << endl;
            PrintState(current);
            cout << "Depth of goal node: " << current.GetG_Cost() << endl;
            cout << "Number of nodes expanded: " << nodes_expanded << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            return 0;
        }
        if (max_queue_size != 1) {
            cout << "The best state to is expand is: " << endl;
        }
        else {
            cout << "Initial state is: " << endl;
        }
        PrintState(current);
        // cout << "Heap size: " << states.size() << endl;
        explored.push_back(current);
        ExpandState(current, states, explored_states, h_type);
        ++nodes_expanded;
    }
    cout << "No solution found" << endl;
    cout << "Number of nodes expanded: " << nodes_expanded << endl;
    cout << "Max queue size: " << max_queue_size << endl;



    return 0;
}
