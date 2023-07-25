#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "AoC 2015 puzzle - https://adventofcode.com/2015/day/1\n";

    string puzzle_fname = "puzzle.txt";
    ifstream puzzle_f(puzzle_fname, ios::in);
    if (!puzzle_f.is_open()) {
        cout << "Could not open puzzle file: " << puzzle_fname << "\n";
        return 1;
    }
    for (string line; getline(puzzle_f, line); ) {
        cout << line << "\n";
    }
    puzzle_f.close();

    string input_fname = "input.txt";
    ifstream input_f(input_fname, ios::in);
    if (!input_f.is_open()) {
        cout << "Could not open input file: " << input_fname << "\n";
        return 1;
    }

    int floor = 0;
    int basement_first_time_position = 1;
    bool basement_first_time = false;
    char c;
    while (input_f.read(&c, 1)) {
        if (c == '(') {
            floor++;
        }
        if (c == ')') {
            floor--;
        }
        if (!basement_first_time) {
            if (floor == -1) {
                basement_first_time = true;
            } else {
                basement_first_time_position++;
            }
        }
    }
    input_f.close();

    cout << "Santa ends up on floor: " << floor << "\n";
    cout << "Santa first time in the basement at position:: " << basement_first_time_position << "\n";

    return 0;
}
