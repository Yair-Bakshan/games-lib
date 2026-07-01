#include "vector.h"
#include "entity.h"
#include "flappy.h"

const Vector2 FLAPPY_SCALE = {75, 50};
Sound FLAP_SFX;

bool check_height(Flappy *plr, const Vector2 *window_size) {
    return plr->entity.pos.y > window_size->y || plr->entity.pos.y < 0;
}

bool set_flappy(Flappy *plr, const Vector2 *window_size, SDL_Renderer *ren) {
    plr->entity.pos = get_center(window_size);
    plr->entity.scale = FLAPPY_SCALE;
    plr->velocity = 0;
    plr->score = 0;
    return set_texture(&plr->entity, "res/Flappy.png", ren);
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