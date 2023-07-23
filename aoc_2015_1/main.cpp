#include <iostream>
#include <fstream>
#include <array>

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

    string input_fname = "input.txt";
    ifstream input_f(input_fname, ios::in);
    if (!input_f.is_open()) {
        cout << "Could not open input file: " << input_fname << "\n";
        return 1;
    }

    int floor = 0;
    char c;
    while (input_f.read(&c, 1)) {
        if (c == '(') {
            floor++;
        }
        if (c == ')') {
            floor--;
        }
    }
    cout << "Santa ends up on floor: " << floor << "\n";

    return 0;
}
