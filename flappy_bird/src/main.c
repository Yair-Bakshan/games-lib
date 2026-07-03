#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
#include "audio.h"
#include "font.h"
#include "pipes.h"
#include "vector.h"
#include "entity.h"
#include "flappy.h"

#define NAME "Flappy Bird"
#define PIPES_AMOUNT 3
#define FONT_SIZE 80
const Vector2 WINDOW_SIZE = {800, 800};
const Vector2 SCORE_POS = {400, 50};
const SDL_Color FONT_COLOR = {255, 255, 255, 255};

int main(void) {
    int ret = 1;

    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;
    bool sprite_ready = false, audio_ready = false, font_ready = false;

    Sprite pipes_spr = {0};
    Sprite flappy_spr = {0};
    Music track = {0};
    Font font = {0};
    Pipes pipes[PIPES_AMOUNT] = {0};
    Flappy plr = {0};

    bool running = true;
    bool pressed = false;
    char score[20];
    Uint32 last;
    SDL_Event e;

    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        goto cleanup;
    }

    // 2. Create a window
    win = SDL_CreateWindow(
        NAME,                              // title
        SDL_WINDOWPOS_CENTERED,           // x
        SDL_WINDOWPOS_CENTERED,          // y
        WINDOW_SIZE.x, WINDOW_SIZE.y,   // width, height
        0                              // flags
    );
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        goto cleanup;
    }

    // 3. Initialize SDL Image / Audio / Font subsystems
    if (!sprite_init()) {
        SDL_Log("IMG_Init failed: %s", IMG_GetError());
        goto cleanup;
    }
    sprite_ready = true;

    if (!audio_init()) {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        goto cleanup;
    }
    audio_ready = true;

    if (!font_init()) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        goto cleanup;
    }
    font_ready = true;

    // 4. Create a renderer
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        goto cleanup;
    }

    srand(time(NULL));

    // 5. Enable Blend
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    if (!load_sprite(&pipes_spr, 0, ren, "res/Pipe.png", NULL)) {
        SDL_Log("Failed to load res/Pipe.png: %s", IMG_GetError());
        goto cleanup;
    }

    for (int i = 0; i < PIPES_AMOUNT; i++)
        set_pipes(&pipes[i], &pipes_spr, &WINDOW_SIZE , i + 1);

    if (!load_sound(&FLAP_SFX, "res/sfx_wing.wav")) {
        SDL_Log("Failed to load res/sfx_wing.wav: %s", Mix_GetError());
        goto cleanup;
    }
    if (!load_sound(&SCORE_SFX, "res/sfx_point.wav")) {
        SDL_Log("Failed to load res/sfx_point.wav: %s", Mix_GetError());
        goto cleanup;
    }
    if (!load_music(&track, "res/track.ogg")) {
        SDL_Log("Failed to load res/track.ogg: %s", Mix_GetError());
        goto cleanup;
    }

    play_music(&track);

    if(!load_font(&font, &FONT_COLOR, FONT_SIZE, "res/font.ttf")) {
        SDL_Log("Failed to load res/font.ttf: %s", TTF_GetError());
        goto cleanup;
    }

    if (!load_sprite(&flappy_spr, 0.125, ren, "res/Flappy1.png", "res/Flappy2.png", "res/Flappy3.png", NULL)) {
        SDL_Log("Failed to load res/Flappy.png: %s", IMG_GetError());
        goto cleanup;
    }
    set_flappy(&plr, &flappy_spr, &WINDOW_SIZE);

    // 6. Main loop
    last = SDL_GetTicks();
    while (running) {
        Uint32 now = SDL_GetTicks();
        decimal dt = (now - last) / 1000.0;
        last = now;

        // Handle events
        while (SDL_PollEvent(&e)) {
            // Window related events
            if (e.type == SDL_QUIT)
                running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                running = false;

            // Player events — flap on Space or left-click (either source)
            bool flap_down = (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) ||
                             (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT);
            bool flap_up   = (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE) ||
                             (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT);

            if (flap_down && !pressed) {
                jump(&plr);
                pressed = true;
            }
            if (flap_up)
                pressed = false;
        }

        // Clear screen (dark blue)
        SDL_SetRenderDrawColor(ren, 135, 206, 235, 255);
        SDL_RenderClear(ren);

        // Draw a cool grid
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 75);
        for (int gx = 0; gx < WINDOW_SIZE.x; gx += 64)
            SDL_RenderDrawLine(ren, gx, 0, gx, WINDOW_SIZE.y);
        for (int gy = 0; gy < WINDOW_SIZE.y; gy += 64)
            SDL_RenderDrawLine(ren, 0, gy, WINDOW_SIZE.x, gy);

        // Handle the player
        apply_gravity(&plr, dt);
        update_angle(&plr);
        draw_entity(&plr.entity, dt, ren);

        if(check_height(&plr, &WINDOW_SIZE))
            running = false;

        // Handle the pipes
        for (int i = 0; i < PIPES_AMOUNT; i++)
        {
            draw_entity(&pipes[i].lower_pipe, dt, ren);
            draw_entity(&pipes[i].upper_pipe, dt, ren);
            move_pipes(&pipes[i], dt);
            loop_pipes(&pipes[i], &plr, &WINDOW_SIZE);

            if(check_flappy_collison(&plr, &pipes[i]))
                running = false;
        }

        snprintf(score, sizeof(score), "%d", plr.score);
        draw_text(&font, score, &SCORE_POS, ren);

        // Present (swap buffers)
        SDL_RenderPresent(ren);
    }

    ret = 0;

cleanup:
    // 7. Cleanup — each step below is safe to call even if the
    // corresponding resource/subsystem was never successfully acquired
    // (structs are zero-initialized, and the free/_quit functions guard
    // against NULL and against subsystems that were never opened).
    stop_music();

    free_music(&track);
    free_sound(&SCORE_SFX);
    free_sound(&FLAP_SFX);
    free_font(&font);
    free_sprite(&pipes_spr);
    free_sprite(&flappy_spr);

    if (font_ready) font_quit();
    if (audio_ready) audio_quit();
    if (sprite_ready) sprite_quit();

    if (ren) SDL_DestroyRenderer(ren);
    if (win) SDL_DestroyWindow(win);
    SDL_Quit();

    return ret;
}
