#include <raylib-cpp.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

class Matrix2D {
    public:
        Matrix2D() {
        }

        void gift(tuple<int , int > pos) {
            int x = get<0>(pos);
            int y = get<1>(pos);

            vector<vector<int>> *grid;
            unsigned long int x_abs = 0, y_abs = 0;

            if (x >= 0 && y >= 0) {
                grid = &_grid[0];
                x_abs = x;
                y_abs = y;
            }
            if (x >= 0 && y < 0) {
                grid = &_grid[1];
                x_abs = x;
                y_abs = (-1 -y);
            }
            if (x < 0 && y < 0) {
                grid = &_grid[2];
                x_abs = (-1 -x);
                y_abs = (-1 -y);
            }
            if (x < 0 && y >= 0) {
                grid = &_grid[3];
                x_abs = (-1 -x);
                y_abs = y;
            }
            _grid_house_add(*grid, x_abs, y_abs); 
            (*grid)[x_abs][y_abs]++;
        }

        unsigned int gifted_houses(void) {
            unsigned int gifted = 0;
            for (vector<vector<int>> &grid : _grid) {
                for (vector<int> &row : grid) {
                    for (int col : row) {
                        if (col > 0) {
                            gifted++;
                        }
                    }
                }
            }
            return gifted;
        }

    private:
        void _grid_house_add(vector<vector<int>> &grid, long unsigned int x_abs, long unsigned int y_abs) {
            while (grid.size() <= x_abs) {
                vector<int> row;
                grid.push_back(row);
            }
            while (grid[x_abs].size() <= y_abs) {
                grid[x_abs].push_back(0);
            }
        }

        vector<vector<int>> _grid[4]; // quadrants; 0:[x>=0,y>=0], 1:[x>=0,y<0], 2:[x<0,y<0], 3:[x<0,y>=0]
};

class Santa {
    public:
        Santa() {
            _pos_x = 0;
            _pos_y = 0;
        }

        tuple<int, int> pos(void) {
            return make_tuple(_pos_x, _pos_y);
        }

        void move(char c) {
            if (c == '>') {
                _pos_x++;
            }
            if (c == '<') {
                _pos_x--;
            }
            if (c == '^') {
                _pos_y++;
            }
            if (c == 'v') {
                _pos_y--;
            }
        }

    private:
        int _pos_x;
        int _pos_y;
};

int main(int argc, char *argv[]) {
    cout << "AoC 2015 day 3 - https://adventofcode.com/2015/day/3\n";

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

    char c;
    Santa santa;
    Matrix2D houses;
    houses.gift(santa.pos());
    while(input_f.get(c)) {
        santa.move(c);
        houses.gift(santa.pos());
    }

    unsigned int gifted_houses = houses.gifted_houses();
    cout << "Part 1: Gifted Houses = " << gifted_houses << endl;

    input_f.clear();
    input_f.seekg(0, ios::beg);

    Santa santa2;
    Santa robo_santa;
    Matrix2D houses2;
    int turn = 0;
    houses2.gift(santa2.pos());
    houses2.gift(robo_santa.pos());
    while(input_f.get(c)) {
        if (turn++ % 2 == 0) {
            santa2.move(c);
            houses2.gift(santa2.pos());
        } else {
            robo_santa.move(c);
            houses2.gift(robo_santa.pos());
        }
    }

    unsigned int gifted_houses2 = houses2.gifted_houses();
    cout << "Part 2: Gifted Houses = " << gifted_houses2 << endl;

    input_f.close();

    int screenWidth = 1920;
    int screenHeight = 1080;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");
    raylib::Color house_rect(0, 68, 130); 

    SetTargetFPS(60);

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // part 1
        //
        // read input
        // make santa move
        // create street, create houses, gift
        // 
        // part 2
        //
        // read input
        // make santa/robot_santa move
        // create street, create houses, gift

        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        house_rect.DrawRectangle(screenWidth/2 - 128, screenHeight/2 - 128, 256, 256);
        textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);
        EndDrawing();
    }

    return 0;
}
