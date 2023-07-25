#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
    int ribbon_len = 0;
    std::string line;
    while (std::getline(input_f, line)) {
        int L, W, H;
        std::istringstream iss(line);
        // Assuming the format is "LxWxH" where L, W, and H are integers
        char delimiter;
        iss >> L >> delimiter >> W >> delimiter >> H;

        vector<int> gift_dim = {L, W, H};
        sort(gift_dim.begin(), gift_dim.end());

        int side_area_smallest = gift_dim[0] * gift_dim[1];
        int area_total = (2 * ((L * W) + (W * H) + (H * L))) + side_area_smallest;
        gift_wrapping_area_total += area_total;

        ribbon_len += (gift_dim[0] * gift_dim[1] * gift_dim[2]) + (2*(gift_dim[0] + gift_dim[1]));
    }
    std::cout << "square feet of wrapping paper needed = " << gift_wrapping_area_total << std::endl;
    std::cout << "feet of ribbon needed = " << ribbon_len << std::endl;

    input_f.close();
    return 0;
}
