//
// Created by Hector Mejia on 3/15/24.
//

#include "../common.h"
#include "textures.h"
#include "../array/array.h"


typedef struct manager {
    TextureAtlas *atlases;
} manager;

static manager textureManager = {
    .atlases = NULL,
};

void initTextureManager() {
    TextureAtlas mainTextureAtlas = {
        .name = AtlasTextureName,
        .texture = LoadTexture(ATLAS_ATLAS_IMAGE_PATH),
        .sprites = {},
    };
    memcpy(
        mainTextureAtlas.sprites,
        rtpDescAtlas,
        sizeof(rtpDescAtlas)
    );
    array_push(textureManager.atlases, mainTextureAtlas);
    slogi("Loaded texture atlas \"%s\" (%dx%d | %d Sprites)",
          mainTextureAtlas.name,
          mainTextureAtlas.texture.width,
          mainTextureAtlas.texture.height,
          sizeof(mainTextureAtlas.sprites) / sizeof(Sprite)
    );
}

TextureAtlas *getTextureAtlas(const char *atlasName) {
    for (int i = 0; i < array_length(textureManager.atlases); i++) {
        if (strcmp(atlasName, textureManager.atlases[i].name) == 0) {
            return &textureManager.atlases[i];
        }
    }

    return nil;
}

Sprite *getSprite(TextureAtlas *atlas, const char *spriteName) {
    for (usize i = 0; i < sizeof(atlas->sprites)/sizeof(atlas->sprites[0]); i++) {
        if (strcmp(spriteName, atlas->sprites[i].nameId) == 0) {
            return &atlas->sprites[i];
        }
    }

    return nil;
}

Sprite *getSpriteByID(TextureAtlas *atlas, rtpAtlasSpriteID id) {
    if (id > sizeof(atlas->sprites)/sizeof(atlas->sprites[0])) {
        return nil;
    }
    return &atlas->sprites[id];
}

void destroyTextureManager() {
    for (int i = 0; i < array_length(textureManager.atlases); i++) {
        UnloadTexture(textureManager.atlases[i].texture);
    }
    array_free(textureManager.atlases);
    textureManager.atlases = nil;
}

Rectangle getSpriteFrame(Sprite sprite) {
    Rectangle result = {
        .x = (float)sprite.positionX,
        .y = (float)sprite.positionY,
        .width = (float)sprite.sourceWidth,
        .height = (float)sprite.sourceHeight,
    };
    return result;
}

