#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    cout << "AoC 2015 day 2 - https://adventofcode.com/2015/day/2\n";

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

    int gift_wrapping_area_total = 0;
    std::string line;
    while (std::getline(input_f, line)) {
        int L, W, H;
        std::istringstream iss(line);
        // Assuming the format is "LxWxH" where L, W, and H are integers
        char delimiter;
        iss >> L >> delimiter >> W >> delimiter >> H;

        int side_area_smallest = L * W;
        if (side_area_smallest > (L * H)) {
            side_area_smallest = (L * H);
        }
        if (side_area_smallest > (W * H)) {
            side_area_smallest = (W * H);
        }
        int area_total = (2 * ((L * W) + (W * H) + (H * L))) + side_area_smallest;
        gift_wrapping_area_total += area_total;
    }
    std::cout << "square feet of wrapping paper needed = " << gift_wrapping_area_total << std::endl;

    input_f.close();
    return 0;
}
