//
// Created by Hector Mejia on 3/16/24.
//

#include "entities.h"
#include "array/array.h"

void updatePlayer(Player *player, float deltaTime) {
    if (player->direction == RIGHT) {
        player->position.x += player->speed * deltaTime;
        if (player->position.x >= (ScreenWidth - player->frame.width)) {
            player->position.x = (ScreenWidth - player->frame.width);
        }
    }
    if (player->direction == LEFT) {
        player->position.x -= player->speed * deltaTime;
        if (player->position.x <= 0) {
            player->position.x = 0;
        }
    }
    player->direction = NONE;
}

void updateBall(Ball *ball, Player *player, float deltaTime) {
    ball->position.x += ball->speed.x * deltaTime;
    ball->position.y += ball->speed.y * deltaTime;
    if (ball->position.x <= 0 || ball->position.x >= (ScreenWidth - ball->radius)) {
        ball->speed.x *= -1;
    }
    if (ball->position.y <= 0) {
        ball->speed.y *= -1;
    }
    if (ball->position.y >= (ScreenHeight - ball->radius)) {
//        resetBall(ball);
        ball->speed = (Vector2) {};
        return; // todo temp
    }

    Rectangle playerRect = {
        .x = player->position.x,
        .y = player->position.y,
        .width = player->frame.width,
        .height = player->frame.height,
    };
    if (CheckCollisionCircleRec(ball->position, ball->radius, playerRect)) {
        ball->speed.y *= -1;
    }
}

void updateBricks(Brick *bricks, Ball *ball, float deltaTime) {
    for (int i = 0; i < array_length(bricks); i++) {
        if (bricks[i].health <= 0) {
            continue;
        }
        Rectangle brickRect = {
            .x = bricks[i].position.x,
            .y = bricks[i].position.y,
            .width = bricks[i].frame.width,
            .height = bricks[i].frame.height,
        };
        if (CheckCollisionCircleRec(ball->position, ball->radius, brickRect)) {
            ball->speed.y *= -1;
            bricks[i].health--;
        }
    }
}
