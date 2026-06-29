#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"

#ifndef LIB_ENTITY_H
#define LIB_ENTITY_H

/*
 * Texture ownership:
 *   - set_texture() loads a texture and marks this entity as its OWNER.
 *   - use_texture() makes this entity reference another entity's texture
 *     WITHOUT taking ownership (no free on destroy).
 *   - destroy_entity() frees the texture only when this entity owns it,
 *     so a texture shared across several entities is freed exactly once.
 */
typedef struct {
    SDL_Texture *tex;
    bool owns_tex;
    Vector2 pos;
    Vector2 scale;
    decimal angle;
} Entity;

/*Texture Handling*/
bool set_texture(Entity *entity, const char *file, SDL_Renderer *ren);
void use_texture(Entity *dst, Entity *src);

/*Position Handling*/
void add_pos(Entity *entity, Vector2 add);
void sub_pos(Entity *entity, Vector2 sub);

/*Angle Handling*/
void add_angle(Entity *entity, decimal add);
void sub_angle(Entity *entity, decimal sub);

/*Other Handling*/
void draw_entity(Entity* entity, SDL_Renderer *ren);
bool check_entities_collision(Entity *a, Entity *b, Vector2 col_scale_a, Vector2 col_scale_b);
void destroy_entity(Entity* entity);

#endif /* LIB_ENTITY_H */