#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H
#include <iostream>
#include <vector>

using namespace std;

const unsigned puzzle_size = 3;

// Place initial state into priority queue based on g_cost + h_cost
// Expand and place states into priority queue
    // Calculate g_cost and h_cost of each state
        // Increment g_cost
        // MTCost or MDCost h_cost if applicable
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
    public:
        puzzle_state() {
            prev_state = NULL;
            g_cost = 0;
            h_cost = 0;
        }
        puzzle_state(vector<vector<string> > puzzle) {
            this->puzzle = puzzle;
            prev_state = NULL;
            g_cost = 0;
            h_cost = 0;
        }
        puzzle_state(vector<vector<string> > puzzle, puzzle_state* prev, \
                     unsigned g_cost, unsigned h_cost) {
            this->puzzle = puzzle;
            this->prev_state = prev;
            this->g_cost = g_cost;
            this->h_cost = h_cost;
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

        // Check for valid operators
        bool CheckUp() {

        }
        bool CheckDown() {

        }
        bool CheckLeft() {

        }
        bool CheckRight() {

        }

        // Move '0' based on valid operators
        void MoveUp() {

        }
        void MoveDown() {

        }
        void MoveLeft() {

        }
        void MoveRight() {

        }

        // calculate h_cost
        unsigned MTCost() {

        }
        unsigned MDCost() {

        }

        void ExpandState() {

        }






};
#endif
