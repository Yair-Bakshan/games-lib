#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"
#include "entity.h"
#include "flappy.h"
#include "pipes.h"

const Vector2 SCALE = {90, 555};
void set_gap(Pipes *pipes, decimal gap, decimal upwards, const Vector2 *window_size);


void set_pipes(Pipes *pipes, SDL_Texture *tex, const Vector2 *window_size, int index) {
    /* 1. Set textures first (shared, non-owning: main owns the texture) */
    pipes->lower_pipe.tex = tex;
    pipes->lower_pipe.owns_tex = false;
    pipes->upper_pipe.tex = tex;
    pipes->upper_pipe.owns_tex = false;

    /* 2. Set the positions (without gaps) */
    // Lower pipe
    pipes->lower_pipe.pos.x = window_size->x + SCALE.x / 2.0 + PIPE_OFFSET * index; // X

    // Upper pipe
    pipes->upper_pipe.pos.x = window_size->x + SCALE.x / 2.0 + PIPE_OFFSET * index; // X

    /* 5. Set the y axis */
    decimal gap = MIN_GAP + ((decimal)rand() / RAND_MAX) * (MAX_GAP - MIN_GAP);
    decimal upwards = -UPWARDS + ((decimal)rand() / RAND_MAX) * (UPWARDS + UPWARDS);
    set_gap(pipes, gap, upwards, window_size);

    /* 3. Set the scales */
    pipes->lower_pipe.scale = SCALE; // Lower pipe
    pipes->upper_pipe.scale = SCALE; // Upper pipe

    /* 4. Set the angles (lower upright, upper flipped) */
    pipes->lower_pipe.angle = 0;
    pipes->upper_pipe.angle = 180;

}

void set_gap(Pipes *pipes , decimal gap, decimal upwards, const Vector2 *window_size) {

    // Reset pipes position
    pipes->lower_pipe.pos.y = window_size->y / 2.0 + upwards;
    pipes->upper_pipe.pos.y = window_size->y / 2.0 + upwards;

    // Set the gap
    pipes->lower_pipe.pos.y += gap / 2.0 + SCALE.y / 2.0;
    pipes->upper_pipe.pos.y -= gap / 2.0 + SCALE.y / 2.0;
}

void move_pipes(Pipes *pipes, decimal dt) {
    pipes->lower_pipe.pos.x -= PIPE_SPEED * dt;
    pipes->upper_pipe.pos.x -= PIPE_SPEED * dt;
}

void loop_pipes(Pipes *pipes, const Vector2 *window_size) {
    if(pipes->upper_pipe.pos.x < -SCALE.x / 2.0)
    {
        pipes->lower_pipe.pos.x = window_size->x + SCALE.x / 2.0; // Lower pipe
        pipes->upper_pipe.pos.x = window_size->x + SCALE.x / 2.0; // Upper pipe

        // Setting the y axis
        decimal gap = MIN_GAP + ((decimal)rand() / RAND_MAX) * (MAX_GAP - MIN_GAP);
        decimal upwards = -UPWARDS + ((decimal)rand() / RAND_MAX) * (UPWARDS + UPWARDS);
        set_gap(pipes, gap, upwards, window_size);
    }
}

bool check_flappy_collison(Flappy *plr, Pipes *pipes) {
    bool col_lower = check_entities_collision(
        &plr->entity,
        &pipes->lower_pipe,
        (Vector2){0.8, 1},
        (Vector2){1, 1});

    bool col_upper = check_entities_collision(
        &plr->entity,
        &pipes->upper_pipe,
        (Vector2){0.8, 1},
        (Vector2){1, 1});

    return col_lower || col_upper;
}