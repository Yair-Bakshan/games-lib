#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "audio.h"
#include "font.h"
#include "pipes.h"
#include "vector.h"
#include "entity.h"
#include "flappy.h"

#define NAME "Flappy Bird"
#define PIPES_AMOUNT 3
const Vector2 WINDOW_SIZE = {800, 800};
const Vector2 SCORE_POS = {400, 50};

int main(void) {
    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    // 2. Create a window
    SDL_Window *win = SDL_CreateWindow(
        NAME,                              // title
        SDL_WINDOWPOS_CENTERED,           // x
        SDL_WINDOWPOS_CENTERED,          // y
        WINDOW_SIZE.x, WINDOW_SIZE.y,   // width, height
        0                              // flags
    );
    
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // 3. Initialize SDL Image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        SDL_Log("IMG_Init failed: %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if(!audio_init()) {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        IMG_Quit(); SDL_Quit();
        return 1;
    }

    if(!font_init()) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        IMG_Quit(); SDL_Quit();
        return 1;
    }

    // 4. Create a renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    srand(time(NULL));

    // 5. Enable Blend
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    
    SDL_Texture *pipes_tex = IMG_LoadTexture(ren, "res/Pipe.png");
    if (!pipes_tex) {
        SDL_Log("Failed to load Player.png: %s", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit(); SDL_Quit();
        return 1;
    }
    
    bool running = true;
    bool pressed = false;

    char score[20];
    Uint32 last = SDL_GetTicks();
    SDL_Event e;

    Pipes pipes[PIPES_AMOUNT];

    for (int i = 0; i < PIPES_AMOUNT; i++)
        set_pipes(&pipes[i], pipes_tex, &WINDOW_SIZE , i + 1);

    Music track;
    load_sound(&FLAP_SFX, "res/sfx_wing.wav");
    load_sound(&SCORE_SFX, "res/sfx_point.wav");
    load_music(&track, "res/track.ogg");
    play_music(&track);

    Font font;
    load_font(&font, &(SDL_Color){255, 255, 255, 255}, 80, "res/font.ttf");

    Flappy plr;

    if(!set_flappy(&plr, &WINDOW_SIZE, ren)) {
        SDL_Log("Failed to load res/Flappy.png: %s", IMG_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit(); SDL_Quit();
        return 1;
    }

    // 6. Main loop
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
                
            // Player events
            if (!pressed) {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                    jump(&plr);
                    pressed = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    jump(&plr);
                    pressed = true;
                }
            }
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
                pressed = false;
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
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
        draw_entity(&plr.entity, ren);
        apply_gravity(&plr, dt);
        update_angle(&plr);

        if(check_height(&plr, &WINDOW_SIZE))
            running = false;

        // Handle the pipes
        for (int i = 0; i < PIPES_AMOUNT; i++)
        {
            draw_entity(&pipes[i].lower_pipe, ren);
            draw_entity(&pipes[i].upper_pipe, ren);
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

    // 7. Cleanup
    stop_music();

    free_music(&track);
    free_sound(&SCORE_SFX);
    free_sound(&FLAP_SFX);
    free_font(&font);
    SDL_DestroyTexture(pipes_tex); /* shared by all pipes; freed once here */
    destroy_entity(&plr.entity);

    font_quit();
    audio_quit();
    IMG_Quit();
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}