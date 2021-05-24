#include <algorithm>
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
using std::sort;
using std::abs;

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

// directional deltas (possible movements)
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


void PrintGridInt(vector<vector<int>> &vetor_entrada) {
    for (int k = 0; k < vetor_entrada.size(); k++) {
        for (int j = 0; j < vetor_entrada[0].size(); j++) {
            cout << vetor_entrada[k][j] << "  ";
        }
        cout << "\n";
    }
}


vector<State> ParseLine(string line) {
    istringstream line_stream(line);
    int n;
    char c;
    vector<State> row;
    while (line_stream >> n >> c && c == ',') {
        if (n == 0) {
        row.push_back(State::kEmpty);
        } else {
        row.push_back(State::kObstacle);
        }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
    std::ifstream my_file;
    my_file.open(path);
    vector<vector<State>> board{};
    if (my_file) {
        string line;
        while (getline(my_file, line)) {
        vector<State> row = ParseLine(line);
        board.push_back(row);
        }
    }
    return board;
}


// Compare if the the f-value of the first node is greater than the
// f-value of the second nodes
bool Compare(const vector<int> node1, const vector<int> node2) {
	// node = {x, y, g, h}
	// g = distance value (increment each movement step)
	// h = heuristic value (is lower as we get closer to the goal)
	// f = g + h
	int f1 = node1[2] + node1[3];
	int f2 = node2[2] + node2[3];
    if (f1 > f2) {
        return true;
    } else if (f1 == f2)
    {
        return node1[3] > node2[3];
    } else {
        return false;
    }

}

// Sort the two-dimensional vector of ints in descending order.
// organized by "Compare" function (f-value descending)
void CellSort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), Compare);
}


int Heuristic(int x1, int y1, int x2, int y2) {
    //cout << "Heuristic: " << abs(x2 - x1) + abs(y2 - y1) << "\n";
    return abs(x2 - x1) + abs(y2 - y1);
}


bool CheckValidCell(int x, int y, vector<vector<State>> &grid_states) {
    bool on_grid_x = (x >= 0 && x < grid_states.size());
    bool on_grid_y = (y >= 0 && y < grid_states[0].size());
    if (on_grid_x && on_grid_y)
        return grid_states[x][y] == State::kEmpty;
    return false;
}


void AddToOpen(int x, int y, int g, int h,
                vector<vector<int>> &open_nodes,
                vector<vector<State>>  &grid_states) {
	vector<int> line = {x, y, g, h};
    open_nodes.push_back(line);
	grid_states[x][y] = State::kClosed;
}

// directional deltas      left    down    right     up
// const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
void ExpandNeighbors(const vector<int> &current,
                    int goal[2],
                    vector<vector<int>> &open_vector,
                    vector<vector<State>> &grid_states) {
    // Current node data
    int x = current[0];
    int y = current[1];
    int g = current[2];

    // Loop through all possibilities around the current node
    for (int i = 0; i <= 3; i++) {
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];
        //Check if is a valid cell and Add it to the open_node list
        if (CheckValidCell(x2, y2, grid_states)) {
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, open_vector, grid_states);
        }
    }
}

string CellString(State cell) {
    switch (cell) {
        case State::kObstacle: return "⛰️    ";
        case State::kStart: return "🚦   ";
        case State::kFinish: return "🏁   ";
        case State::kPath: return "🚗   ";
        default: return "0    ";
    }
}


void PrintBoard(const vector<vector<State>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << CellString(board[i][j]);
        }
        cout << "\n";
    }
}


vector<vector<State>> Search(vector<vector<State>> grid_states,
							 int init[2],
							 int goal[2]) {
	// Initialize the init position
	int x = init[0];
	int y = init[1];
    int g = 0;
	int h = Heuristic(init[0], init[1], goal[0], goal[1]);

    // Start the open nodes grid
	vector<vector<int>> open_nodes {};
	AddToOpen(x, y, g, h, open_nodes, grid_states);

	while (open_nodes.size() > 0) {

        // ------------ testing ----------------
	    cout << "Open Nodes before sorting: " << "\n";
        PrintGridInt(open_nodes);
        // -------------------------------------

        // Sort open_nodes by f-value descending
	    CellSort(&open_nodes);

        // ------------ testing ----------------
	    cout << "Open Nodes After sorting: " << "\n";
        PrintGridInt(open_nodes);
        // -------------------------------------

		// Get the last line = lower f-value = closest to the goal
		auto current = open_nodes.back();

		// Removes the last line = higher f-value 
		open_nodes.pop_back();
		x = current[0];
		y = current[1];
		grid_states[x][y] = State::kPath;

        // --------------- Testing ----------------------
        cout << "Open Nodes After pop_back(): " << "\n";
        PrintGridInt(open_nodes);
        cout << "Current Node: ";
        for (int i = 0; i < current.size(); i++){
            cout << current[i] << " ";
        } cout << "\n";
        PrintBoard(grid_states);

        std::cin.ignore(); //Press enter to continue
		// ----------------------------------------------

        // Check if we're done.
		if (x == goal[0] && y == goal[1]) {
            grid_states[init[0]][init[1]] = State::kStart;
            grid_states[goal[0]][goal[1]] = State::kFinish;
			return grid_states;
		} else {
            ExpandNeighbors(current, goal, open_nodes, grid_states);
        }

	}

    // We've run out of new nodes to explore and haven't found a path.
    cout << "No path found!" << "\n";
    return std::vector<vector<State>> {};
}

//--------------------- Main Function ---------------------------------
int main() {
    int init[2] {0, 0};
    int goal[2] {4, 5};
    auto board_file = ReadBoardFile("../files/grid.txt");
    auto solution = Search(board_file, init, goal);
    // TODO: Change the following line to pass "solution" to PrintBoard.
    PrintBoard(solution);
}
