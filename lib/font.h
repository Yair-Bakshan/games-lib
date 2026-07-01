#ifndef LIB_FONT_H
#define LIB_FONT_H

#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "vector.h"

typedef struct {
    TTF_Font *ttf;
    SDL_Color color;
} Font;

// Init / quit
bool font_init(void);
void font_quit(void);

// Loading/Free font
bool load_font(Font *font, SDL_Color *color, int size, const char *file);
void free_font(Font *font);

// Draw font
void draw_text(Font *font, const char *text, const Vector2 *pos, SDL_Renderer *ren);

#endif