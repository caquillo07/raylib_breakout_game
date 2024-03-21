//
// Created by Hector Mejia on 3/16/24.
//

#ifndef BREAKOUT_GAME_GAME_H
#define BREAKOUT_GAME_GAME_H

#include "entities.h"

typedef enum GameState {
    MENU_SCREEN,
    LOBBY,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN,
} GameState;

typedef struct Game {
    GameState state;
    Player *player;
    Brick *bricks;
    Ball *ball;
    u32 brickCount;
    u32 level;
    u32 highestScore;
    bool isDebug;
} Game;

void gameInit(Game *game);
void destroyGame(Game *game);

void updateGame(Game *game);
void resetGame(Game *game);

void loadLevel(Game *game, TextureAtlas *atlas, const int levelNum);

void drawGameScores(Game *game);
void drawDebug(Game *game);

#endif //BREAKOUT_GAME_GAME_H
