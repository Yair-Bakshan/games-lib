#include <SDL2/SDL.h>
#include "vector.h"
#include "entity.h"
#include "sprite.h"
#include "flappy.h"
#include "audio.h"

#ifndef PIPES
#define PIPES

#define PIPE_SPEED 200
#define PIPE_OFFSET 300

#define UPWARDS 50
#define MAX_GAP 400
#define MIN_GAP 300

extern Sound SCORE_SFX;
extern const Vector2 PIPE_SCALE;

typedef struct {
    Entity upper_pipe;
    Entity lower_pipe;
    bool passed;
} Pipes;

void set_pipes(Pipes *pipes, Sprite *spr, const Vector2 *window_size, int index);
void move_pipes(Pipes *pipes, decimal dt);
void loop_pipes(Pipes *pipes, Flappy *plr, const Vector2 *window_size);
bool check_flappy_collison(Flappy *plr, Pipes *pipes);

#endif