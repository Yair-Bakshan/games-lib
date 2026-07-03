#include "font.h"

bool font_init(void) {
    return TTF_Init() == 0;
}
void font_quit(void) {
    TTF_Quit();
}

bool load_font(Font *font, const SDL_Color *color, int size, const char *file) {
    if (font == NULL || color == NULL) return false;
    font->ttf = TTF_OpenFont(file, size); // Set the ttf
    font->color = *color; // Set the color
    return font->ttf != NULL; // Return if load was succesfull
}
void free_font(Font *font) {
    if (font == NULL) return;
    TTF_CloseFont(font->ttf);
    font->ttf = NULL;
}

void draw_text(Font *font, const char *text, const Vector2 *pos, SDL_Renderer *ren) {
    if (font == NULL || pos == NULL || font->ttf == NULL) return;

    SDL_Surface *surf = TTF_RenderText_Blended(font->ttf, text, font->color);

    if (!surf) return;

    SDL_Texture *tex  = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf); // Free surface immediately after converting

    // Get size so you can position it
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_Rect dst = {pos->x - w / 2.0, pos->y - h / 2.0, w, h};
    SDL_RenderCopy(ren, tex, NULL, &dst);

    SDL_DestroyTexture(tex); // Free after drawing

}