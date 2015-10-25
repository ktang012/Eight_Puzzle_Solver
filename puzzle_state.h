#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const unsigned puzzle_size = 3;

// Place initial state into priority queue based on g_cost + h_cost
// Expand and place states into priority queue
    // Calculate g_cost and h_cost of each state
        // Increment g_cost
        // MTCost or MDCost h_cost if applicable
        // Note: When we calculate costs while expanding
// Get highest priority state, state_i
// Test state_i if goal
// Expand state_i and place states into priority queue
// ...
// Found state_i is goal
// Add state_i to list
// Go to state_i-1, add state_i-1 to list, ..., until NULL
// Output list in ordered fashion with state representation, g_cost, and h_cost

class puzzle_state {
    private:
        vector<vector<string> > puzzle;
        puzzle_state* prev_state;
        unsigned g_cost;
        unsigned h_cost;
        pair<int, int> blank;
    public:
        puzzle_state() {
            prev_state = NULL;
            g_cost = 0;
            h_cost = 0;
            blank = make_pair(0, 0);
        }
        // Used for initial state
        puzzle_state(vector<vector<string> > puzzle) {
            this->puzzle = puzzle;
            prev_state = NULL;
            g_cost = 0;
            h_cost = 0;
            blank = CalcBlank();
        }
        // Will be used when expanding
        // Need to code in h_cost
        puzzle_state(vector<vector<string> > puzzle, puzzle_state* prev, unsigned h_cost) {
            this->puzzle = puzzle;
            this->prev_state = prev;
            g_cost = g_cost + 1;
            this->h_cost = h_cost;
            blank = CalcBlank();
        }

        void PrintPuzzle() {
            for (unsigned i = 0; i < puzzle.size(); ++i) {
                for (unsigned j = 0; j < puzzle.at(i).size(); ++j) {
                    cout << puzzle.at(i).at(j) << " ";
                }
                cout << endl;
            }
        }
        vector<vector<string> > GetState() {
            return this->puzzle;
        }
        puzzle_state* GetPrevState() {
            return this->prev_state;
        }
        unsigned GetG_Cost() {
            return this->g_cost;
        }
        unsigned GetH_Cost() {
            return this->h_cost;
        }
        pair<int, int> GetBlank() {
            return this->blank;
        }

        // Check for valid operators in NxN board
        bool CheckUp() {
            if (blank.first == 0) {
                return false;
            }
           return true;
        }
        bool CheckDown() {
            if (blank.first == puzzle.size()-1) {
                return false;
            }
            return true;
        }
        bool CheckLeft() {
            if (blank.second == 0) {
                return false;
            }
            return true;
        }
        bool CheckRight() {
            if (blank.second == puzzle.size()-1) {
                return false;
            }
            return true;
        }

        // Move '0' based on valid operators
        void MoveUp() {
            if (CheckUp()) {
                string temp = puzzle.at(blank.first - 1).at(blank.second);
                puzzle.at(blank.first - 1).at(blank.second) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.first = blank.first - 1;
            }
        }
        void MoveDown() {
            if (CheckDown()) {
                string temp = puzzle.at(blank.first + 1).at(blank.second);
                puzzle.at(blank.first + 1).at(blank.second) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.first = blank.first + 1;
            }
        }
        void MoveLeft() {
            if (CheckLeft()) {
                string temp = puzzle.at(blank.first).at(blank.second - 1);
                puzzle.at(blank.first).at(blank.second - 1) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.second= blank.second - 1;
            }
        }
        void MoveRight() {
            if (CheckRight()) {
                string temp = puzzle.at(blank.first).at(blank.second + 1);
                puzzle.at(blank.first).at(blank.second + 1) = "0";
                puzzle.at(blank.first).at(blank.second) = temp;
                blank.second= blank.second + 1;
            }
        }

        // calculate stuff
        unsigned MTCost() {
            vector<int> puzzle_map;
            for (unsigned i = 0; i < puzzle.size(); ++i) {
                for (unsigned j = 0; j < puzzle.at(i).size(); ++j) {
                    puzzle_map.push_back(stoi(puzzle.at(i).at(j)));
                }
            }
            unsigned num_MT = 0;
            for (unsigned i = 0; i < puzzle_map.size() - 1; ++i) {
                if (puzzle_map.at(i) != i + 1) {
                    num_MT += 1;
                }
            }
            if (puzzle_map.at(puzzle_map.size() - 1) != 0) {
                num_MT += 1;
            }
            // cout << "MT: " << num_MT << endl;
            return num_MT;
        }
        unsigned MDCost() {


        }
        pair<int, int> CalcBlank() {
            for (int i = 0; i < puzzle.size(); ++i) {
                for(int j = 0; j < puzzle.at(i).size(); ++j) {
                    if (puzzle.at(i).at(j) == "0") {
                        pair<int, int> blank_rc(i, j);
                        return blank_rc;
                    }
                }
            }
            cerr << "Error finding \"0\"" << endl;
            pair<int, int> blank_rc(-1, -1);
            return blank_rc;
        }

        void ExpandState() {

        }


};
#endif
