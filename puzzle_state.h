#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H
#include <iostream>
#include <vector>
#include <queue>
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

        void PrintPuzzle() {
            for (unsigned i = 0; i < puzzle.size(); ++i) {
                for (unsigned j = 0; j < puzzle.at(i).size(); ++j) {
                    cout << puzzle.at(i).at(j) << " ";
                }
                cout << endl;
            }
        }
        vector<vector<string> > GetState() const {
            return this->puzzle;
        }
        puzzle_state* GetPrevState() const {
            return this->prev_state;
        }
        unsigned GetG_Cost() const {
            return this->g_cost;
        }
        unsigned GetH_Cost() const {
            return this->h_cost;
        }
        pair<int, int> GetBlank() const {
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
            unsigned num_MT = 0;
            vector<int> puzzle_map;
            for (unsigned i = 0; i < puzzle.size(); ++i) {
                for (unsigned j = 0; j < puzzle.at(i).size(); ++j) {
                    puzzle_map.push_back(stoi(puzzle.at(i).at(j)));
                }
            }
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
            unsigned num_MD = 0;
            unsigned MD_sum = 0;
            int num = 1;
            // Checks from 0,0 to i,j-1 -- last tile on board
            // Need to check 0 manually
            for (int i = 0; i < puzzle.size(); ++i) {
                for (int j = 0; j < puzzle.at(i).size() && num != puzzle.size() * puzzle.size(); ++j) {
                    // cout << "Checking " << i << " " << j << " for " << num;
                    // cout << "... found " << puzzle.at(i).at(j) << endl;

                    // If we find a mismatch we find the position the tile is supposed to be
                    // in and calculate it
                    if (puzzle.at(i).at(j) != to_string(num)) {
                        for(int k = 0; k < puzzle.size(); ++k) {
                            for (int l = 0; l < puzzle.at(k).size(); ++l) {
                                if (to_string(num) == puzzle.at(k).at(l)) {
                                    MD_sum += abs(i - k) + abs(j - l);
                                    // cout << "MD so far: " << MD_sum << endl;
                                }
                            }
                        }
                    }
                    ++num;
                }
            }

            if (puzzle.at(puzzle.size()-1).at(puzzle.size()-1) != "0") {
                for (int i = 0; i < puzzle.size(); ++i) {
                    for (int j = 0; j < puzzle.size(); ++j) {
                        if (puzzle.at(i).at(j) == "0") {
                            int sz = puzzle.size()-1;
                            // cout << "Found 0 at " << i << " "  << j << endl;
                            MD_sum += abs(sz - i) + abs(sz- j);
                        }
                    }
                }
            }
            // cout << "MD: " << MD_sum << endl;
            return MD_sum;
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
        unsigned CalcF_Cost() const {
            return GetG_Cost() + GetH_Cost();
        }

        void PrintCost() {
            cout << "g_cost: " << g_cost << endl;
            cout << "h_cost: " << h_cost << endl;
            cout << "f_cost: " << g_cost + h_cost << endl;
        }

        // Performs operation on my_puzzle, sets pointer to implicit object, return my_puzzle
        puzzle_state CreateUp(puzzle_state my_puzzle) {
            my_puzzle.MoveUp();
            my_puzzle.prev_state = this;
            return my_puzzle;
        }
        puzzle_state CreateDown(puzzle_state my_puzzle) {
            my_puzzle.MoveDown();
            my_puzzle.prev_state = this;
            return my_puzzle;
        }
        puzzle_state CreateLeft(puzzle_state my_puzzle) {
            my_puzzle.MoveLeft();
            my_puzzle.prev_state = this;
            return my_puzzle;
        }
        puzzle_state CreateRight(puzzle_state my_puzzle) {
            my_puzzle.MoveRight();
            my_puzzle.prev_state = this;
            return my_puzzle;
        }

        void SetCosts(const string &h) {
            this->g_cost += 1;
            if (h == "MT") {
                // cout << "Set to: MT" << endl;
                this->h_cost = MTCost();
            }
            else if (h == "MD") {
                // cout << "Set to: MD" << endl;
                this->h_cost = MDCost();
            }
            else {
                // cout << "Set to default: UCS" << endl;
                this->h_cost = 0;
            }
        }

        // Want lowest value!
        bool operator<(const puzzle_state &lhs) const {
            return !(this->CalcF_Cost() < lhs.CalcF_Cost());
        }
};

string map_state(vector<vector<string> > state) {
            string state_map;
            for (unsigned i = 0; i < state.size(); ++i) {
                for (unsigned j = 0; j < state.at(i).size(); ++j) {
                    state_map.append(state.at(i).at(j));
                }
            }
            return state_map;
        }

void ExpandState(puzzle_state current, priority_queue<puzzle_state> &states, \
                vector<string> &explored_states, const string &h) {
    puzzle_state puzzle_up = current.CreateUp(current);
    string up_map = map_state(puzzle_up.GetState());
    puzzle_state puzzle_down = current.CreateDown(current);
    string down_map = map_state(puzzle_down.GetState());
    puzzle_state puzzle_left = current.CreateLeft(current);
    string left_map = map_state(puzzle_left.GetState());
    puzzle_state puzzle_right = current.CreateRight(current);
    string right_map = map_state(puzzle_right.GetState());
    bool repeat_up = 0;
    bool repeat_down = 0;
    bool repeat_left = 0;
    bool repeat_right = 0;
    explored_states.push_back(map_state(current.GetState()));
    for (unsigned i = 0; i < explored_states.size(); ++i) {
        if (explored_states.at(i) == up_map) {
            // cout << "Already explored " << up_map << endl;
            repeat_up = 1;
        }
        else if (explored_states.at(i) == down_map) {
            // cout << "Already explored " << down_map << endl;
            repeat_down = 1;
        }
        else if (explored_states.at(i) == left_map) {
            // cout << "Already explored " << left_map << endl;
            repeat_left = 1;
        }
        else if (explored_states.at(i) == right_map) {
            // cout << "Already explored " << right_map << endl;
            repeat_right = 1;
        }
    }
    if (!(repeat_up)) {
        puzzle_up.SetCosts(h);
        states.push(puzzle_up);
    }
    if (!(repeat_down)) {
        puzzle_down.SetCosts(h);
        states.push(puzzle_down);
    }
    if (!(repeat_left)) {
        puzzle_left.SetCosts(h);
        states.push(puzzle_left);
    }
    if (!(repeat_right)) {
        puzzle_right.SetCosts(h);
        states.push(puzzle_right);
    }
}

bool CheckGoal(const puzzle_state &my_puzzle) {
    string goal = "123456780";
    string my_state = map_state(my_puzzle.GetState());
    if (goal == my_state) {
        return true;
    }
    return false;
}





#endif
