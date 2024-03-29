//
// Created by Hector Mejia on 3/16/24.
//

#include "game.h"
#include "array/array.h"
#include "levels.h"


void gameInit(Game *game) {
    game->level = 1;
    game->highestScore = 0;
    game->state = LOBBY;

    TextureAtlas *atlas = getTextureAtlas("atlas");
    panicIf(atlas == nil, "Failed to get texture atlas");

    Sprite *playerSprite = getSprite(atlas, "paddleBlu");
    panicIf(playerSprite == nil, "Failed to get sprite");

    game->player = newPlayer(*playerSprite);
    game->ball = newBall(*getSprite(atlas, "ballBlue"), game->player);

    Sprite *brickSprite = getSprite(atlas, "element_blue_rectangle");
    panicIf(brickSprite == nil, "Failed to get sprite");

    loadLevel(game, atlas, 1);
}

void destroyGame(Game *game) {
    destroyPlayer(game->player);
    game->player = nil;

    array_free(game->bricks);
    game->bricks = nil;

    destroyBall(game->ball);
    game->ball = nil;
}

void drawDebug(Game *game) {
    if (!game->isDebug) {
        return;
    }

    const int fontSize = 20;
    const int topPadding = 30;
    const int leftPadding = 10;
    DrawText(
        TextFormat("Ball Speed: %02.fx%02.f", game->ball->speed.x, game->ball->speed.y),
        leftPadding,
        topPadding,
        fontSize,
        GREEN
    );
    DrawText(
        TextFormat("Ball Multi: %i", game->ball->isMultiplied),
        leftPadding,
        topPadding + fontSize,
        fontSize,
        GREEN
    );
}

void drawHUD(Game *game) {
    const int topPadding = 10;
    const int rightPadding = 20;
    const int fontSize = 30;
    const char *currentScoreText = TextFormat("Score: %i", game->player->score);
    const int currentScoreWidth = MeasureText(currentScoreText, fontSize);
    DrawText(
        currentScoreText,
        ScreenWidth - currentScoreWidth - rightPadding,
        topPadding,
        fontSize,
        WHITE
    );

    const char *highestScoreText = TextFormat("Highest Score: %i", game->highestScore);
    const int highestScoreWidth = MeasureText(highestScoreText, fontSize);
    DrawText(
        highestScoreText,
        ScreenWidth - highestScoreWidth - rightPadding,
        topPadding + fontSize /* the height of the previous text */,
        fontSize,
        WHITE
    );

    const char *levelText = TextFormat("Level: %i", game->level);
    DrawText(
        levelText,
        rightPadding,
        topPadding,
        fontSize,
        WHITE
    );

    const char *livesText = TextFormat("Lives: %i", game->player->lives);
    DrawText(
        livesText,
        rightPadding,
        topPadding + fontSize /* the height of "the" previous text */,
        fontSize,
        WHITE
    );
}

void updateGame(Game *game) {
    if (game->highestScore < game->player->score) {
        game->highestScore = game->player->score;
    }

    if (game->ball->dead) {
        game->player->lives--;
        if (game->player->lives <= 0) {
            game->state = GAME_OVER;
            return;
        }
        resetBall(game->ball, game->player);
        game->state = LOBBY;
        return;
    }

    if (game->brickCount <= 0 && game->state == PLAYING) {
        if (game->level == TOTAL_LEVELS) {
            game->state = WIN;
            return;
        }
        game->level++;
        loadLevel(game, getTextureAtlas("atlas"), game->level);
        resetBall(game->ball, game->player);
        game->state = LOBBY;
    }
}

void loadLevel(Game *game, TextureAtlas *atlas, const int levelNum) {
    int levelData[BRICKS_PER_MAP];
    switch (levelNum) {
        case 1:
            memcpy(levelData, levelOneBricks, sizeof(levelOneBricks));
            break;
        case 2:
            memcpy(levelData, levelTwoBricks, sizeof(levelTwoBricks));
            break;
        case 3:
            memcpy(levelData, levelThreeBricks, sizeof(levelThreeBricks));
            break;
        default:
            memcpy(levelData, levelOneBricks, sizeof(levelOneBricks));
            break;
    }


    if (game->bricks != nil) {
        array_free(game->bricks);
        game->bricks = nil;
    }
    Sprite *brickSprite = getSprite(atlas, "element_blue_rectangle");
    for (int i = 0; i < BRICKS_PER_MAP; i++) {
        if (levelData[i] == 0) {
            continue;
        }

        const float topPadding = 20;
        float brickX = (float) (i % MAP_WIDTH) * (float) brickSprite->sourceWidth;
        float brickY = ((float) (i / MAP_WIDTH) * (float) brickSprite->sourceHeight) + topPadding;
        float emptyXSpace = (float) (MAP_WIDTH * brickSprite->sourceWidth) - ScreenWidth;
        Brick brick = {
            .frame = getSpriteFrame(*brickSprite),
            .health = 1,
            .sprite = *brickSprite,
            .position = (Vector2) {
                .x = brickX - emptyXSpace / 2,
                .y = brickY - emptyXSpace / 2,
            },
        };
        array_push(game->bricks, brick);
    }
    game->brickCount = array_length(game->bricks);
}

void resetGame(Game *game) {
    game->player->score = 0;
    game->player->lives = 3;
    game->level = 1;
    game->state = LOBBY;

    // player
    resetPlayer(game->player);
    resetBall(game->ball, game->player);
    loadLevel(game, getTextureAtlas("atlas"), 1);
}
