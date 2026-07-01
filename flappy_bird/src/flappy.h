#include "vector.h"
#include "entity.h"
#include "audio.h"

#ifndef FLAPPY
#define FLAPPY

#define GRAVITY     2000.0
#define JUMP_FORCE   850.0
#define ANGLE_FACTOR 0.08

extern const Vector2 FLAPPY_SCALE;
extern Sound FLAP_SFX;

typedef struct {
    Entity entity;
    decimal velocity;
    int score;
} Flappy;

bool check_height(Flappy *plr, const Vector2 *window_size);
bool set_flappy(Flappy *plr, const Vector2 *window_size, SDL_Renderer *ren);
void apply_gravity(Flappy *plr, decimal dt);
void update_angle(Flappy *plr);
void jump(Flappy *plr);

#endif