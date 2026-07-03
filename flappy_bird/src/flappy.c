#include "vector.h"
#include "entity.h"
#include "flappy.h"

const Vector2 FLAPPY_SCALE = {75, 75};
Sound FLAP_SFX;

bool check_height(Flappy *plr, const Vector2 *window_size) {
    return plr->entity.pos.y > window_size->y || plr->entity.pos.y < 0;
}

void set_flappy(Flappy *plr, Sprite *spr, const Vector2 *window_size) {
    plr->entity.pos = get_center(window_size);
    plr->entity.scale = FLAPPY_SCALE;
    plr->entity.sprite = spr;
    plr->entity.angle = 0;
    plr->velocity = 0;
    plr->score = 0;
}

void apply_gravity(Flappy *plr, decimal dt) {
    plr->velocity += GRAVITY * dt;
    plr->entity.pos.y += plr->velocity * dt;
}

void update_angle(Flappy *plr) {
    plr->entity.angle = plr->velocity * ANGLE_FACTOR;
}

void jump(Flappy *plr) {
    play_sound(&FLAP_SFX);
    plr->velocity = -JUMP_FORCE;
}