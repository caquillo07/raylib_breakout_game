//
// Created by Hector Mejia on 3/16/24.
//

#include <math.h>
#include "entities.h"
#include "array/array.h"

void updatePlayer(Player *player, float deltaTime) {
    if (player->direction == RIGHT) {
        player->position.x += player->speed * deltaTime;
        if (player->position.x >= (ScreenWidth - player->frame.width - WALL_THICKNESS)) {
            player->position.x = (ScreenWidth - player->frame.width - WALL_THICKNESS);
        }
    }
    if (player->direction == LEFT) {
        player->position.x -= player->speed * deltaTime;
        if (player->position.x <= WALL_THICKNESS) {
            player->position.x = WALL_THICKNESS;
        }
    }
    player->direction = NONE;
}

void updateBallLobby(Ball *ball, Player *player, float deltaTime) {
    ball->position.x = player->position.x + (player->frame.width / 2);
    ball->position.y = player->position.y - ball->radius;
}

static float lastBallY = 0;

void updateBall(Ball *ball, Player *player, float deltaTime) {
    ball->position.x += ball->speed.x * deltaTime;
    ball->position.y += ball->speed.y * deltaTime;

    if ((ball->position.x - ball->radius - WALL_THICKNESS) <= 0 ||
        ball->position.x + ball->radius >= (ScreenWidth - WALL_THICKNESS)) {
        ball->speed.x *= -1;
    }
    if (ball->position.y - ball->radius - WALL_THICKNESS <= 0) {
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
        bool ballHitLeftEdge = ball->position.x < player->position.x + player->frame.width / 6.f
            && ball->position.x > player->position.x;
        bool ballHitRightEdge = ball->position.x > player->position.x + player->frame.width * 5/6.f
            && ball->position.x < player->position.x + player->frame.width;
        if (ballHitLeftEdge || ballHitRightEdge) {
            ball->speed.x *= -1;
        }
    }
    if ((int) fabsf(ball->position.y - lastBallY) < (int) (ball->speed.y * deltaTime)) {
        ball->speed.y *= 1;
    }
    lastBallY = ball->position.y;
}

void updateBricks(Brick *bricks, Ball *ball, float deltaTime) {
    if (!deltaTime) {
        return;
    }
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
            // todo - this is a mess, and not in the right place. Find a better
            //  way to handle this
            Vector2 bRightSide = ballRightSide(ball);
            Vector2 bLeftSide = ballLeftSide(ball);
            Vector2 bTopSide = ballTopSide(ball);
            Vector2 bBottomSide = ballBottomSide(ball);
            bool hitLeft = bRightSide.x >= brickRect.x
                           && bLeftSide.x <= brickRect.x
                           && bTopSide.x < brickRect.x;
            bool hitRight = bLeftSide.x <= brickRect.x + brickRect.width
                            && bRightSide.x >= brickRect.x + brickRect.width
                            && bTopSide.x > brickRect.x + brickRect.width;
            if (hitLeft || hitRight) {
                ball->speed.x *= -1;
                bool hitTopEdge = bBottomSide.y <= brickRect.y + (brickRect.height * 0.1f);
                bool hitBottomEdge = bTopSide.y >= brickRect.y + (brickRect.height * 0.9f);

                if (hitTopEdge || hitBottomEdge) {
                    ball->speed.y *= -1;
                }
                goto FinishCollision;
            }

            bool hitTop = bBottomSide.y >= brickRect.y && bTopSide.y <= brickRect.y;
            bool hitBottom =
                bTopSide.y <= brickRect.y + brickRect.height && bBottomSide.y >= brickRect.y + brickRect.height;
            if (hitTop || hitBottom) {
                ball->speed.y *= -1;

//                bool hitTopEdge = bBotomSide.y <= brickRect.y + (brickRect.height * 0.1f);
//                bool hitBottomEdge = bTopSide.y >= brickRect.y + (brickRect.height * 0.9f);
//                if (hitTopEdge || hitBottomEdge) {
//                    ball->speed.x *= -1;
//                }
                goto FinishCollision;
            }

            FinishCollision:

            ball->speed.x += 10.f * (ball->speed.x < 0 ? -1.f : 1.f);
            ball->speed.y += 10.f * (ball->speed.y < 0 ? -1.f : 1.f);
            bricks[i].health--;
            return;
        }
    }
}

Vector2 ballLeftSide(Ball *ball) {
    Vector2 result = {
        .x = ball->position.x - ball->radius,
        .y = ball->position.y,
    };
    return result;
}

Vector2 ballRightSide(Ball *ball) {
    Vector2 result = {
        .x = ball->position.x + ball->radius,
        .y = ball->position.y,
    };
    return result;
}

Vector2 ballTopSide(Ball *ball) {
    Vector2 result = {
        .x = ball->position.x,
        .y = ball->position.y - ball->radius,
    };
    return result;
}

Vector2 ballBottomSide(Ball *ball) {
    Vector2 result = {
        .x = ball->position.x,
        .y = ball->position.y + ball->radius,
    };
    return result;
}
