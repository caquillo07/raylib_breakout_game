#include "raylib.h"
#include "common.h"
#include "assets/textures.h"
#include "array/array.h"
#include "game.h"

Game game = {};

static void input() {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        game.player->direction = RIGHT;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        game.player->direction = LEFT;
    }
}

static void update(float deltaTime) {
    updatePlayer(game.player, deltaTime);
    updateBall(game.ball, game.player, deltaTime);

    updateBricks(game.bricks, game.ball, deltaTime);
    game.brickCount = array_length(game.bricks);
}

static void draw() {
    BeginDrawing();
    {
        ClearBackground(DARKGRAY);

        TextureAtlas *atlas = getTextureAtlas("atlas"); // todo - fix this when its not 2:40am
        DrawTextureRec(atlas->texture, game.player->frame, game.player->position, WHITE);

        for (int i = 0; i < array_length(game.bricks); i++) {
            if (game.bricks[i].health <= 0) {
                continue;
            }
            DrawTextureRec(atlas->texture, game.bricks[i].frame, game.bricks[i].position, WHITE);
        }

        DrawCircleV(game.ball->position, game.ball->radius, WHITE);

    }
    EndDrawing();
}

static void init() {
    InitWindow(ScreenWidth, ScreenHeight, "raylib [core] example - basic window");
    SetTargetFPS(FPS);

    initLogger();
    initTextureManager();

    gameInit(&game);
}

static void cleanup() {
    CloseWindow();
    slog_destroy();
    destroyTextureManager();
    destroyGame(&game);
}

int main() {
    init();
    while (!WindowShouldClose()) {
        input();
        update(GetFrameTime());
        draw();
    }
    cleanup();
    return EXIT_SUCCESS;
}
