//
// Created by Hector Mejia on 3/16/24.
//

#ifndef BREAKOUT_GAME_GAME_H
#define BREAKOUT_GAME_GAME_H

#include "entities.h"

typedef struct Game {
    Player *player;
    Brick *bricks;
    Ball *ball;
    u32 brickCount;
} Game;

void gameInit(Game *game);
void destroyGame(Game *game);

#endif //BREAKOUT_GAME_GAME_H
