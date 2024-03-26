//
// Created by Hector Mejia on 3/20/24.
//

#ifndef BREAKOUT_GAME_LEVELS_H
#define BREAKOUT_GAME_LEVELS_H

#define MAP_WIDTH 6
#define MAP_HEIGHT 5
#define BRICKS_PER_MAP MAP_WIDTH * MAP_HEIGHT
#define TOTAL_LEVELS 3

//static const int levelOneBricks[BRICKS_PER_MAP] = {
//    1, 1, 1, 1, 1, 1,
//    1, 0, 0, 0, 0, 1,
//    1, 0, 0, 0, 0, 1,
//    1, 1, 1, 1, 1, 1,
//    0, 0, 0, 0, 0, 0,
//};
//
//static const int levelTwoBricks[BRICKS_PER_MAP] = {
//    1, 1, 1, 1, 1, 1,
//    1, 0, 1, 0, 0, 1,
//    1, 1, 0, 1, 0, 1,
//    1, 0, 1, 0, 0, 1,
//    1, 1, 1, 1, 1, 1,
//};
//
//static const int levelThreeBricks[BRICKS_PER_MAP] = {
//    1, 1, 1, 1, 1, 1,
//    1, 1, 0, 0, 1, 1,
//    1, 1, 0, 0, 1, 1,
//    1, 1, 0, 0, 1, 1,
//    1, 1, 1, 1, 1, 1,
//};
static const int levelOneBricks[BRICKS_PER_MAP] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0,
};

static const int levelTwoBricks[BRICKS_PER_MAP] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1,
};

static const int levelThreeBricks[BRICKS_PER_MAP] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1,
};

#endif //BREAKOUT_GAME_LEVELS_H
