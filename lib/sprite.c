#include <SDL2/SDL_image.h>
#include <stdarg.h>
#include "sprite.h"

// Init / quit
bool sprite_init(void) {
    return (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != 0;
}
void sprite_quit(void) {
    IMG_Quit();
}

// Loading/Freeing sprite
bool load_sprite(Sprite *spr, decimal frame_time, SDL_Renderer *ren, ...) {
    if(spr == NULL || ren == NULL) return false;

    spr->elapsed = 0;
    spr->frames = NULL;
    spr->frame_count = 0;
    spr->current_frame = 0;
    spr->frame_time = frame_time;
        
    va_list args;
    va_start(args, ren);

    int count;

    while(true) {
        const char *file = va_arg(args, const char *);

        if(file == NULL) break;

        count = spr->frame_count + 1;

        SDL_Texture **temp = realloc(spr->frames, count * sizeof(SDL_Texture *));

        if (temp == NULL) { // In case something goes wrong
            va_end(args);
            free_sprite(spr); // release whatever frames loaded so far
            return false;
        }
        spr->frames = temp;

        SDL_Texture *tex = IMG_LoadTexture(ren, file);

        if (tex == NULL) {
            SDL_Log("Failed to load: %s, Error: %s", file, IMG_GetError());
            continue;
        }

        spr->frames[spr->frame_count] = tex;
        spr->frame_count++;
    }
    va_end(args);

    if (spr->frame_count == 0) {
        free_sprite(spr); // nothing loaded successfully — nothing left dangling
        return false;
    }
    return true;
}
void free_sprite(Sprite *spr) {
    if (spr == NULL) return;

    for (int i = 0; i < spr->frame_count; i++) {
        if (spr->frames[i] != NULL) {
            SDL_DestroyTexture(spr->frames[i]);
        }
    }
    
    free(spr->frames);
    spr->frames = NULL;
    spr->frame_count = 0;
}

// Update sprite
void update_sprite(Sprite *spr, decimal dt) {
    if(spr == NULL) return;
    if (spr->frame_count == 0 || spr->frame_count == 1) return;
    
    spr->elapsed += dt;

    if(spr->elapsed > spr->frame_time) {
        spr->current_frame++;

        if(spr->current_frame == spr->frame_count) spr->current_frame = 0;

        spr->elapsed -= spr->frame_time;
    }
}