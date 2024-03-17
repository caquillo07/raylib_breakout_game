//
// Created by Hector Mejia on 3/16/24.
//

#include "game.h"
#include "array/array.h"

#define MAP_WIDTH 6
#define MAP_HEIGHT 4
const int bricksMap[MAP_HEIGHT * MAP_WIDTH] = {
    1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1,
};

void gameInit(Game *game) {
    TextureAtlas *atlas = getTextureAtlas("atlas");
    game->player = (Player *) malloc(sizeof(Player));
    panicIf(game->player == nil, "Failed to allocate memory for player");
    memset(game->player, 0, sizeof(Player));
    Sprite *sprite = getSprite(atlas, "paddleBlu");
    panicIf(sprite == nil, "Failed to get sprite");
    game->player->sprite = *sprite;
    game->player->speed = 350;
    game->player->position = (Vector2) {(ScreenWidth / 2) - (sprite->sourceWidth / 2), 600};
    game->player->direction = NONE;
    game->player->frame = getSpriteFrame(*sprite);

    Sprite *brickSprite = getSprite(atlas, "element_blue_rectangle");
    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        if (bricksMap[i] == 0) {
            continue;
        }
        float brickX = (i % MAP_WIDTH) * brickSprite->sourceWidth;
        float brickY = (i / MAP_WIDTH) * brickSprite->sourceHeight;
        float emptyXSpace = (MAP_WIDTH * brickSprite->sourceWidth) - ScreenWidth;
        Brick brick = {
            .frame = getSpriteFrame(*brickSprite),
            .health = bricksMap[i],
            .sprite = *brickSprite,
            .position = (Vector2) {
                .x = brickX - emptyXSpace / 2,
                .y = brickY - emptyXSpace / 2,
            },
        };
        array_push(game->bricks, brick);
    }
    game->brickCount = array_length(game->bricks);

    game->ball = (Ball *) malloc(sizeof(Ball));
    panicIf(game->ball == nil, "Failed to allocate memory for ball");
    memset(game->ball, 0, sizeof(Ball));

    Sprite* ballSprite = getSprite(atlas, "ballBlue");
    panicIf(ballSprite == nil, "Failed to get sprite");


    float ballX = (ScreenWidth / 2) - (ballSprite->sourceWidth / 2);
    float ballY = game->player->position.y - ballSprite->sourceHeight;
    game->ball->position = (Vector2) {ballX, ballY};
    game->ball->speed = (Vector2) {200, -200};
    game->ball->radius = ballSprite->sourceWidth / 2;
    game->ball->sprite = *ballSprite;
    game->ball->frame = getSpriteFrame(*ballSprite);

    game->state = LOBBY;
}

void destroyGame(Game *game) {
    free(game->player);
    game->player = nil;
    array_free(game->bricks);
    game->bricks = nil;
    free(game->ball);
    game->ball = nil;
}
