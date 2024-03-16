#include <stdio.h>
#include <raylib.h>
#include "common.h"

const int screenWidth = 1280;
const int screenHeight = 720;

static void input() {
    slogw("input");
}

static void update() {
    slogt("update");
}

static void draw() {
    slogi("draw");
    BeginDrawing();
    {
        ClearBackground(DARKGRAY);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    }
    EndDrawing();
}

static void init() {
    initLogger();
    sloge("init");


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);
}

static void cleanup() {
    CloseWindow();
    slogf("cleanup");
}

int main() {
    init();
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        input();
        update();
        draw();
        break;
    }

    cleanup();
    return 0;
}
