#include <SDL2/SDL.h>
#include "vector.h"
#include "entity.h"
#include "flappy.h"

#ifndef PIPES
#define PIPES

#define PIPE_SPEED 200
#define PIPE_OFFSET 300

#define UPWARDS 50
#define MAX_GAP 350
#define MIN_GAP 250

extern const Vector2 SCALE;

typedef struct {
    Entity upper_pipe;
    Entity lower_pipe;
} Pipes;

void set_pipes(Pipes *pipes, SDL_Texture *tex, const Vector2 *window_size, int index);
void move_pipes(Pipes *pipes, decimal dt);
void loop_pipes(Pipes *pipes, const Vector2 *window_size);
bool check_flappy_collison(Flappy *plr, Pipes *pipes);

#endif