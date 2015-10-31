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

void PrintPrev(puzzle_state *prev) {
    if (prev == NULL) {
        cout << "Is null" << endl;
        PrintState(*prev);
        return;
    }
    PrintPrev(prev->GetPrevState());
    PrintState(*prev);
}

void PrintPath(vector<puzzle_state> states) {
    PrintState(states.at(5));
    PrintState(states.at(4));
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

    string h_type;
    cout << "Pick an algorithm: MT, MD, or UCS" << endl;
    cin >> h_type;

    puzzle_state my_puzzle(puzzle);
    priority_queue<puzzle_state> states;
    vector<string> explored_states;
    vector<puzzle_state> explored;

    cout << "Initial state: " << endl;
    PrintState(my_puzzle);
    states.push(my_puzzle);
    unsigned max_queue_size = states.size();
    while(!states.empty()) {
        if (max_queue_size < states.size()) {
            max_queue_size = states.size();
        }
        puzzle_state current = states.top();
        cout << "The best state to is expand is: " << endl;
        PrintState(current);
        explored.push_back(current);
        if (CheckGoal(current)) {
            cout << "Found goal: " << endl;
            PrintState(current);
            cout << "Number of unique states: " << explored_states.size() << endl;
            cout << "Depth of goal node: " << current.GetG_Cost() << endl;
            cout << "Max queue size: " << max_queue_size << endl;
            break;
        }
        // PrintState(current);
        states.pop();
        ExpandState(current, states, explored_states, h_type);
        // cout << "Explored size: " << explored_states.size() << endl;
    }



    return 0;
}
