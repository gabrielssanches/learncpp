#include <raylib-cpp.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

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

        vector<vector <int>> *grid_get(int q) {
            return &_grid[q];
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

    int screenWidth = 800;
    int screenHeight = 600;

    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(__window_main_loop, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose()) {    // Detect window close button or ESC key
        __window_main_loop();
    }
#endif
    return 0;
}

static void __window_main_loop(void) {
    static bool setup_done = false;

    if (setup_done) {
        goto main_loop;
    }

    int rot = 0;
    float window_ts = 0.0f;
    float lastdrawn_ts = 0.0f;

    char c;
    Santa santa;
    Matrix2D houses;
    houses.gift(santa.pos());

    raylib::Camera2D cam(raylib::Vector2{0,0}, raylib::Vector2{0,0}, 0.0f, 1.0f);

main_loop:
    window_ts += w.GetFrameTime();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (IsKeyDown(KEY_UP)) {
        //cam.target = cam.GetTarget() + Vector2{0, -10};
        raylib::Vector2 target_diff(0, -10);
        raylib::Vector2 target;
        target = cam.GetTarget();
        target += target_diff;
        cam.SetTarget(target); // Addition assignment operator override.
    }
    if (IsKeyDown(KEY_DOWN)) {
        //cam.target = cam.target + Vector2{0, 10};
        // raylib-cpp
        raylib::Vector2 target_diff(0, 10);
        raylib::Vector2 target;
        target = cam.GetTarget();
        target += target_diff;
        cam.SetTarget(target); // Addition assignment operator override.
    }


    BeginMode2D(cam);

    if (true || (window_ts - lastdrawn_ts) > 0.010f) {
        lastdrawn_ts = window_ts;
        rot+=10;

        if (!input_f.get(c)) {
            cout << "DONE!" << endl;
            break;
        }
        santa.move(c);
        houses.gift(santa.pos());
    }
    
    vector<vector <int>> *grid = houses.grid_get(0);
    int row_i = 0;
    for (vector<int> &row : *grid) {
        int col_i = 0;
        for (int col : row) {
            raylib::Rectangle h_rect(screenWidth/2 + (row_i * 10), screenHeight/2 -10 - (col_i * 10), 10, 10);
            if (col > 0) {
                h_rect.Draw(GREEN);
            } else {
                h_rect.Draw(LIGHTGRAY);
            }
            col_i++;
        }
        row_i++;
    }
    grid = houses.grid_get(1);
    row_i = 0;
    for (vector<int> &row : *grid) {
        int col_i = 0;
        for (int col : row) {
            raylib::Rectangle h_rect(screenWidth/2 + (row_i * 10), screenHeight/2 + (col_i * 10), 10, 10);
            if (col > 0) {
                h_rect.Draw(GREEN);
            } else {
                h_rect.Draw(LIGHTGRAY);
            }
            col_i++;
        }
        row_i++;
    }
    grid = houses.grid_get(2);
    row_i = 0;
    for (vector<int> &row : *grid) {
        int col_i = 0;
        for (int col : row) {
            raylib::Rectangle h_rect(screenWidth/2 -10 - (row_i * 10), screenHeight/2 + (col_i * 10), 10, 10);
            if (col > 0) {
                h_rect.Draw(GREEN);
            } else {
                h_rect.Draw(LIGHTGRAY);
            }
            col_i++;
        }
        row_i++;
    }
    grid = houses.grid_get(3);
    row_i = 0;
    for (vector<int> &row : *grid) {
        int col_i = 0;
        for (int col : row) {
            raylib::Rectangle h_rect(screenWidth/2 -10 - (row_i * 10), screenHeight/2 -10 - (col_i * 10), 10, 10);
            if (col > 0) {
                h_rect.Draw(GREEN);
            } else {
                h_rect.Draw(LIGHTGRAY);
            }
            col_i++;
        }
        row_i++;
    }

    int x, y;
    tie(x, y) = santa.pos();
    raylib::Rectangle santa(screenWidth/2 + (x * 10), screenHeight/2 -10 - (y * 10), 10, 10);
    santa.Draw(RED);

    raylib::Vector2 y_axis(screenWidth/2, 0);
    y_axis.DrawLine((raylib::Vector2){screenWidth/2, screenHeight}, (raylib::Color){BLACK});
    raylib::Vector2 x_axis(0, screenHeight/2);
    x_axis.DrawLine((raylib::Vector2){screenWidth, screenHeight/2}, (raylib::Color){BLACK});

    //santa.Draw((raylib::Vector2){0,0}, (float)rot, RED);

    //house_rect.DrawLine(screenWidth/2100, 100, 200, 200);
    
    //house_rect.DrawRectangle(-100, screenHeight/2 - 128, 256, 256);
    string pos_str;
    pos_str = "Santa(" + to_string(x) + ", " + to_string(y) + ")";
    raylib::Color textColor(BLACK);
    textColor.DrawText(pos_str, 10, 10, 20);
    EndMode2D();
    EndDrawing();

    //unsigned int gifted_houses = houses.gifted_houses();
    //cout << "Part 1: Gifted Houses = " << gifted_houses << endl;
    //input_f.close();
}
