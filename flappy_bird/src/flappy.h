#include "vector.h"
#include "entity.h"

#ifndef FLAPPY
#define FLAPPY

#define GRAVITY     2000.0
#define JUMP_FORCE   850.0
#define ANGLE_FACTOR 0.08

typedef struct {
    Entity entity;
    decimal velocity;
} Flappy;

bool check_height(Flappy *plr, const Vector2 *window_size);
void apply_gravity(Flappy *plr, decimal dt);
void update_angle(Flappy *plr);
void jump(Flappy *plr);

#endif