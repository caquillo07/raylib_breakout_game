#include "raylib.h"
#include "common.h"
#include "assets/textures.h"
#include "array/array.h"
#include "game.h"

Game game = {};

static void input() {
    if (IsKeyPressed(KEY_F1)) {
        game.isDebug = !game.isDebug;
    }
    // switch on game state for general input
    if (game.state == MENU_SCREEN) {
        if (IsKeyPressed(KEY_ENTER)) {
            game.state = LOBBY;
        }
    }
    if (game.state == LOBBY || game.state == PLAYING) {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            game.player->direction = RIGHT;
            return;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            game.player->direction = LEFT;
            return;
        }
    }
    if (game.state == LOBBY) {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
            game.state = PLAYING;
        }
    }
    if (game.state == PLAYING) {
        if (IsKeyPressed(KEY_P)) {
            game.state = PAUSED;
        }
        if (IsKeyDown(KEY_SPACE)) {
            game.ball->isMultiplied = true;
        } else {
            game.ball->isMultiplied = false;
        }
        return;
    }
    if (game.state == PAUSED) {
        if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
            game.state = PLAYING;
        }
    }

    if (game.state == GAME_OVER) {
        if (IsKeyPressed(KEY_ENTER)) {
            resetGame(&game);
            game.state = LOBBY;
        }
    }
}

static void update(float deltaTime) {
    switch (game.state) {
        case MENU_SCREEN:
            break;
        case LOBBY:
            updateBallLobby(game.ball, game.player);
            updatePlayer(game.player, deltaTime);
            break;
        case PLAYING:
            updatePlayer(game.player, deltaTime);
            updateBall(game.ball, game.player, deltaTime);
            updateBricks(game.bricks, game.ball, game.player, deltaTime);
            break;
        case PAUSED:
            break;
        case GAME_OVER:
            break;
        case WIN:
            break;
        default:
            break;
    }

    updateGame(&game);
    game.brickCount = array_length(game.bricks);
}

static void draw() {
    BeginDrawing();
    {
        ClearBackground(GRAY);
        // draw walls and a ceiling
        DrawRectangle(0, 0, WALL_WIDTH, ScreenHeight, DARKGRAY);
        DrawRectangle(ScreenWidth - WALL_WIDTH, 0, WALL_WIDTH, ScreenHeight, DARKGRAY);
        DrawRectangle(0, 0, ScreenWidth, CEILING_HEIGHT, DARKGRAY);

        TextureAtlas *atlas = getTextureAtlas("atlas"); // todo - fix this when its not 2:40am
        DrawTextureRec(atlas->texture, game.player->frame, game.player->position, WHITE);

        for (int i = 0; i < array_length(game.bricks); i++) {
            if (game.bricks[i].health <= 0) {
                continue;
            }
            DrawTextureRec(atlas->texture, game.bricks[i].frame, game.bricks[i].position, WHITE);
        }

        DrawCircleV(game.ball->position, (float) game.ball->radius, WHITE);

        drawGameScores(&game);
        drawDebug(&game);
    }
    DrawFPS(10, 10);
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
        float deltaTime = min(GetFrameTime(), 1 / 60.f);
        input();
        update(deltaTime);
        draw();
    }
    cleanup();
    return EXIT_SUCCESS;
}
