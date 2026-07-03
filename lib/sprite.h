#ifndef LIB_SPRITE_H
#define LIB_SPRITE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"

typedef struct {
    SDL_Texture **frames;  // array of loaded textures, one per frame
    int frame_count;
    int current_frame;
    decimal frame_time;    // seconds per frame
    decimal elapsed;       // internal timer, don't touch
} Sprite;

// Init / quit
bool sprite_init(void);
void sprite_quit(void);

// Loading/Freeing sprite
bool load_sprite(Sprite *spr, decimal frame_time, SDL_Renderer *ren, ...);
void free_sprite(Sprite *spr);

// Update sprite
void update_sprite(Sprite *spr, decimal dt);

#endif