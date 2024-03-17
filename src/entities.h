//
// Created by Hector Mejia on 3/16/24.
//

#ifndef BREAKOUT_GAME_ENTITIES_H
#define BREAKOUT_GAME_ENTITIES_H

#include "common.h"
#include "assets/textures.h"

typedef enum Direction {
    LEFT = -1,
    NONE = 0,
    RIGHT = 1,
} Direction;

typedef struct Player {
    Sprite sprite;
    float speed;
    i8 direction;
    Vector2 position;
    Rectangle frame;
} Player;

typedef struct Brick {
    Sprite sprite;
    Rectangle frame;
    i32 health;
    Vector2 position;
} Brick;

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    int radius;
    Sprite sprite;
    Rectangle frame;
} Ball;

Vector2 ballLeftSide(Ball *ball);
Vector2 ballRightSide(Ball *ball);
Vector2 ballTopSide(Ball *ball);
Vector2 ballBottomSide(Ball *ball);

void updatePlayer(Player *player, float dt);
void updateBall(Ball *ball, Player *player, float deltaTime);
void updateBallLobby(Ball *ball, Player *player, float deltaTime);
void updateBricks(Brick *bricks, Ball* ball, float deltaTime);

#endif //BREAKOUT_GAME_ENTITIES_H
