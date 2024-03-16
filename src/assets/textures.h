//
// Created by Hector Mejia on 3/15/24.
//

#ifndef BREAKOUT_GAME_TEXTURES_H
#define BREAKOUT_GAME_TEXTURES_H


#include "raylib.h"
#include "atlas.h"

#define MAX_ATLAS_NAME_LENGTH 64

typedef rtpAtlasSprite Sprite ;

typedef struct TextureAtlas {
    char name[MAX_ATLAS_NAME_LENGTH];
    Texture texture;
    Sprite sprites[ATLAS_ATLAS_SPRITE_COUNT];
} TextureAtlas;

#define AtlasTextureName "atlas"

void initTextureManager();
TextureAtlas *getTextureAtlas(const char *atlasName);
Sprite* getSprite(TextureAtlas *atlas, const char *spriteName);
Sprite* getSpriteByID(TextureAtlas *atlas, rtpAtlasSpriteID id);
Rectangle getSpriteFrame(Sprite sprite);
void destroyTextureManager();

#endif //BREAKOUT_GAME_TEXTURES_H
