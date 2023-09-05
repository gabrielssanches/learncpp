#include <raylib-cpp.hpp>

raylib::Window window;

static void __window_draw(void) {
    BeginDrawing();
    {
        window.ClearBackground(BLACK);
        
        raylib::Rectangle paddle_r(100, 100, 10, 100);
        paddle_r.Draw(RAYWHITE);

        raylib::Rectangle paddle_l(700, 100, 10, 100);
        paddle_r.Draw(RAYWHITE);
    }
    EndDrawing();
}

static void __main_loop(void) {
    __window_draw();
}

int main(int argc, char *argv[]) {
    window.Init(800, 450, "Pong - raylib-cpp");

    SetTargetFPS(60);

    while (!window.ShouldClose()) {   // Detect window close button or ESC key
        __main_loop();
    }

    return 0;
}

