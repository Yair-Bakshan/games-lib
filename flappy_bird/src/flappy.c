#include "vector.h"
#include "entity.h"
#include "flappy.h"

bool check_height(Flappy *plr, const Vector2 *window_size) {
    return plr->entity.pos.y > window_size->y || plr->entity.pos.y < 0;
}

void apply_gravity(Flappy *plr, decimal dt) {
    plr->velocity += GRAVITY * dt;
    plr->entity.pos.y += plr->velocity * dt;
}

void update_angle(Flappy *plr) {
    plr->entity.angle = plr->velocity * ANGLE_FACTOR;
}

void jump(Flappy *plr) {
    plr->velocity = -JUMP_FORCE;
}