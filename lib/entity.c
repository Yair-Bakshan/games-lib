#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vector.h"
#include "entity.h"

/* Position Handling */
void add_pos(Entity *entity, Vector2 add) { 
    entity->pos = add_vector2(entity->pos, add);
}

void sub_pos(Entity *entity, Vector2 sub) {
    entity->pos = sub_vector2(entity->pos, sub);
}

/* Angle Handling */
void add_angle(Entity *entity, decimal add) {
    entity->angle += add;
}

void sub_angle(Entity *entity, decimal sub) {
    entity->angle -= sub;
}

/* Other */
void draw_entity(Entity* entity, decimal dt, SDL_Renderer *ren) {
    if (!entity->sprite) return;
    if (!entity->sprite->frames)return;
    update_sprite(entity->sprite, dt);

    SDL_Rect dst = {
        (int)(entity->pos.x - entity->scale.x / 2.0f),
        (int)(entity->pos.y - entity->scale.y / 2.0f),
        (int)entity->scale.x,
        (int)entity->scale.y
    };
    
    SDL_RenderCopyEx(
        ren,
        entity->sprite->frames[entity->sprite->current_frame],
        NULL,       /* source rect — NULL = whole texture             */
        &dst,       /* destination rect                               */
        entity->angle,      /* rotation in degrees, clockwise                 */
        NULL,       /* centre of rotation — NULL = dst centre         */
        SDL_FLIP_NONE
    );
}

/* Axis-aligned bounding-box test; entity rotation (angle) is ignored. */
bool check_entities_collision(Entity *a, Entity *b, Vector2 col_scale_a, Vector2 col_scale_b) {
    decimal ha_x = a->scale.x * col_scale_a.x / 2.0f;
    decimal ha_y = a->scale.y * col_scale_a.y / 2.0f;
    decimal hb_x = b->scale.x * col_scale_b.x / 2.0f;
    decimal hb_y = b->scale.y * col_scale_b.y / 2.0f;

    return !(a->pos.x + ha_x <= b->pos.x - hb_x ||
             a->pos.x - ha_x >= b->pos.x + hb_x ||
             a->pos.y + ha_y <= b->pos.y - hb_y ||
             a->pos.y - ha_y >= b->pos.y + hb_y);
}